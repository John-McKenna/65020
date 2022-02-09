-- Generated file --
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity NANOCODE is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		opcode : in STD_LOGIC_VECTOR(15 downto 0);
		memReadData : in STD_LOGIC_VECTOR(15 downto 0);
		opcodeLoadEn : in STD_LOGIC;
		cycle : in STD_LOGIC_VECTOR(2 downto 0);
		reset : in STD_LOGIC;

		ALUASel : out MC.ALUASel_t;
		ALUBSel : out MC.ALUBSel_t;
		PCInc : out STD_LOGIC;
		AddressInputSel : out MC.AddressInputSel_t;
		MemWriteDataSel : out MC.MemWriteDataSel_t;
		WriteEnable : out STD_LOGIC;
		SPLoad : out STD_LOGIC;
		SPInc : out STD_LOGIC;
		SPDec : out STD_LOGIC;
		OperandLoad : out STD_LOGIC;
		OperandExtend : out STD_LOGIC;
		OperandAddrLoad : out STD_LOGIC;
		OperandAddrExtend : out STD_LOGIC;
		OperandAddrExtendFromOperand : out STD_LOGIC;
		AddressInc : out STD_LOGIC;
		PCLoad : out STD_LOGIC;
		OpcodeLoad : out STD_LOGIC;
		CycleCond : out MC.CycleCond_t;
		CycleJump : out MC.CycleJump_t;
		RegASel : out MC.RegASel_t;
		RegBSel : out MC.RegBSel_t;
		RegWriteSel : out MC.RegWriteSel_t;
		RegWriteEnable : out STD_LOGIC;
		FlagsWriteEnable : out STD_LOGIC;
		MemWriteWidth : out MC.MemWriteWidth_t;
		RegBIsIndex : out STD_LOGIC;
		RunMulDiv : out STD_LOGIC;
		SetI : out STD_LOGIC;
		SetB : out STD_LOGIC;
		ExitReset : out STD_LOGIC
	);
end NANOCODE;

architecture Structural of NANOCODE is
	signal addr : STD_LOGIC_VECTOR(7 downto 0) := x"00";
	signal addr0 : STD_LOGIC_VECTOR(13 downto 0);
	signal addr1 : STD_LOGIC_VECTOR(13 downto 0);
	signal raw_data : STD_LOGIC_VECTOR(63 downto 0);
	signal data : STD_LOGIC_VECTOR(63 downto 0);
	signal enabled : STD_LOGIC;
