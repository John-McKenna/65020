library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

-- Add, AND, OR, or EOR two four bit values.  If the operation is 'Add',
-- 'decimal' is 1, and the result is greater than 9 or carry out is 1,
-- then add an extra 6.

entity ADDER4 is
	port (
		-- inputs
		inputA : in STD_LOGIC_VECTOR(3 downto 0);
		inputB : in STD_LOGIC_VECTOR(3 downto 0);
		op : in MC.ALUOp_t;
		decimal : in STD_LOGIC;

		-- carry chains
		binaryCarryChainIn : in STD_LOGIC;
		binaryCarryChainOut : out STD_LOGIC;

		bcdCarryChainIn : in STD_LOGIC;
		bcdCarryChainOut : out STD_LOGIC; 

		-- outputs
		result : out STD_LOGIC_VECTOR(3 downto 0);
		carryOut : out STD_LOGIC
	);
end ADDER4;

architecture Behavioural of ADDER4 is
	signal binaryResult : STD_LOGIC_VECTOR(3 downto 0);
	signal binaryOutput : STD_LOGIC_VECTOR(3 downto 0);
	signal binaryGenerate : STD_LOGIC_VECTOR(3 downto 0);

	signal bcdResult : STD_LOGIC_VECTOR(3 downto 0);
	signal bcdOutput : STD_LOGIC_VECTOR(3 downto 0);
	signal bcdGenerate : STD_LOGIC_VECTOR(3 downto 0);

	signal binaryCarryOut : STD_LOGIC_VECTOR(3 downto 0);
	signal bcdCarryOut : STD_LOGIC_VECTOR(3 downto 0);

	signal doCorrection : STD_LOGIC;

	type BCDCorrectionLogicArray is array (0 to 3) of BIT_VECTOR(63 downto 0);
	constant bcdCorrectionLogic : BCDCorrectionLogicArray := (
		x"aaaaaaaa00000000",
		x"aaa6aaaa00080000",
		x"aaa6aaaa00080000",
		x"aaaaaaaa00000000"
	);
begin
	Adder4Generate:
	for i in 0 to 3 generate
		-- Binary adder
		GenPropx : LUT6_2
			generic map (
				-- low 32 bits are O5 'generate'
				-- high 32 bits are O6 'result'
				-- op:
				--   000 add		100 add
				--   001 and		101 inB
				--   010 or			110 ---
				--   011 eor		111 ---
				-- gen:res O5:O6
				--   BA add and or  eor add inB --- ---
				--   00	0:0 0:0 0:0 0:0 0:0 0:0 0:0 0:0
				--   01	0:1 0:0 0:1 0:1 0:1 0:0 0:0 0:0
				--   10	0:1 0:0 0:1 0:1 0:1 0:1 0:0 0:0
				--   11	1:0 0:1 0:1 0:0 1:0 0:1 0:0 0:0
				-- O6: 0000 0000 1100 0110 0110 1110 1000 0110  00c66e86
				-- O5: 0000 0000 0000 1000 0000 0000 0000 1000  00080008
				INIT => x"00c66e8600080008"
			)
			port map (
				I0 => inputA(i),
				I1 => inputB(i),
				I2 => op(0),
				I3 => op(1),
				I4 => op(2),
				I5 => '1',
	
				O5 => binaryGenerate(i),
				O6 => binaryResult(i)
			);
		-- BCD correction
		BCDCorrectionx : LUT6_2
			generic map (
				-- low 32 bits are O5 'generate'
				-- high 32 bits are O6 'propagate'
				-- both op = 000 and 100 are "add", and the
				-- others don't do correction.  So we only
				-- need to look at op(0) and op(1)
				INIT => bcdCorrectionLogic(i)
			)
			port map (
				I0 => binaryOutput(i),
				I1 => doCorrection,
				I2 => op(0),
				I3 => op(1),
				I4 => decimal,
				I5 => '1',
	
				O5 => bcdGenerate(i),
				O6 => bcdResult(i)
			);
	end generate Adder4Generate;

	DoCorrectionLogic : LUT5
		generic map (
			INIT => x"fffffc00"	-- 0 to 9 -> 0, 10 to 31 -> 1
		)
		port map (
			I0 => binaryOutput(0),
			I1 => binaryOutput(1),
			I2 => binaryOutput(2),
			I3 => binaryOutput(3),
			I4 => binaryCarryOut(3),

			O => doCorrection
		);

	-- Binary adder
	Carries : CARRY4
		port map (
			CI => binaryCarryChainIn,
			DI => binaryGenerate,
			S => binaryResult,

			CO => binaryCarryOut,
			O => binaryOutput
		);
	-- BCD correction
	BCDCarries : CARRY4
		port map (
			CI => bcdCarryChainIn,
			DI => bcdGenerate,
			S => bcdResult,

			CO => bcdCarryOut,
			O => bcdOutput
		);

	binaryCarryChainOut <= binaryCarryOut(3);
	bcdCarryChainOut <= bcdCarryOut(3);

	result <= bcdOutput;
	carryOut <= bcdCarryOut(3) or binaryCarryOut(3);

end Behavioural;

-- width 19
