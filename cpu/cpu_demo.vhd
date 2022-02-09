library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity CPU_Demo is
end CPU_Demo;

architecture Behavioural of CPU_Demo is
	signal cpuClock : STD_LOGIC;
	signal cpuAddress : STD_LOGIC_VECTOR(31 downto 0);
	signal cpuWriteData : STD_LOGIC_VECTOR(15 downto 0);
	signal cpuWriteEnable : STD_LOGIC;
	signal cpuWrite8 : STD_LOGIC;
	signal cpuReadData : STD_LOGIC_VECTOR(15 downto 0);
	signal reset : STD_LOGIC := '1';

	signal memAddr : integer;

	constant ramSize : integer := 8192;
	constant romSize : integer := 16;
	constant romBase : integer := 65536 - romSize;

	type ramArray is array(0 to 2*ramSize-1) of STD_LOGIC_VECTOR(7 downto 0);
	type romArray is array(0 to romSize-1) of STD_LOGIC_VECTOR(15 downto 0);
	signal RAM : ramArray := ( others => x"00");
	signal ROM : romArray := (
		x"00a9",	-- ldr.b a0, #1
		x"0001",
		x"0085",	-- str.b a0, 2
		x"0002",
		x"004c",	-- jmp $fff0
		x"00f0",
		x"00ff",
		x"0000",
		x"0000",
		x"0000",
		x"0000",
		x"0000",
		x"00f0",	-- reset vector $fff0
		x"00ff",
		x"0000",
		x"0000"
	);
begin
	CPU_INST : entity work.CPUMain
		port map (
			cpuClock => cpuClock,
			cpuAddress => cpuAddress,
			cpuWriteData => cpuWriteData,
			cpuWriteEnable => cpuWriteEnable,
			cpuWrite8 => cpuWrite8,
			cpuReadData => cpuReadData,
			dmaActive => '0',
			requestIRQ => '0',
			reset => reset,

			debugRegisterIndex => "0000"
		);
	resetProcess : process
	begin
		wait for 1us;
		reset <= '0';
	end process;

	memReadProcess : process(cpuAddress, cpuWriteEnable, cpuClock)
	begin
		memAddr <= to_integer(unsigned(cpuAddress));
		if cpuWriteEnable = '0' then
			if memAddr < ramSize then
				cpuReadData(7 downto 0) <= RAM(2*memAddr);
				cpuReadData(15 downto 8) <= RAM(2*memAddr+1);
			end if;
			if memAddr >= romBase and memAddr < 65536 then
				cpuReadData <= ROM(memAddr-romBase);
			end if;
		end if;
	end process;

	memWriteProcess : process(cpuClock, cpuWriteEnable)
	begin
		if rising_edge(cpuClock) and cpuWriteEnable = '1' then
			if memAddr < ramSize then
				RAM(2*memAddr) <= cpuWriteData(7 downto 0);
				if cpuWrite8 = '1' then
					RAM(2*memAddr+1) <= cpuWriteData(15 downto 8);
				end if;
			end if;
		end if;
	end process;

	clock : process
	begin
		cpuClock <= '0';
		wait for 200ns;
		cpuClock <= '1';
		wait for 200ns;
	end process;
end Behavioural;
