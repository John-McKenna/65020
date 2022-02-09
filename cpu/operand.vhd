library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity OPERAND is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		memReadData : in STD_LOGIC_VECTOR(15 downto 0);
		operandLoad : in STD_LOGIC;
		operandExtend : in STD_LOGIC;

		operandOut : out STD_LOGIC_VECTOR(31 downto 0)
	);
end OPERAND;

architecture Behavioural of OPERAND is
	signal operand_int : STD_LOGIC_VECTOR(31 downto 0);
begin
	process( cpuClock )
	begin
		if rising_edge(cpuClock) then
			if operandLoad = '1' and dmaActive = '0' then
				operand_int <= x"0000" & memReadData;
			end if;
			if operandExtend = '1' and dmaActive = '0' then
				operand_int <= memReadData(15 downto 8) & operand_int(15 downto 8) & memReadData(7 downto 0) & operand_int(7 downto 0);
			end if;
		end if;
	end process;

	operandOut <= operand_int;
end Behavioural;
-- width 17
