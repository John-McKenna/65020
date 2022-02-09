-- Generated file --
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

package MC is
	subtype CSel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant CSel_0 : CSel_t := "00";
	constant CSel_1 : CSel_t := "01";
	constant CSel_C : CSel_t := "10";
	constant CSel_Sign : CSel_t := "11";

	subtype ShiftSel_t is STD_LOGIC_VECTOR(2 downto 0);
	constant ShiftSel_0 : ShiftSel_t := "000";
	constant ShiftSel_BitNum : ShiftSel_t := "001";
	constant ShiftSel_Operand : ShiftSel_t := "010";
	constant ShiftSel_RegA : ShiftSel_t := "011";
	constant ShiftSel_N : ShiftSel_t := "100";
	constant ShiftSel_1 : ShiftSel_t := "101";
	constant ShiftSel_RegB : ShiftSel_t := "110";

	subtype ALUOp_t is STD_LOGIC_VECTOR(2 downto 0);
	constant ALUOp_add : ALUOp_t := "000";
	constant ALUOp_and : ALUOp_t := "001";
	constant ALUOp_or : ALUOp_t := "010";
	constant ALUOp_eor : ALUOp_t := "011";
	constant ALUOp_inB : ALUOp_t := "101";

	subtype DefaultReg_t is STD_LOGIC_VECTOR(2 downto 0);
	constant DefaultRegA0 : DefaultReg_t := "000";
	constant DefaultRegX0 : DefaultReg_t := "001";
	constant DefaultRegY0 : DefaultReg_t := "010";
	constant DefaultRegP : DefaultReg_t := "011";
	constant DefaultRegSP : DefaultReg_t := "100";
	constant DefaultRegPC : DefaultReg_t := "101";

	subtype RegMod_t is STD_LOGIC_VECTOR(2 downto 0);
	constant RegMod_None : RegMod_t := "000";
	constant RegMod_13_14 : RegMod_t := "001";
	constant RegMod_13_15 : RegMod_t := "010";
	constant RegMod_8_11 : RegMod_t := "011";
	constant RegMod_10_13 : RegMod_t := "100";
	constant RegMod_10_12 : RegMod_t := "101";
	constant RegMod_11_14 : RegMod_t := "110";
	constant RegMod_MOV : RegMod_t := "111";

	subtype DefaultIndex_t is STD_LOGIC_VECTOR(2 downto 0);
	constant DefaultIndexA0 : DefaultIndex_t := "000";
	constant DefaultIndexX0 : DefaultIndex_t := "001";
	constant DefaultIndexY0 : DefaultIndex_t := "010";
	constant DefaultIndexP : DefaultIndex_t := "011";
	constant DefaultIndexPC : DefaultIndex_t := "100";
	constant DefaultIndexSP : DefaultIndex_t := "101";

	subtype IndexMod_t is STD_LOGIC_VECTOR(1 downto 0);
	constant IndexMod_None : IndexMod_t := "00";
	constant IndexMod_10_12 : IndexMod_t := "01";
	constant IndexMod_8_11 : IndexMod_t := "10";
	constant IndexMod_MOV : IndexMod_t := "11";

	subtype BitNum_t is STD_LOGIC_VECTOR(2 downto 0);
	constant BitNum_0 : BitNum_t := "000";
	constant BitNum_2 : BitNum_t := "010";
	constant BitNum_3 : BitNum_t := "011";
	constant BitNum_6 : BitNum_t := "110";

	subtype FlagWrite_t is STD_LOGIC_VECTOR(4 downto 0);
	constant FlagWrite_C : FlagWrite_t := "00001";
	constant FlagWrite_Z : FlagWrite_t := "00010";
	constant FlagWrite_V : FlagWrite_t := "00100";
	constant FlagWrite_N : FlagWrite_t := "01000";
	constant FlagWrite_NZ : FlagWrite_t := "01010";
	constant FlagWrite_CNZ : FlagWrite_t := "01011";
	constant FlagWrite_NVZ : FlagWrite_t := "01110";
	constant FlagWrite_CNVZ : FlagWrite_t := "01111";
	constant FlagWrite_ShifterC : FlagWrite_t := "10000";
	constant FlagWrite_SCNZ : FlagWrite_t := "11010";
	constant FlagWrite_SCNVZ : FlagWrite_t := "11110";

	subtype MulDivOp_t is STD_LOGIC_VECTOR(1 downto 0);
	constant MulDivOp_Mul : MulDivOp_t := "00";
	constant MulDivOp_Div : MulDivOp_t := "01";
	constant MulDivOp_Mod : MulDivOp_t := "10";

	subtype DataWidthSel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant DataWidthSel_8 : DataWidthSel_t := "00";
	constant DataWidthSel_16 : DataWidthSel_t := "01";
	constant DataWidthSel_32 : DataWidthSel_t := "10";
	constant DataWidthSel_8_9 : DataWidthSel_t := "11";

	subtype ALUASel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant AluASel_Reg : ALUASel_t := "00";
	constant AluASel_Operand : ALUASel_t := "01";
	constant AluASel_0 : ALUASel_t := "10";
	constant AluASel_Sign : ALUASel_t := "11";

	subtype ALUBSel_t is STD_LOGIC_VECTOR(2 downto 0);
	constant AluBSel_Reg : ALUBSel_t := "000";
	constant AluBSel_Operand : ALUBSel_t := "001";
	constant AluBSel_N : ALUBSel_t := "010";
	constant AluBSel_One : ALUBSel_t := "011";
	constant AluBSel_RegA : ALUBSel_t := "100";

	subtype AddressInputSel_t is STD_LOGIC_VECTOR(2 downto 0);
	constant AddressInputSel_PC : AddressInputSel_t := "000";
	constant AddressInputSel_SP : AddressInputSel_t := "001";
	constant AddressInputSel_AluOut : AddressInputSel_t := "010";
	constant AddressInputSel_Vector : AddressInputSel_t := "011";
	constant AddressInputSel_OperandAddrIndexed : AddressInputSel_t := "100";
	constant AddressInputSel_OperandAddr : AddressInputSel_t := "101";

	subtype MemWriteDataSel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant MemWriteDataSel_RegAOutL : MemWriteDataSel_t := "00";
	constant MemWriteDataSel_RegAOutH : MemWriteDataSel_t := "01";
	constant MemWriteDataSel_ALUOutL : MemWriteDataSel_t := "10";
	constant MemWriteDataSel_ALUOutH : MemWriteDataSel_t := "11";

	subtype CycleCond_t is STD_LOGIC_VECTOR(2 downto 0);
	constant CycleCond_Never : CycleCond_t := "000";
	constant CycleCond_Always : CycleCond_t := "001";
	constant CycleCond_BaseAddr16 : CycleCond_t := "010";
	constant CycleCond_Data16 : CycleCond_t := "011";
	constant CycleCond_Branch : CycleCond_t := "100";
	constant CycleCond_MulDivRunning : CycleCond_t := "101";

	subtype CycleJump_t is STD_LOGIC_VECTOR(2 downto 0);
	constant CycleJump0 : CycleJump_t := "000";
	constant CycleJump1 : CycleJump_t := "001";
	constant CycleJump2 : CycleJump_t := "010";
	constant CycleJump3 : CycleJump_t := "011";
	constant CycleJump4 : CycleJump_t := "100";
	constant CycleJump5 : CycleJump_t := "101";
	constant CycleJump6 : CycleJump_t := "110";
	constant CycleJump7 : CycleJump_t := "111";

	subtype RegASel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant RegASel_PC : RegASel_t := "00";
	constant RegASel_P : RegASel_t := "01";
	constant RegASel_Reg : RegASel_t := "10";
	constant RegASel_Operand : RegASel_t := "11";

	subtype RegBSel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant RegBSel_Reg : RegBSel_t := "00";
	constant RegBSel_Index : RegBSel_t := "01";
	constant RegBSel_Zero : RegBSel_t := "10";
	constant RegBSel_Operand : RegBSel_t := "11";

	subtype RegWriteSel_t is STD_LOGIC_VECTOR(1 downto 0);
	constant RegWriteSel_Alu : RegWriteSel_t := "00";
	constant RegWriteSel_MulDiv : RegWriteSel_t := "01";
	constant RegWriteSel_Data : RegWriteSel_t := "10";

	subtype MemWriteWidth_t is STD_LOGIC_VECTOR(1 downto 0);
	constant MemWriteWidth_8 : MemWriteWidth_t := "00";
	constant MemWriteWidth_16 : MemWriteWidth_t := "01";
	constant MemWriteWidth_32 : MemWriteWidth_t := "10";
	constant MemWriteWidth_D : MemWriteWidth_t := "11";

end package;