begin
	ROUTINE_INST_0 : RAM256X1S
		generic map ( INIT => x"fa6efc78f26ef0787276f07000040002fa7efd79fa6eec68fe7efd78fa6eec69" )
		port map ( A => opcode(7 downto 0), O => addr(3), D => '0', WE => '0', WCLK => '0' );
	ROUTINE_INST_1 : RAM256X1S
		generic map ( INIT => x"aba4beb1a324b2317374f275f274f0f2ebe4eae5ebe4eae5efe4faf5ebe4eae4" )
		port map ( A => opcode(7 downto 0), O => addr(4), D => '0', WE => '0', WCLK => '0' );
	ROUTINE_INST_2 : RAM256X1S
		generic map ( INIT => x"414741424147454201070002f275f17201170113011701130107010201070103" )
		port map ( A => opcode(7 downto 0), O => addr(5), D => '0', WE => '0', WCLK => '0' );
	ROUTINE_INST_3 : RAM256X1S
		generic map ( INIT => x"4145414041454540050505008507058041454444414544444145444441454445" )
		port map ( A => opcode(7 downto 0), O => addr(6), D => '0', WE => '0', WCLK => '0' );
	ROUTINE_INST_4 : RAM256X1S
		generic map ( INIT => x"4040454040404540040005000500058000101111001011110000010100000100" )
		port map ( A => opcode(7 downto 0), O => addr(7), D => '0', WE => '0', WCLK => '0' );
	ROM_INST : RAMB16BWER
		generic map (
			SIM_DEVICE => "SPARTAN6",
			DATA_WIDTH_A => 36,
			DATA_WIDTH_B => 36,

			INIT_00 => x"0000000000000000000000000000000000000000000000000000000000c00020",		-- routine 0	Illegal
			INIT_01 => x"0000000000000020000000000000000000000000000000000000000000000000",
			INIT_02 => x"00000000000000000000000000000000000000000000000000000018c0c00020",		-- routine 1	M_Acc
			INIT_03 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_04 => x"00000000000000000000001840c0002400000000000100200000000009808020",		-- routine 2	M_Imm
			INIT_05 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_06 => x"0000008080110100000000809180810000000000000400200000000009020020",		-- routine 3	M_BI
			INIT_07 => x"0000000000000000000000000000000000000000000000000000001840c00024",
			INIT_08 => x"0000000015808140000000808018010000000080800081000000000000020020",		-- routine 4	M_ZPX
			INIT_09 => x"000000000000000000000000000000000000001840c000240000000000110140",
			INIT_0A => x"0000008095808100000000000018014000000000000081400000000000020020",		-- routine 5	M_ZPY
			INIT_0B => x"000000000000000000000000000000000000001840c000240000008080110100",
			INIT_0C => x"000000e0d1900b00000000e0d180090000000000000400200000000009020020",		-- routine 6	S_BI
			INIT_0D => x"0000000000000000000000000000000000000000000000000000000000c00020",
			INIT_0E => x"0000006055800940000000808018010000000080800081000000000000020020",		-- routine 7	S_ZPX
			INIT_0F => x"000000000000000000000000000000000000000000c000200000006051900b40",
			INIT_10 => x"000000e0d5800900000000000018014000000000000081400000000000020020",		-- routine 8	S_ZPY
			INIT_11 => x"000000000000000000000000000000000000000000c00020000000e0c0100b00",
			INIT_12 => x"0000000000000000000000000000000000000000000000000000001840c00020",		-- routine 9	RMW_Acc
			INIT_13 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_14 => x"0000000000000000000000000000000000000019c0c000300000000000008020",		-- routine 10	RMW_Imm
			INIT_15 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_16 => x"0000008080110100000000809180810000000000000400200000000009020020",		-- routine 11	RMW_BI
			INIT_17 => x"00000000000000000000000000c00020000000e080100f04000000f099800d04",
			INIT_18 => x"0000008082180100000000808200810000000000020400200000000002020020",		-- routine 12	Branch
			INIT_19 => x"0000000000c000200000008080e00160000000c102004c40000000c102004e40",
			INIT_1A => x"00000000000200c0000000202000484000000040000048400000044000004a40",		-- routine 13	BRK
			INIT_1B => x"00000000000000000000080000c00020000002000020014000000000001400c0",
			INIT_1C => x"0000000000000000000000000000000000000000000000000000001840c0002c",		-- routine 14	BSR_Acc
			INIT_1D => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_1E => x"0000008080110100000000808000810000000000000400200000000009020020",		-- routine 15	BSR_BI
			INIT_1F => x"00000000000000000000000000c00020000000e080100f0d000000f080000d0d",
			INIT_20 => x"00000000000000000000000000e0016000000000000400200000000000020020",		-- routine 16	JMP_Abs
			INIT_21 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_22 => x"0000000000180140000000000000814000000000000400200000000000020020",		-- routine 17	JMP_Ind
			INIT_23 => x"0000000000000000000000000000000000000000000000000000000000e00160",
			INIT_24 => x"000000000004000000000040000048400000004000004a400000000000020020",		-- routine 18	JSR_Abs
			INIT_25 => x"0000000000000000000000000000000000000000000000000000000000e00160",
			INIT_26 => x"0000000000000000000000000000000000000000000000000000000000c00020",		-- routine 19	NOP
			INIT_27 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_28 => x"00000000000000000000000000c0002000000060400048400000006049804a40",		-- routine 20	PHA
			INIT_29 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_2A => x"00000000000000000000001840c000240000000000112040000000000990a040",		-- routine 21	PLA
			INIT_2B => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_2C => x"0000000000e00160000000000014204000000000001220400000000c20102040",		-- routine 22	RTI
			INIT_2D => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_2E => x"0000000000c00020000000000030014000000000001420400000000000122040",		-- routine 23	RTS
			INIT_2F => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_30 => x"00000000000000000000000000000000000000000000000000000018c0c00020",		-- routine 24	MOV
			INIT_31 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_32 => x"0000000000000000000000000000000000000000000000000000000000000000",		-- routine 25	MD_ACC
			INIT_33 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_34 => x"0000001a40c00020000001004a80000400000000000100200000000009808020",		-- routine 26	MD_IMM
			INIT_35 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_36 => x"0000000000000000000000000000000000000000000000000000000000000000",		-- routine 27	MD_BI
			INIT_37 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_38 => x"0000000000000000000000000000000000000000000000000000001840c00028",		-- routine 28	ID_Acc
			INIT_39 => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_3A => x"0000008080110100000000809180810000000000000400200000000009020020",		-- routine 29	ID_BI
			INIT_3B => x"00000000000000000000000000c00020000000e080100f09000000f099800d09",
			INIT_3C => x"0000000000000000000000000000000000000000000000000000000000000000",		-- routine 30	
			INIT_3D => x"0000000000000000000000000000000000000000000000000000000000000000",
			INIT_3E => x"0000000000000000000000000000000000000000000000000000000000000000",		-- routine 31	
			INIT_3F => x"0000000000000000000000000000000000000000000000000000000000000000"
		)
		port map (
			ADDRA => addr0,
			ADDRB => addr1,

			DOA => raw_data(31 downto 0),
			DOB => raw_data(63 downto 32),

			DIA => x"00000000",
			DIB => x"00000000",
			DIPA => "0000",
			DIPB => "0000",
			WEA => "0000",
			WEB => "0000",
			ENA => enabled,
			ENB => enabled,
			CLKA => cpuClock,
			CLKB => cpuClock,
			RSTA => '0',
			RSTB => '0',
			REGCEA => '0',
			REGCEB => '0'
		);

	addr(2 downto 0) <= cycle;
	addr0 <= addr & "000000";
	addr1 <= addr & "100000";

	data <=
		raw_data when reset = '0' else
		x"0000000000000000";

	ALUASel <= data(1 downto 0);
	ALUBSel <= data(4 downto 2);
	PCInc <= data(5);
	AddressInputSel <= data(8 downto 6);
	MemWriteDataSel <= data(10 downto 9);
	WriteEnable <= data(11);
	SPLoad <= data(12);
	SPInc <= data(13);
	SPDec <= data(14);
	OperandLoad <= data(15);
	OperandExtend <= data(16);
	OperandAddrLoad <= data(17);
	OperandAddrExtend <= data(18);
	OperandAddrExtendFromOperand <= data(19);
	AddressInc <= data(20);
	PCLoad <= data(21);
	OpcodeLoad <= data(22);
	CycleCond <= data(25 downto 23);
	CycleJump <= data(28 downto 26);
	RegASel <= data(30 downto 29);
	RegBSel <= data(32 downto 31);
	RegWriteSel <= data(34 downto 33);
	RegWriteEnable <= data(35);
	FlagsWriteEnable <= data(36);
	MemWriteWidth <= data(38 downto 37);
	RegBIsIndex <= data(39);
	RunMulDiv <= data(40);
	SetI <= data(41);
	SetB <= data(42);
	ExitReset <= data(43);

	enabled <= not dmaActive;
end Structural;
-- width 23