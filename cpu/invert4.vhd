library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

-- 			binary	decimal
--	0000    1111    1001
--	0001    1110    1000
--	0010    1101    0111
--	0011    1100    0110

--	0100    1011    0101
--	0101    1010    0100
--	0110    1001    0011
--	0111    1000    0010

--	1000    0111    0001
--	1001    0110    0000
--	1010    0101    1111
--	1011    0100    1110

--	1100    0011    1101
--	1101    0010    1100
--	1110    0001    1011
--	1111    0000    1010

-- Bottom two bits of output depend on bottom two bits of input, invert, decimal
-- Top two bits don't depend on bottom bit, so they need top 3, invert, decimal

entity INVERT4 is
	port (
		-- inputs
		input : in STD_LOGIC_VECTOR(3 downto 0);
		invert : in STD_LOGIC;
		decimal : in STD_LOGIC;

		-- outputs
		result : out STD_LOGIC_VECTOR(3 downto 0)
	);
end INVERT4;

architecture Behavioural of INVERT4 is
begin
	LowBits : LUT6_2
		generic map (
			INIT => x"0c0c030c050a050a"
		)
		port map (
			I0 => input(0),
			I1 => input(1),
			I2 => '0',
			I3 => invert,
			I4 => decimal,
			I5 => '1',

			O5 => result(0),
			O6 => result(1)
		);
	HighBits : LUT6_2
		generic map (
			INIT => x"e1f00ff066cc33cc"
		)
		port map (
			I0 => input(1),
			I1 => input(2),
			I2 => input(3),
			I3 => invert,
			I4 => decimal,
			I5 => '1',

			O5 => result(2),
			O6 => result(3)
		);
end Behavioural;
-- width 12
