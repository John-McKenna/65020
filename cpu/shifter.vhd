library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity SHIFTER is
	port (
		input : in STD_LOGIC_VECTOR(31 downto 0);
		cIn : in STD_LOGIC;
		amount : in STD_LOGIC_VECTOR(4 downto 0);
		size : in STD_LOGIC_VECTOR(1 downto 0);

		-- 0 means shift left, 1 means shift right
		shiftRight : in STD_LOGIC;
		-- 0 means fill (0 or extend), 1 means rotate
		rotate : in STD_LOGIC;
		-- 0 means n+1 bit rotate, 1 means n bit rotate (when rotate is 1)
		rotateWord : in STD_LOGIC;
		-- 0 means shift in 0, 1 means extend left/right-most bit (when rotate is 0)
		extend : in STD_LOGIC;

		result : out STD_LOGIC_VECTOR(31 downto 0);
		cOut : out STD_LOGIC
	);
end SHIFTER;

architecture Behavioural of SHIFTER is
	signal source   : STD_LOGIC_VECTOR(31 downto 0);	signal ext  : STD_LOGIC_VECTOR(31 downto 0);
	signal shifted0 : STD_LOGIC_VECTOR(31 downto 0);	signal ext0 : STD_LOGIC_VECTOR(31 downto 0);	signal c0 : STD_LOGIC;
	signal shifted1 : STD_LOGIC_VECTOR(31 downto 0);	signal ext1 : STD_LOGIC_VECTOR(31 downto 0);	signal c1 : STD_LOGIC;
	signal shifted2 : STD_LOGIC_VECTOR(31 downto 0);	signal ext2 : STD_LOGIC_VECTOR(31 downto 0);	signal c2 : STD_LOGIC;
	signal shifted3 : STD_LOGIC_VECTOR(31 downto 0);	signal ext3 : STD_LOGIC_VECTOR(31 downto 0);	signal c3 : STD_LOGIC;
	signal shifted4 : STD_LOGIC_VECTOR(31 downto 0);													signal c4 : STD_LOGIC;

	signal output   : STD_LOGIC_VECTOR(31 downto 0);	signal resultC : STD_LOGIC;

	signal fill : STD_LOGIC;

	signal extSelect : STD_LOGIC_VECTOR(1 downto 0);
	signal stage0Select : STD_LOGIC_VECTOR(1 downto 0);
	signal stage1Select : STD_LOGIC_VECTOR(1 downto 0);
	signal stage2Select : STD_LOGIC_VECTOR(1 downto 0);
	signal stage3Select : STD_LOGIC_VECTOR(1 downto 0);
	signal stage4Select : STD_LOGIC_VECTOR(1 downto 0);

	signal c0Select : STD_LOGIC_VECTOR(2 downto 0);
	signal c1Select : STD_LOGIC_VECTOR(2 downto 0);
	signal c2Select : STD_LOGIC_VECTOR(2 downto 0);
	signal c3Select : STD_LOGIC_VECTOR(2 downto 0);
	signal c4Select : STD_LOGIC_VECTOR(2 downto 0);

	signal resultSelect : STD_LOGIC_VECTOR(1 downto 0);
	signal alignedResult : STD_LOGIC_VECTOR(15 downto 0);

