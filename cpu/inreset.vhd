library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity IN_RESET is
	port (
		cpuClock : in boolean;
		dmaActive : in STD_LOGIC;
		set : in boolean;
		reset : in boolean;

		inResetOut : out boolean;
	);
end IN_RESET;

architecture Behavioural of IN_RESET is
	signal inReset_int : boolean := true;
begin
	process ( cpuClock )
		if rising_edge(cpuClock) and dmaActive = '0' then
			if set then
				inReset_int <= true;
			end if;
			if reset then
				inReset_int <= false;
			end if;
		end if;
	end process;

	inRestOut <= inReset_int;
end Behavioural;
