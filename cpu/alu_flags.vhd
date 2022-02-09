library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;
use work.CPU.all;

entity ALU_FLAGS is
	port (
		A : in STD_LOGIC_VECTOR(31 downto 0);
		B : in STD_LOGIC_VECTOR(31 downto 0);
		result : in STD_LOGIC_VECTOR(31 downto 0);
		size : in STD_LOGIC_VECTOR(1 downto 0);
		flagsFromB : in STD_LOGIC;

		outZ : out STD_LOGIC;
		outV : out STD_LOGIC;
		outN : out STD_LOGIC
	);
end ALU_FLAGS;

architecture Structural of ALU_FLAGS is
	signal N_alu : STD_LOGIC := '0';
	signal N_B : STD_LOGIC := '0';

	signal Z0_5 : STD_LOGIC := '0';
	signal Z6_7 : STD_LOGIC := '0';
	signal Z8_13 : STD_LOGIC := '0';
	signal Z14_15 : STD_LOGIC := '0';
	signal Z16_21 : STD_LOGIC := '0';
	signal Z22_27 : STD_LOGIC := '0';
	signal Z28_31 : STD_LOGIC := '0';
	signal Z8 : STD_LOGIC := '0';
	signal Z16H : STD_LOGIC := '0';
	signal Z32H : STD_LOGIC := '0';

	signal V8 : STD_LOGIC := '0';
	signal V16 : STD_LOGIC := '0';
	signal VA32 : STD_LOGIC := '0';
	signal VB32 : STD_LOGIC := '0';
	signal V_alu : STD_LOGIC := '0';
	signal V_B : STD_LOGIC := '0';

	signal N : STD_LOGIC := '0';
	signal V : STD_LOGIC := '0';
	signal Z : STD_LOGIC := '0';

