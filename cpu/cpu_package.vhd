library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

package CPU is
	constant regA0 : integer := 0;
	constant regA1 : integer := 1;
	constant regA2 : integer := 2;
	constant regA3 : integer := 3;

	constant regX0 : integer := 4;
	constant regX1 : integer := 5;
	constant regX2 : integer := 6;
	constant regX3 : integer := 7;

	constant regY0 : integer := 8;
	constant regY1 : integer := 9;
	constant regY2 : integer := 10;
	constant regY3 : integer := 11;

	constant regP : integer := 12;
	constant regZ : integer := 13;
	constant regSP : integer := 14;
	constant regPC : integer := 15;

	constant regP_C : integer := 0;
	constant regP_Z : integer := 1;
	constant regP_I : integer := 2;
	constant regP_D : integer := 3;
	constant regP_B : integer := 4;
	constant regP_V : integer := 6;
	constant regP_N : integer := 7;
end package;
