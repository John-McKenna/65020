library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity REGADDR is
	port (
		defaultReg : in MC.DefaultReg_t;
		regMod : in MC.RegMod_t;
		regIndex : out STD_LOGIC_VECTOR(3 downto 0);
		opcode : in STD_LOGIC_VECTOR(15 downto 0);

		defaultIndex : in MC.DefaultIndex_t;
		indexMod : in MC.IndexMod_t;
		indexIndex : out STD_LOGIC_VECTOR(3 downto 0)
	);
end REGADDR;

architecture Behavioural of REGADDR is
	signal regBase : STD_LOGIC_VECTOR(3 downto 0);
	signal regXor : STD_LOGIC_VECTOR(3 downto 0);
	signal indexBase : STD_LOGIC_VECTOR(3 downto 0);
	signal indexXor : STD_LOGIC_VECTOR(3 downto 0);
begin
	with defaultReg select regBase <=
		STD_LOGIC_VECTOR(to_unsigned(CPU.regA0,4)) when MC.DefaultRegA0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regX0,4)) when MC.DefaultRegX0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regY0,4)) when MC.DefaultRegY0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) when MC.DefaultRegP,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4)) when MC.DefaultRegSP,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regPC,4)) when MC.DefaultRegPC,
		"0000" when others;

	with regMod select regXor <=
		"0000" when MC.RegMod_None,
		"00" & opcode(14 downto 13) when MC.RegMod_13_14,
		'0' & opcode(15 downto 13) when MC.RegMod_13_15,
		opcode(11 downto 8) when MC.RegMod_8_11,
		opcode(13 downto 10) when MC.RegMod_10_13,
		'0' & opcode(12 downto 10) when MC.RegMod_10_12,
		opcode(14 downto 11) when MC.RegMod_11_14,
		opcode(15) & '0' & opcode(14 downto 13) when MC.RegMod_MOV,
		"0000" when others;

	with defaultIndex select indexBase <=
		STD_LOGIC_VECTOR(to_unsigned(CPU.regA0,4)) when MC.DefaultIndexA0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regX0,4)) when MC.DefaultIndexX0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regY0,4)) when MC.DefaultIndexY0,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) when MC.DefaultIndexP,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4)) when MC.DefaultIndexSP,
		STD_LOGIC_VECTOR(to_unsigned(CPU.regPC,4)) when MC.DefaultIndexPC,
		"0000" when others;

	with indexMod select indexXor <=
		"0000" when MC.IndexMod_None,
		"0" & opcode(12 downto 10) when MC.IndexMod_10_12,
		opcode(11 downto 8) when MC.IndexMod_8_11,
		opcode(12) & '0' & opcode(11 downto 10) when MC.IndexMod_MOV,
		"0000" when others;

	regIndex <= regBase xor regXor;
	indexIndex <= indexBase xor indexXor;
end Behavioural;
-- width 17
