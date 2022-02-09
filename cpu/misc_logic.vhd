library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;
use work.CPU.all;

entity MISC_LOGIC is
	port (
		opcode : in STD_LOGIC_VECTOR(15 downto 0);

		-- Modify ALU controls for NEG/ABS/EXT instructions
		negAbsExtNot : in STD_LOGIC;

		aluOpIn : in MC.ALUOp_t;
		aluASelIn : in MC.ALUASel_t;
		aluBSelIn : in MC.ALUBSel_t;
		aluInvertBIn : in STD_LOGIC;
		aluConditionalInvertBIn : in STD_LOGIC;
		aluCSelIn : in MC.CSel_t;

		aluOpOut : out MC.ALUOp_t;
		aluASelOut : out MC.ALUASel_t;
		aluBSelOut : out MC.ALUBSel_t;
		aluInvertBOut : out STD_LOGIC;
		aluConditionalInvertBOut : out STD_LOGIC;
		aluCSelOut : out MC.CSel_t;
		aluSignForExtOut : out STD_LOGIC;

		-- Modify ALU shift input for RMW imm instructions
		aluShiftSelOperandOrReg : in STD_LOGIC;
		aluShiftSelIn : in MC.ShiftSel_t;
		aluShiftSelOut : out MC.ShiftSel_t;

		-- Disable decimal mode if op is not ADD
		aluDecimalIn : in STD_LOGIC;
		aluDecimalOut : out STD_LOGIC;

		-- Data width
		dataWidthSel : in MC.DataWidthSel_t;
		dataWidth : out STD_LOGIC_VECTOR(1 downto 0);

		-- Memory write data source
		memWriteDataSelIn : in MC.MemWriteDataSel_t;
		memWriteDataSelOut : out MC.MemWriteDataSel_t;

		-- BitNum
		bitNumIn : in STD_LOGIC_VECTOR(2 downto 0);
		bitNumOut : out STD_LOGIC_VECTOR(4 downto 0)
	);
end MISC_LOGIC;

architecture Structural of MISC_LOGIC is
	signal negAbsExtNot_14_13 : STD_LOGIC_VECTOR(2 downto 0);
	signal aluShiftSelOperandOrReg_14 : STD_LOGIC_VECTOR(1 downto 0);
	signal bitNumMod : STD_LOGIC_VECTOR(4 downto 0);
	signal dataWidth_int : STD_LOGIC_VECTOR(1 downto 0);
begin
	negAbsExtNot_14_13 <= negAbsExtNot & opcode(14) & opcode(13);
	with negAbsExtNot_14_13 select aluOpOut <=
		aluOpIn when "000" | "001" | "010" | "011",
		MC.ALUOp_add when "100",
		MC.ALUOp_add when "101",
		MC.ALUOp_or when "110",
		MC.ALUOp_add when "111",
		MC.ALUOp_add when others;

	with negAbsExtNot_14_13 select aluASelOut <=
		aluASelIn when "000" | "001" | "010" | "011",
		MC.AluASel_0 when "100",			-- NEG
		MC.AluASel_0 when "101",			-- ABS
		MC.AluASel_Sign when "110",		-- EXT
		MC.AluASel_0 when "111",			-- NOT
		MC.AluASel_0 when others;

	with negAbsExtNot_14_13 select aluBSelOut <=
		aluBSelIn when "000" | "001" | "010" | "011",
		MC.AluBSel_RegA when "100",		-- NEG
		MC.AluBSel_RegA when "101",		-- ABS
		MC.AluBSel_RegA when "110",		-- EXT
		MC.AluBSel_RegA when "111",		-- NOT
		MC.AluBSel_Reg when others;

	with negAbsExtNot_14_13 select aluInvertBOut <=
		aluInvertBIn when "000" | "001" | "010" | "011",
		'1' when "100",
		'0' when "101",
		'0' when "110",
		'1' when "111",
		'0' when others;

	with negAbsExtNot_14_13 select aluConditionalInvertBOut <=
		aluConditionalInvertBIn when "000" | "001" | "010" | "011",
		'0' when "100",
		'1' when "101",
		'0' when "110",
		'0' when "111",
		'0' when others;

	with negAbsExtNot_14_13 select aluCSelOut <=
		aluCSelIn when "000" | "001" | "010" | "011",
		MC.CSel_1 when "100",
		MC.CSel_Sign when "101",
		MC.CSel_0 when "110",
		MC.CSel_0 when "111",
		MC.CSel_0 when others;

	with negAbsExtNot_14_13 select aluSignForExtOut <=
		'0' when "000" | "001" | "010" | "011",
		'0' when "100",
		'0' when "101",
		'1' when "110",
		'0' when "111",
		'0' when others;

	-- aluShiftSelOperandOrReg:
	--   0 means always use operand
	--   1 means use operand or register, depending on opcode(14)
	-- opcode(14)
	--   0 means following byte is immediate
	--   1 means following byte is register index
	aluShiftSelOperandOrReg_14 <= aluShiftSelOperandOrReg & opcode(14);
	with aluShiftSelOperandOrReg_14 select aluShiftSelOut <=
		aluShiftSelIn when "00" | "01",
		MC.ShiftSel_Operand when "10",
		MC.ShiftSel_RegB when "11",
		MC.ShiftSel_Operand when others;

	with aluOpIn select aluDecimalOut <=
		aluDecimalIn when MC.ALUOp_add,
		'0' when others;

	with dataWidthSel select dataWidth_int <=
		"10" when MC.DataWidthSel_32,
		opcode(9 downto 8) when MC.DataWidthSel_8_9,
		opcode(9 downto 8) when others;
	dataWidth <= dataWidth_int;

	bitNumMod <= opcode(14) & opcode(13) & opcode(12) & opcode(12) & opcode(12);
	bitNumOut <= ("00" & bitNumIn) xor bitNumMod;

	memWriteDataSelOut <=
		MC.MemWriteDataSel_RegAOutL when dataWidth_int(1) = '0' and memWriteDataSelIn = MC.MemWriteDataSel_RegAOutH else
		MC.MemWriteDataSel_ALUOutL when dataWidth_int(1) = '0' and memWriteDataSelIn = MC.MemWriteDataSel_ALUOutH else
		memWriteDataSelIn;

end Structural;
-- width 25
