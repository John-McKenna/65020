library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;
use work.CPU.all;

--                              +-------+
-- A -------------------------> |       | ------> result
--                              | ADDER |
-- B --> SHIFTER --> INVERT --> |       |
--         ^ ^                  +-------+
-- shift --+ |                      ^
--           |                      |
-- C --------+----------------------+

-- Shifter interface
--		input : in STD_LOGIC_VECTOR(31 downto 0);
--		cIn : in STD_LOGIC;
--		amount : in STD_LOGIC_VECTOR(4 downto 0);
--		size : in STD_LOGIC_VECTOR(1 downto 0);

--		shiftRight : in STD_LOGIC;
--		rotate : in STD_LOGIC;
--		rotateWord : in STD_LOGIC;
--		extend : in STD_LOGIC;

--		result : out STD_LOGIC_VECTOR(31 downto 0);
--		cOut : out STD_LOGIC

--  right	rotate	word	extend	instruction
--	0		0		x		0		ASL
--	0		0		x		1		ESL
--	0		1		0		x		ROL
--	0		1		1		x		RLB
--	1		0		x		0		LSR
--	1		0		x		1		ASR
--	1		1		0		x		ROR
--	1		1		1		x		RRB

-- Inverter interface
--		input : in STD_LOGIC_VECTOR(3 downto 0);
--		invert : in STD_LOGIC;
--		decimal : in STD_LOGIC;

--		result : out STD_LOGIC_VECTOR(3 downto 0);

-- Adder interface
--		inputA : in STD_LOGIC_VECTOR(3 downto 0);
--		inputB : in STD_LOGIC_VECTOR(3 downto 0);
--		op : in STD_LOGIC_VECTOR(1 downto 0);
--		carryIn : in STD_LOGIC;
--		decimal : in STD_LOGIC;

--		result : out STD_LOGIC_VECTOR(3 downto 0);
--		carryOut : out STD_LOGIC

		-- carry chains
--		binaryCarryChainIn : in STD_LOGIC;
--		binaryCarryChainOut : out STD_LOGIC;
--		bcdCarryChainIn : in STD_LOGIC;
--		bcdCarryChainOut : out STD_LOGIC; 

-- ALU has two carry outputs: one from the adder, one from the shifter.
-- C flag will have a MUX to select one, driven by microcode
-- Adder and shifter both take C input from the same ALU input

-- Adder carryIn is carryIn for stage 0, 0 for later stages
-- Adder carry chain inputs are 0 for stage 0, previous stage output for later stages

entity ALU is
	port (
		inRegA : in STD_LOGIC_VECTOR(31 downto 0);
		inRegB : in STD_LOGIC_VECTOR(31 downto 0);
		inOperand : in STD_LOGIC_VECTOR(31 downto 0);
		N : in STD_LOGIC_VECTOR(1 downto 0);
		bitNum : in STD_LOGIC_VECTOR(4 downto 0);
		inCarry : in STD_LOGIC;
		ASel : in MC.ALUASel_t;
		BSel : in MC.ALUBSel_t;
		CSel : in MC.CSel_t;
		shiftSel : in MC.ShiftSel_t;
		shifterRight : in STD_LOGIC;
		shifterRotate : in STD_LOGIC;
		shifterRotateWord : in STD_LOGIC;
		shifterExtend : in STD_LOGIC;
		invertB_in : in STD_LOGIC;
		conditionalInvertB : in STD_LOGIC;	-- 0: invertB_in used directly.  1: invertB if negative
		signForEXT : in STD_LOGIC;			-- 0: sign is bit 7/15/31/31.    1: sign is bit 0/7/15/15
		decimal : in STD_LOGIC;
		flagsFromB : in STD_LOGIC;
		size : in STD_LOGIC_VECTOR(1 downto 0);
		op : in MC.ALUOp_t;

		result : out STD_LOGIC_VECTOR(31 downto 0);
		outAdderC : out STD_LOGIC;
		outShifterC : out STD_LOGIC;
		outZ : out STD_LOGIC;
		outV : out STD_LOGIC;
		outN : out STD_LOGIC
	);
end ALU;

architecture Structural of ALU is
	-- ALU inputs, selected from the various sources
	signal valA : STD_LOGIC_VECTOR(31 downto 0);
	signal valB : STD_LOGIC_VECTOR(31 downto 0);

	-- internal connections
	signal shiftedB : STD_LOGIC_VECTOR(31 downto 0);
	signal invertedB : STD_LOGIC_VECTOR(31 downto 0);

	-- shift amount, selected from the various sources
	signal shift : STD_LOGIC_VECTOR(4 downto 0);

	-- carry in, selected from the various sources
	signal c : STD_LOGIC;

	-- carries for each nybble of the adder.  Most of the
	-- inputs are constant 0, most of the outputs are ignored
	signal adderCarryOut : STD_LOGIC_VECTOR(7 downto 0);

	-- internal connection for the carry chains.  Element -1
	-- of each is set to '0'
	signal adderBinaryCarryChain : STD_LOGIC_VECTOR(8 downto 0);
	signal adderBinaryCarryIn : STD_LOGIC_VECTOR(8 downto 0);
	signal adderDecimalCarryChain : STD_LOGIC_VECTOR(8 downto 0);

	-- Select for input A MUX
	-- 000: reg    001: operand
	-- 010: 0      011: ffffff00
	-- 100: ffff0000
	signal aMuxSel : STD_LOGIC_VECTOR(2 downto 0);

	-- Select for input B MUX
	-- 00: reg    01: operand
	-- 10: N      11: constant 1
	signal bMuxSel : STD_LOGIC_VECTOR(1 downto 0);

	-- Sign of B input.  Depends on size.
	signal signB : STD_LOGIC;
	signal invertB : STD_LOGIC;

	-- N+1 for shift amount
	signal nPlusOne : STD_LOGIC_VECTOR(4 downto 0);

	signal result_int : STD_LOGIC_VECTOR(31 downto 0);
