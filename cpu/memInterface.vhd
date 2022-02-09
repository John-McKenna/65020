library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity MEM_INTERFACE is
	port (
		writeDataSel : in MC.MemWriteDataSel_t;
		data16 : in STD_LOGIC;
		regAData : in STD_LOGIC_VECTOR(31 downto 0);
		aluData : in STD_LOGIC_VECTOR(31 downto 0);

		memWriteData : out STD_LOGIC_VECTOR(15 downto 0)
	);
end MEM_INTERFACE;

architecture Behavioural of MEM_INTERFACE is
begin
	with data16 & writeDataSel select memWriteData <=
		regAData(15 downto 0) when '1' & MC.MemWriteDataSel_RegAOutL,
		regAData(31 downto 16) when '1' & MC.MemWriteDataSel_RegAOutH,	-- shouldn't happen
		aluData(15 downto 0) when '1' & MC.MemWriteDataSel_ALUOutL,
		aluData(31 downto 16) when '1' & MC.MemWriteDataSel_ALUOutH,	-- shouldn't happen
		regAData(23 downto 16) & regAData(7 downto 0) when '0' & MC.MemWriteDataSel_RegAOutL,
		regAData(31 downto 24) & regAData(15 downto 8) when '0' & MC.MemWriteDataSel_RegAOutH,
		aluData(23 downto 16) & aluData(7 downto 0) when '0' & MC.MemWriteDataSel_ALUOutL,
		aluData(31 downto 24) & aluData(15 downto 8) when '0' & MC.MemWriteDataSel_ALUOutH,
		aluData(31 downto 16) when others;

end Behavioural;
-- width 19