begin
	-- source is left-aligned (for right shifts) or right-aligned (for right shifts) copy of the input
	-- ext is a copy of source shifted one place with C inserted for ROL and ROR, with the opposite alignment
	--   or all fill.  Fill is 0, source bit 0, source bit 7, source bit 15, source bit 31

	-- Each stage of the shifter takes the concatenation of source and ext and either passes it through,
	-- or shifts it left or right.

	-- duplicating the input for smaller sizes is done so that it is
	-- aligned regardless of the shift direction.
	source(7 downto 0) <= input(7 downto 0);
	source(31 downto 8) <=
		input(31 downto 8) when size = "10" else
		input(31 downto 8) when size = "11" else
		input(15 downto 0) & input(15 downto 8) when size = "01" else
		input(7 downto 0) & input(7 downto 0) & input(7 downto 0) when size = "00";

	fill <=
		'0'       when extend = '0' else
		input(0)  when extend = '1' and shiftRight = '0' else
		input(7)  when extend = '1' and shiftRight = '1' and size = "00" else
		input(15) when extend = '1' and shiftRight = '1' and size = "01" else
		input(31) when extend = '1' and shiftRight = '1' and size = "10" else
		'0';

	extSelect(0) <= rotate and (rotateWord or shiftRight);
	extSelect(1) <= rotate and (not rotateWord);
	-- rotate	rotateWord	shiftRight	|	sel1	sel0
	--	0		0			0			|	0		0		D
	--	0		0			1			|	0		0		D
	--	0		1			0			|	0		0		D
	--	0		1			1			|	0		0		D
	--	1		0			0			|	1		0		A
	--	1		0			1			|	1		1		B
	--	1		1			0			|	0		1		C
	--	1		1			1			|	0		1		C
	with extSelect select ext <=
		(others => fill) when "00",
		source when "01",
		CIn & source(31 downto 1) when "10",
		source(30 downto 0) & CIn when "11",
		source(30 downto 0) & CIn when others;

	stage0Select <= amount(4) & shiftRight;
	stage1Select <= amount(3) & shiftRight;
	stage2Select <= amount(2) & shiftRight;
	stage3Select <= amount(1) & shiftRight;
	stage4Select <= amount(0) & shiftRight;

	with stage0Select select shifted0 <=
		source                                  when "00",
		source                                  when "01",
		source(15 downto 0) & ext(31 downto 16) when "10",
		ext(15 downto 0) & source(31 downto 16) when "11",
		ext(15 downto 0) & source(31 downto 16) when others;
	with stage0Select select ext0 <=
		ext                         when "00",
		ext                         when "01",
		ext(15 downto 0) & x"0000"  when "10",
		x"0000" & ext(31 downto 16) when "11",
		x"0000" & ext(31 downto 16) when others;
	-- shiftRight	size1	size0	|
	-- 0			0		0		|	A
	-- 0			0		1		|	B
	-- 0			1		0		|	C
	-- 0			1		1		|	-
	-- 1			0		0		|	D
	-- 1			0		1		|	E
	-- 1			1		0		|	F
	-- 1			1		1		|	cIn
	c0Select(0) <= (not amount(4)) or size(0);
	c0Select(1) <= (not amount(4)) or size(1);
	c0Select(2) <= (not amount(4)) or shiftRight;
	with c0Select select c0 <=
		source(0)  when "000",
		source(0)  when "001",
		source(16) when "010",
		source(16) when "011",
		source(31) when "100",
		source(31) when "101",
		source(15) when "110",
		CIn        when "111",
		CIn        when others;

	with stage1Select select shifted1 <=
		shifted0                                   when "00",
		shifted0                                   when "01",
		shifted0(23 downto 0) & ext0(31 downto 24) when "10",
		ext0(7 downto 0) & shifted0(31 downto 8)   when "11",
		ext0(7 downto 0) & shifted0(31 downto 8)   when others;
	with stage1Select select ext1 <=
		ext0                           when "00",
		ext0                           when "01",
		ext0(23 downto 16) & x"000000" when "10",
		x"000000" & ext0(15 downto 8)  when "11",
		x"000000" & ext0(15 downto 8)  when others;
	c1Select(0) <= (not amount(3)) or size(0);
	c1Select(1) <= (not amount(3)) or size(1);
	c1Select(2) <= (not amount(3)) or shiftRight;
	with c1Select select c1 <=
		shifted0(0)  when "000",
		shifted0(8)  when "001",
		shifted0(24) when "010",
		shifted0(24) when "011",
		shifted0(31) when "100",
		shifted0(23) when "101",
		shifted0(7)  when "110",
		c0         when "111",
		c0         when others;

	with stage2Select select shifted2 <=
		shifted1                                   when "00",
		shifted1                                   when "01",
		shifted1(27 downto 0) & ext1(31 downto 28) when "10",
		ext1(3 downto 0) & shifted1(31 downto 4)   when "11",
		ext1(3 downto 0) & shifted1(31 downto 4)   when others;
	with stage2Select select ext2 <=
		ext1                            when "00",
		ext1                            when "01",
		ext1(27 downto 24) & x"0000000" when "10",
		x"0000000" & ext1(7 downto 4)   when "11",
		x"0000000" & ext1(7 downto 4)   when others;
	c2Select(0) <= (not amount(2)) or size(0);
	c2Select(1) <= (not amount(2)) or size(1);
	c2Select(2) <= (not amount(2)) or shiftRight;
	with c2Select select c2 <=
		shifted1(4)  when "000",
		shifted1(12) when "001",
		shifted1(28) when "010",
		shifted1(28) when "011",
		shifted1(27) when "100",
		shifted1(19) when "101",
		shifted1(3)  when "110",
		c1         when "111",
		c1         when others;

	with stage3Select select shifted3 <=
		shifted2                                   when "00",
		shifted2                                   when "01",
		shifted2(29 downto 0) & ext2(31 downto 30) when "10",
		ext2(1 downto 0) & shifted2(31 downto 2)   when "11",
		ext2(1 downto 0) & shifted2(31 downto 2)   when others;
	with stage3Select select ext3 <=
		ext2                                   when "00",
		ext2                                   when "01",
		ext2(29 downto 28) & "00" & x"0000000" when "10",
		"00" & x"0000000" & ext2(3 downto 2)   when "11",
		"00" & x"0000000" & ext2(3 downto 2)   when others;
	c3Select(0) <= (not amount(1)) or size(0);
	c3Select(1) <= (not amount(1)) or size(1);
	c3Select(2) <= (not amount(1)) or shiftRight;
	with c3Select select c3 <=
		shifted2(6)  when "000",
		shifted2(14) when "001",
		shifted2(30) when "010",
		shifted2(30) when "011",
		shifted2(25) when "100",
		shifted2(17) when "101",
		shifted2(1)  when "110",
		c2         when "111",
		c2         when others;

	with stage4Select select shifted4 <=
		shifted3                                   when "00",
		shifted3                                   when "01",
		shifted3(30 downto 0) & ext3(31 downto 31) when "10",
		ext3(0 downto 0) & shifted3(31 downto 1)   when "11",
		ext3(0 downto 0) & shifted3(31 downto 1)   when others;
	c4Select(0) <= (not amount(0)) or size(0);
	c4Select(1) <= (not amount(0)) or size(1);
	c4Select(2) <= (not amount(0)) or shiftRight;
	with c4Select select c4 <=
		shifted3(7)  when "000",
		shifted3(15) when "001",
		shifted3(31) when "010",
		shifted3(31) when "011",
		shifted3(24) when "100",
		shifted3(16) when "101",
		shifted3(0)  when "110",
		c3         when "111",
		c3         when others;

	-- shiftRight	size1	size0	|	sel1	sel0
	-- 0			0		0		|	0		1			shifted4(15 downto 0)
	-- 0			0		1		|	1		1			shifted4(15 downto 0)
	-- 0			1		0		|	0		1			shifted4(15 downto 0)
	-- 0			1		1		|	1		1			shifted4(15 downto 0)
	-- 1			0		0		|	0		0			x"00" & shifted4(31 downto 24)
	-- 1			0		1		|	1		0			shifted4(31 downto 16)
	-- 1			1		0		|	0		1			shifted4(15 downto 0)
	-- 1			1		1		|	1		1			shifted4(15 downto 0)
	resultSelect(0) <= not shiftRight or size(1);
	resultSelect(1) <= size(0);
	with resultSelect select alignedResult <=
		x"00" & shifted4(31 downto 24) when "00",
		shifted4(15 downto 0)          when "01",
		shifted4(31 downto 16)         when "10",
		shifted4(15 downto 0)          when "11",
		shifted4(15 downto 0)          when others;

	output(31 downto 16) <= shifted4(31 downto 16);
	output(15 downto 8) <= alignedResult(15 downto 8);
	output(7 downto 0) <= alignedResult(7 downto 0);

	result <= output;
	COut <= c4;

end Behavioural;
-- width 13
