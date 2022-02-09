library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

-- When opcodeLoad is active, the output is taken directly from memReadData
-- This is so microcode and nanocode can latch addresses built from it

entity OPCODE_REG is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		memReadData : in STD_LOGIC_VECTOR(15 downto 0);
		opcodeLoad : in STD_LOGIC;
		startIRQ : in STD_LOGIC;
		reset : in STD_LOGIC;

		opcodeOut : out STD_LOGIC_VECTOR(15 downto 0);
		nextOpcode : out STD_LOGIC_VECTOR(15 downto 0)
	);
end OPCODE_REG;

architecture Behavioural of OPCODE_REG is
	signal opcode_int : STD_LOGIC_VECTOR(15 downto 0) := x"0000";
begin
	process( cpuClock )
	begin
		if rising_edge(cpuClock) and opcodeLoad = '1' and dmaActive = '0' then
			if startIRQ = '1' or reset = '1' then
				opcode_int <= x"0000";
			else
				opcode_int <= memReadData;
			end if;
		end if;
	end process;

	nextOpcode <=
		x"0000" when startIRQ = '1' else
		opcode_int when opcodeLoad = '0' else
		memReadData;
	opcodeOut <= opcode_int;

end Behavioural;
-- width 17
