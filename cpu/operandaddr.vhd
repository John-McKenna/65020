library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity OPERANDADDR is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		memReadData : in STD_LOGIC_VECTOR(15 downto 0);
		operandAddrLoad : in STD_LOGIC;
		operandAddrExtend : in STD_LOGIC;
		operandAddrExtendFromOperand : in STD_LOGIC;
		operand : in STD_LOGIC_VECTOR(15 downto 0);
		opcode : in STD_LOGIC_VECTOR(15 downto 0);
		cycle : in STD_LOGIC_VECTOR(2 downto 0);
		pcValue : in STD_LOGIC_VECTOR(31 downto 0);

		operandAddrOut : out STD_LOGIC_VECTOR(31 downto 0)
	);
end OPERANDADDR;

architecture Behavioural of OPERANDADDR is
	signal operandAddr_int : STD_LOGIC_VECTOR(31 downto 0);
	signal isBranch : boolean := false;
	signal isIndirect : boolean := false;
	signal branchOffsetLong : boolean := false;
	signal branchOffset : STD_LOGIC_VECTOR(31 downto 0);
	signal shortBranchOffset : STD_LOGIC_VECTOR(15 downto 0);
	signal s : STD_LOGIC;
	signal s8 : STD_LOGIC_VECTOR(7 downto 0);
	signal s16 : STD_LOGIC_VECTOR(15 downto 0);
begin
	process( cpuClock )
	begin
		if rising_edge(cpuClock) then
			if operandAddrLoad = '1' and dmaActive = '0' then
				operandAddr_int <= x"0000" & memReadData;
			end if;
			if operandAddrExtend = '1' and dmaActive = '0' then
				operandAddr_int <= memReadData(15 downto 8) & operandAddr_int(15 downto 8) & memReadData(7 downto 0) & operandAddr_int(7 downto 0);
			end if;
			if operandAddrExtendFromOperand = '1' and dmaActive = '0' then
				operandAddr_int <= memReadData(15 downto 8) & operand(15 downto 8) & memReadData(7 downto 0) & operand(7 downto 0);
			end if;
		end if;
	end process;

	isBranch <= opcode(4 downto 0) = "10000";
	isIndirect <= opcode(13) = '1';
	branchOffsetLong <= opcode(14) = '1';

	-- short branches:
	-- 0040 -> 0040 -> 00000040
	-- 00c0 -> ffc0 -> ffffffc0
	-- ff40 -> ff40 -> ffffff40
	-- ffc0 -> 00c0 -> 000000c0
	s <= operandAddr_int(7);
	s8 <= s & s & s & s & s & s & s & s;
	shortBranchOffset <= (s8 xor operandAddr_int(15 downto 8)) & operandAddr_int(7 downto 0);
	s16 <=
		x"0000" when shortBranchOffset(15) = '0' else
		x"ffff";
	branchOffset <=
		operandAddr_int when branchOffsetLong else
		s16 & shortBranchOffset;

	operandAddrOut <= 
		STD_LOGIC_VECTOR(unsigned(branchOffset) + unsigned(pcValue)) when isBranch and not isIndirect and (cycle = "010" or cycle = "011" or cycle = "110") else
		operandAddr_int;
end Behavioural;
-- width 20