begin
	flags_inst : entity work.ALU_FLAGS
		port map (
			A => valA,
			B => valB,
			result => result_int,
			size => size,
			flagsFromB => flagsFromB,
	
			outZ => outZ,
			outV => outV,
			outN => OutN
		);

	-- select valB
	-- Need B = 1 for creating bitmasks
	with N & BSel select valB <=
		inRegB      when "00000" | "01000" | "10000" | "11000",		-- Reg
		inRegA      when "00100" | "01100" | "10100" | "11100",		-- RegA
		inOperand   when "00001" | "01001" | "10001" | "11001",		-- Operand
		x"00000001" when "00010",
		x"00000002" when "01010",
		x"00000003" when "10010",
		x"00000004" when "11010",	-- N
		x"00000001" when "00011" | "01011" | "10011" | "11011",		-- Constant 1
		inRegB when others;

	with signForEXT & size select signB <=
		valB(0)  when "100",
		valB(7)  when "000" | "101",
		valB(15) when "001" | "110" | "111",
		valB(31) when others;

	with conditionalInvertB select invertB <=
		invertB_in	when '0',
		signB 		when '1',
		signB		when others;

	-- Select for input A MUX
	-- 000: reg			001: operand
	-- 010: 0			011: fffffffe
	-- 100: ffffff00	101: ffff0000
	with ASel & signB & size select aMuxSel <=
		"000" when "00000" | "00001" | "00010" | "00011" | "00100" | "00101" | "00110" | "00111",
		"001" when "01000" | "01001" | "01010" | "01011" | "01100" | "01101" | "01110" | "01111",
		"010" when "10000" | "10001" | "10010" | "10011" | "10100" | "10101" | "10110" | "10111",
		"010" when "11000" | "11001" | "11010" | "11011",
		"011" when "11100",
		"100" when "11101",
		"101" when "11110" | "11111";

	-- select valA
	with aMuxSel select valA <=
		inRegA      when "000",
		inOperand   when "001",
		x"00000000" when "010",
		x"fffffffe" when "011",
		x"ffffff00" when "100",
		x"ffff0000" when "101",
		x"ffff0000" when others;

	with N select nPlusOne <=
		"00001" when "00",
		"00010" when "01",
		"00011" when "10",
		"00100" when "11",
		"00100" when others;

	-- select shift
	with shiftSel select shift <=
		bitNum when MC.ShiftSel_BitNum,
		inOperand(4 downto 0) when MC.ShiftSel_Operand,
		inRegA(4 downto 0) when MC.ShiftSel_RegA,
		nPlusOne when MC.ShiftSel_N,
		"00000" when MC.ShiftSel_0,
		"00001" when MC.ShiftSel_1,
		inRegB(4 downto 0) when MC.ShiftSel_RegB,
		"00001" when others;

	-- select C
	c <=
		'0' when CSel = MC.CSel_0 and op = MC.ALUOp_add else
		'1' when CSel = MC.CSel_1 and op = MC.ALUOp_add else
		inCarry when CSel = MC.CSel_C and op = MC.ALUOp_add else
		signB when CSel = MC.CSel_Sign and op = MC.ALUOp_add else
		'0';

	-- instantiate shifter
	Shifter_inst : entity work.SHIFTER
		port map (
			input => valB,
			cIn => inCarry,
			amount => shift,
			size => size,

			shiftRight => shifterRight,
			rotate => shifterRotate,
			rotateWord => shifterRotateWord,
			extend => shifterExtend,

			result => shiftedB,
			cOut => outShifterC
		);
	-- instantiate inverter
	InverterGen: for i in 0 to 7 generate
		Invert4x : entity work.INVERT4
			port map (
				input => shiftedB(4*i+3 downto 4*i),
				invert => invertB,
				decimal => decimal,

				result => invertedB(4*i+3 downto 4*i)
			);
	end generate;
	-- instantiate adder
	adderDecimalCarryChain(0) <= '0';
	adderBinaryCarryIn(0) <= '0';
	Adder40 : entity work.ADDER4
		port map (
			inputA => valA(3 downto 0),
			inputB => invertedB(3 downto 0),
			op => op,
			decimal => decimal,

			binaryCarryChainIn => c,
			binaryCarryChainOut => adderBinaryCarryChain(1),

			bcdCarryChainIn => '0',
			bcdCarryChainOut => adderDecimalCarryChain(1),

			result => result_int(3 downto 0),
			carryOut => adderCarryOut(0)
		);
	AdderGen: for i in 1 to 7 generate
		adderBinaryCarryIn(i) <= adderBinaryCarryChain(i) or AdderDecimalCarryChain(i);
		Adder4x : entity work.ADDER4
			port map (
				inputA => valA(4*i+3 downto 4*i),
				inputB => invertedB(4*i+3 downto 4*i),
				op => op,
				decimal => decimal,

				binaryCarryChainIn => adderBinaryCarryIn(i),
				binaryCarryChainOut => adderBinaryCarryChain(i+1),

				bcdCarryChainIn => '0',
				bcdCarryChainOut => adderDecimalCarryChain(i+1),

				result => result_int(4*i+3 downto 4*i),
				carryOut => adderCarryOut(i)
			);
	end generate;

	-- flags logic
	with size select outAdderC <=
		adderCarryOut(1) when "00",
		adderCarryOut(3) when "01",
		adderCarryOut(7) when "10",
		adderCarryOut(7) when "11",
		adderCarryOut(7) when others;

	result <= result_int;
end Structural;