begin
	N_ALU_LUT : LUT5
		-- SS012			SS012			SS012			SS012
		-- 00000 0			01000 0			10000 0			11000 0
		-- 00001 1			01001 0			10001 0			11001 0
		-- 00010 0			01010 1			10010 0			11010 0
		-- 00011 1			01011 1			10011 0			11011 0
		-- 00100 0			01100 0			10100 1			11100 1
		-- 00101 1			01101 0			10101 1			11101 1
		-- 00110 0			01110 1			10110 1			11110 1
		-- 00111 1			01111 1			10111 1			11111 1
		generic map ( INIT => x"f0f0ccaa" )
		port map (
			I0 => result(7),
			I1 => result(15),
			I2 => result(31),
			I3 => size(0),
			I4 => size(1),
			O => N_alu
		);
	N_B_LUT : LUT5
		generic map ( INIT => x"f0f0ccaa" )
		port map (
			I0 => B(7),
			I1 => B(15),
			I2 => B(31),
			I3 => size(0),
			I4 => size(1),
			O => N_B
		);
	N_LUT : MUXF7
		port map (
			I0 => N_alu,
			I1 => N_B,
			S => flagsFromB,
			O => N
		);
	Z0_5_LUT : LUT6
		-- O = I0 + I1 + I2 + I3 + I4 + I5
		generic map ( INIT => x"fffffffffffffffe" )
		port map (
			I0 => result(0),
			I1 => result(1),
			I2 => result(2),
			I3 => result(3),
			I4 => result(4),
			I5 => result(5),
			O => Z0_5
		);
	Z6_7_LUT : LUT6_2
		-- O5 = I0 + I1
		-- O6 = I2^I1 & I3^I1
		-- BA76 5 6		BA76 5 6
		-- 0000	0 0		1000 0 0
		-- 0001	1 0		1001 1 0
		-- 0010	1 1		1010 1 0
		-- 0011	1 1		1011 1 0
		-- 0100	0 0		1100 0 1
		-- 0101	1 0		1101 1 1
		-- 0110	1 0		1110 1 0
		-- 0111	1 0		1111 1 0
		generic map ( INIT => x"0000300c0000eeee" )
		port map (
			I0 => result(6),
			I1 => result(7),
			I2 => A(7),
			I3 => B(7),
			I4 => '0',
			I5 => '1',
			O5 => Z6_7,
			O6 => V8
		);
	Z8_13_LUT : LUT6
		generic map ( INIT => x"fffffffffffffffe" )
		port map (
			I0 => result(8),
			I1 => result(9),
			I2 => result(10),
			I3 => result(11),
			I4 => result(12),
			I5 => result(13),
			O => Z8_13
		);
	Z14_15_LUT : LUT6_2
		generic map ( INIT => x"0000300c0000eeee" )
		port map (
			I0 => result(14),
			I1 => result(15),
			I2 => A(15),
			I3 => B(15),
			I4 => '0',
			I5 => '1',
			O5 => Z14_15,
			O6 => V16
		);
	Z16_21_LUT : LUT6
		generic map ( INIT => x"fffffffffffffffe" )
		port map (
			I0 => result(16),
			I1 => result(17),
			I2 => result(18),
			I3 => result(19),
			I4 => result(20),
			I5 => result(21),
			O => Z16_21
		);
	Z22_27_LUT : LUT6
		generic map ( INIT => x"fffffffffffffffe" )
		port map (
			I0 => result(22),
			I1 => result(23),
			I2 => result(24),
			I3 => result(25),
			I4 => result(26),
			I5 => result(27),
			O => Z22_27
		);
	Z28_31_LUT : LUT6_2
		-- Z28_31 = I0 + I1 + I2 + I3
		-- VA32 = I4 ^ I3
		-- A3210 5 6		A3210 5 6		A3210 5 6		A3210 5 6
		-- 00000 0 0		01000 1 1		10000 0 1		11000 1 0
		-- 00001 1 0		01001 1 1		10001 1 1		11001 1 0
		-- 00010 1 0		01010 1 1		10010 1 1		11010 1 0
		-- 00011 1 0		01011 1 1		10011 1 1		11011 1 0
		-- 00100 1 0		01100 1 1		10100 1 1		11100 1 0
		-- 00101 1 0		01101 1 1		10101 1 1		11101 1 0
		-- 00110 1 0		01110 1 1		10110 1 1		11110 1 0
		-- 00111 1 0		01111 1 1		10111 1 1		11111 1 0
		generic map ( INIT => x"00ffff00fffefffe" )
		port map (
			I0 => result(28),
			I1 => result(29),
			I2 => result(30),
			I3 => result(31),
			I4 => A(31),
			I5 => '1',
			O5 => Z28_31,
			O6 => VA32
		);
	Z8_LUT : LUT6_2
		-- O5 = I0 + I1
		-- O6 = I2 + I3
		-- 0000	0 0		1000 0 1
		-- 0001	1 0		1001 1 1
		-- 0010	1 0		1010 1 1
		-- 0011	1 0		1011 1 1
		-- 0100	0 1		1100 0 1
		-- 0101	1 1		1101 1 1
		-- 0110	1 1		1110 1 1
		-- 0111	1 1		1111 1 1
		generic map ( INIT => x"0000fff00000eeee" )
		port map (
			I0 => Z0_5,
			I1 => Z6_7,
			I2 => Z8_13,
			I3 => Z14_15,
			I4 => '0',
			I5 => '1',
			O5 => Z8,
			O6 => Z16H
		);
	Z32H_LUT : LUT6_2
		-- O5 = I0 + I1 + I2
		-- O6 = I3 ^ I4
		-- BR210 5 6		BR210 5 6		BR210 5 6		BR210 5 6
		-- 00000 0 0		01000 0 1		10000 0 1		11000 0 0
		-- 00001 1 0		01001 1 1		10001 1 1		11001 1 0
		-- 00010 1 0		01010 1 1		10010 1 1		11010 1 0
		-- 00011 1 0		01011 1 1		10011 1 1		11011 1 0
		-- 00100 1 0		01100 1 1		10100 1 1		11100 1 0
		-- 00101 1 0		01101 1 1		10101 1 1		11101 1 0
		-- 00110 1 0		01110 1 1		10110 1 1		11110 1 0
		-- 00111 1 0		01111 1 1		10111 1 1		11111 1 0
		generic map ( INIT => x"00ffff00fefefefe" )
		port map (
			I0 => Z16_21,
			I1 => Z22_27,
			I2 => Z28_31,
			I3 => result(31),
			I4 => B(31),
			I5 => '1',
			O5 => Z32H,
			O6 => VB32
		);
	V_B_LUT : LUT5
		generic map ( INIT => x"f0f0ccaa" )
		port map (
			I0 => B(6),
			I1 => B(14),
			I2 => B(30),
			I3 => size(0),
			I4 => size(1),
			O => V_B
		);
	Z_LUT : LUT5
		-- SS012			SS012			SS012			SS012
		-- 00000 1			01000 1			10000 1			11000 1
		-- 00001 0			01001 0			10001 0			11001 0
		-- 00010 1			01010 0			10010 0			11010 0
		-- 00011 0			01011 0			10011 0			11011 0
		-- 00100 1			01100 1			10100 0			11100 0
		-- 00101 0			01101 0			10101 0			11101 0
		-- 00110 1			01110 0			10110 0			11110 0
		-- 00111 0			01111 0			10111 0			11111 0
		generic map ( INIT => x"01011155" )
		port map (
			I0 => Z8,
			I1 => Z16H,
			I2 => Z32H,
			I3 => size(0),
			I4 => size(1),
			O => Z
		);
	V_alu_LUT : LUT6
		-- O = I0, size = 00
		--     I1, size = 01
		--     I2 & I3, size = 10 or 11
		-- 00.0000 0			01.0000 0		10.0000 0		11.0000 0
		-- 00.0001 1			01.0001 0		10.0001 0		11.0001 0
		-- 00.0010 0			01.0010 1		10.0010 0		11.0010 0
		-- 00.0011 1			01.0011 1		10.0011 0		11.0011 0
		-- 00.0100 0			01.0100 0		10.0100 0		11.0100 0
		-- 00.0101 1			01.0101 0		10.0101 0		11.0101 0
		-- 00.0110 0			01.0110 1		10.0110 0		11.0110 0
		-- 00.0111 1			01.0111 1		10.0111 0		11.0111 0
		-- 00.1000 0			01.1000 0		10.1000 0		11.1000 0
		-- 00.1001 1			01.1001 0		10.1001 0		11.1001 0
		-- 00.1010 0			01.1010 1		10.1010 0		11.1010 0
		-- 00.1011 1			01.1011 1		10.1011 0		11.1011 0
		-- 00.1100 0			01.1100 0		10.1100 1		11.1100 1
		-- 00.1101 1			01.1101 0		10.1101 1		11.1101 1
		-- 00.1110 0			01.1110 1		10.1110 1		11.1110 1
		-- 00.1111 1			01.1111 1		10.1111 1		11.1111 1
		generic map ( INIT => x"f000f000ccccaaaa" )
		port map (
			I0 => V8,
			I1 => V16,
			I2 => VA32,
			I3 => VB32,
			I4 => size(0),
			I5 => size(1),
			O => V_alu
		);
	V_LUT : MUXF7
		port map (
			I0 => V_alu,
			I1 => V_B,
			S => flagsFromB,
			O => V
		);

	outZ <= Z;
	outV <= V;
	outN <= N;
end Structural;
