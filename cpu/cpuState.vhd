library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;
use work.CPU.all;

entity CPUSTATE is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		lastCycle : in STD_LOGIC;

		-- Interrupts
		requestIRQ : in STD_LOGIC;
		flagI : in STD_LOGIC;
		startIRQ : out STD_LOGIC;
		handleIRQ : out STD_LOGIC;

		-- Reset
		requestReset : in STD_LOGIC;
		finishedReset : in STD_LOGIC;
		inReset : out STD_LOGIC
	);
end CPUSTATE;

architecture Behavioural of CPUSTATE is
	signal inReset_int : STD_LOGIC := '0';
	signal startIRQ_int : STD_LOGIC := '0';
	signal handleIRQ_int : STD_LOGIC := '0';
begin
	process (cpuClock)
	begin
		if rising_edge(cpuClock) and dmaActive = '0' then
			if requestReset = '1' then
				inReset_int <= '1';
			elsif finishedReset = '1' then
				inReset_int <= '0';
			end if;
			if startIRQ_int = '1' then
				handleIRQ_int <= '1';
			elsif lastCycle = '1' then
				handleIRQ_int <= '0';
			end if;

		end if;
	end process;

	inReset <= inReset_int;
	startIRQ_int <= lastCycle and requestIRQ and not flagI;
	startIRQ <= startIRQ_int;
	handleIRQ <= handleIRQ_int;

end Behavioural;
-- width 16
