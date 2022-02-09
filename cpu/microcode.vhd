-- Generated file --
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity MICROCODE is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		opcode : in STD_LOGIC_VECTOR(15 downto 0);
		memReadData : in STD_LOGIC_VECTOR(15 downto 0);

		CSel : out MC.CSel_t;
		ShiftSel : out MC.ShiftSel_t;
		ShifterRight : out STD_LOGIC;
		ShifterRotate : out STD_LOGIC;
		ShifterRotateWord : out STD_LOGIC;
		ShifterExtend : out STD_LOGIC;
		InvertB : out STD_LOGIC;
		ConditionalInvertB : out STD_LOGIC;
		NegAbsExtNot : out STD_LOGIC;
		FlagsFromB : out STD_LOGIC;
		ShiftSelOperandOrReg : out STD_LOGIC;
		UseShifterC : out STD_LOGIC;
		ALUOp : out MC.ALUOp_t;
		DefaultReg : out MC.DefaultReg_t;
		RegMod : out MC.RegMod_t;
		DefaultIndex : out MC.DefaultIndex_t;
		IndexMod : out MC.IndexMod_t;
		BaseAddr16 : out STD_LOGIC;
		BitNum : out MC.BitNum_t;
		FlagWrite : out MC.FlagWrite_t;
		NoRegWrite : out STD_LOGIC;
		MulDivOp : out MC.MulDivOp_t;
		DataWidthSel : out MC.DataWidthSel_t;
		Illegal : out STD_LOGIC
	);
end MICROCODE;

architecture Structural of MICROCODE is
	signal romAddr : STD_LOGIC_VECTOR(13 downto 0);
	signal data : STD_LOGIC_VECTOR(63 downto 0);
	signal enabled : STD_LOGIC;
begin
	ROM_LOW_INST : RAMB16BWER
	generic map (
			SIM_DEVICE => "SPARTAN6",
			DATA_WIDTH_A => 36,
			DATA_WIDTH_B => 36,
			INIT_00 => x"00000000082500000082a1080082a00800000000092100000000000003000000",		-- 00
			INIT_01 => x"00000000002500002b0281102b028010000000002b2100000000000000000000",		-- 04
			INIT_02 => x"000000000a25000000828114008280140000000000c10000000000000d2c0000",		-- 08
			INIT_03 => x"00000000092500000b0281100b028010000000000b2100000000000000000000",		-- 0c
			INIT_04 => x"00000000082900001000800410008204000000000a2100001400020014000200",		-- 10
			INIT_05 => x"0000000000290000290281102902801000000000292100000000000000000000",		-- 14
			INIT_06 => x"000000000a2900000000000000000000000000000a210000006c8004006c8204",		-- 18
			INIT_07 => x"0000000009250000090281100902801000000000092100000000000008210000",		-- 1c
			INIT_08 => x"08248200082480000082a0c80082a0480920820009208000000000000b000000",		-- 20
			INIT_09 => x"00248200002480002b0280d02b0280502b2082002b208000000000002b209000",		-- 24
			INIT_0A => x"0a2482000a248000008280d40082805400c0820000c08000000000000d2e8000",		-- 28
			INIT_0B => x"09248200092480000b0280d00b0280500b2082000b208000000000000b209000",		-- 2c
			INIT_0C => x"082882000828800010018004100100040a2082000a2080001400020014000200",		-- 30
			INIT_0D => x"0028820000288000290280d02902805029208200292080000000000008209000",		-- 34
			INIT_0E => x"0a2882000a28800000000000092090000a2082000a208000006d8004006d0004",		-- 38
			INIT_0F => x"0928820009288000090280d00902805009208200092080000820820008208000",		-- 3c
			INIT_10 => x"00000000082580000082a1200082a0200000000009218000000000000d0c0000",		-- 40
			INIT_11 => x"00000000002580002b0281302b028030000000002b218000000000000d240000",		-- 44
			INIT_12 => x"000000000a25800000828134008280340000000000c18000000000000d200000",		-- 48
			INIT_13 => x"00000000092580000b0281300b028030000000000b2180000000000000000000",		-- 4c
			INIT_14 => x"00000000082980009000800490008204000000000a2180001400020014000200",		-- 50
			INIT_15 => x"000000000029800029028130290280300000000029218000000000000d280000",		-- 54
			INIT_16 => x"000000000a2980000000000000000000000000000a218000806c8004806c8204",		-- 58
			INIT_17 => x"0000000009298000090281300902803000000000092180000000000008218000",		-- 5c
			INIT_18 => x"08240000082400020082a0e80082a0680920000009200002000000000d000000",		-- 60
			INIT_19 => x"00240000002400022b0280f02b0280702b2000002b200002000000000d268000",		-- 64
			INIT_1A => x"0a2400000a240002008280f40082807400c0000000c00002000000000d228000",		-- 68
			INIT_1B => x"09240000092400020b0280f00b0280700b2000000b2000020000000000000000",		-- 6c
			INIT_1C => x"082800000828000290018004900100040a2000000a2000021400020014000200",		-- 70
			INIT_1D => x"0028000000280002290280f0290280702920000029200002000000000d2a8000",		-- 74
			INIT_1E => x"0a2800000a28000200000000000000000a2000000a200002806d8004806d0004",		-- 78
			INIT_1F => x"0928000009280002090280f00902807009200000092000020820000008200002",		-- 7c
			INIT_20 => x"0000000000000000000000000000000000000000092000000000000000000000",		-- 80
			INIT_21 => x"0000000000c00000000000002b440000000000002b400000000000002b480000",		-- 84
			INIT_22 => x"000000000000000019e2800019e28000000000000000000000aa880100a80201",		-- 88
			INIT_23 => x"0000000009440000000000000b440000000000000b400000000000000b480000",		-- 8c
			INIT_24 => x"00000000000000009000800490008204000000000a2000001400020014000200",		-- 90
			INIT_25 => x"0000000000000000000000002944000000000000294000000000000029480000",		-- 94
			INIT_26 => x"000000000000000019f2800019f28000000000000a4000001ae280001ae28000",		-- 98
			INIT_27 => x"806d8004806d0004000000000a44000000000000094000000000000009480000",		-- 9c
			INIT_28 => x"00000000000000000000000000268000000000000922800000000000002a8000",		-- a0
			INIT_29 => x"0000000000000000000000002b268000000000002b228000000000002b2a8000",		-- a4
			INIT_2A => x"000000000000000018e6800018e68000000000000022800018ea800018ea8000",		-- a8
			INIT_2B => x"0000000009268000000000000b268000000000000b228000000000000b2a8000",		-- ac
			INIT_2C => x"00000000000000009001800490010004000000000a2280001400020014000200",		-- b0
			INIT_2D => x"0000000000000000000000002a268000000000002922800000000000292a8000",		-- b4
			INIT_2E => x"00000000000000001de680001de68000000000000a228000806c8004806c8204",		-- b8
			INIT_2F => x"0000000000000000000000000a268000000000000922800000000000092a8000",		-- bc
			INIT_30 => x"0824020208240201000000000000000009200202092002010028020200280201",		-- c0
			INIT_31 => x"00000000000000002b0008012b0002012b2002022b2002012b2802022b280201",		-- c4
			INIT_32 => x"000000000000000000a6880100a4020100c0020200c002010000000000a80000",		-- c8
			INIT_33 => x"09240202092402010b0008010b0002010b2002020b2002010b2802020b280201",		-- cc
			INIT_34 => x"0828020208280201d0008004d00082040a2002020a2002011400020014000200",		-- d0
			INIT_35 => x"0000000000000000290008012900020129200202292002010000000000000000",		-- d4
			INIT_36 => x"000000000000000000000000000000000a2002020a200201c06c8004c06c8204",		-- d8
			INIT_37 => x"0b2802000b280201000000000900020109200202092002010820020208200201",		-- dc
			INIT_38 => x"0824020108240202000000000000000009200201092002020024020200240201",		-- e0
			INIT_39 => x"0024020100240202000000002b0000002b2002012b2002022b2402022b240201",		-- e4
			INIT_3A => x"0a2402010a240202000000000000000000c0020100c002020000000000a40000",		-- e8
			INIT_3B => x"0924020109240202000000000b0000000b2002010b2002020b2402020b240201",		-- ec
			INIT_3C => x"0828020108280202d0018004d00100040a2002010a2002021400020014000200",		-- f0
			INIT_3D => x"0028020100280202000000002900000029200201292002020000000000000000",		-- f4
			INIT_3E => x"0a2802010a28020200000000000000000a2002010a200202c06d8004c06d0004",		-- f8
			INIT_3F => x"0928020109280202000000000900000009200201092002020820020108200202"		-- fc
		)
		port map (
			ADDRA => romAddr,
			ADDRB => "00000000000000",

			DOA => data(31 downto 0),

			DIA => x"00000000",
			DIB => x"00000000",
			DIPA => "0000",
			DIPB => "0000",
			WEA => "0000",
			WEB => "0000",
			ENA => enabled,
			ENB => '0',
			CLKA => cpuClock,
			CLKB => '0',
			RSTA => '0',
			RSTB => '0',
			REGCEA => '0',
			REGCEB => '0'
		);
	ROM_HIGH_INST : RAMB16BWER
		generic map (
			SIM_DEVICE => "SPARTAN6",
			DATA_WIDTH_A => 36,
			DATA_WIDTH_B => 36,
			INIT_00 => x"0000080000000614000006340000063400000800000006140000080000000400",		-- 00
			INIT_01 => x"0000080000000614000006340000063400000800000006140000080000000800",		-- 04
			INIT_02 => x"0000080000000614000006340000063400000800000006140000080000000600",		-- 08
			INIT_03 => x"0000080000000614000006340000063400000800000006140000080000000800",		-- 0c
			INIT_04 => x"0000080000000614000004440000040000000800000006140000040000000400",		-- 10
			INIT_05 => x"0000080000000614000006340000063400000800000006140000080000000800",		-- 14
			INIT_06 => x"0000080000000614000008000000080000000800000006140000044400000400",		-- 18
			INIT_07 => x"0000080000000614000006340000063400000800000006140000080000000614",		-- 1c
			INIT_08 => x"0000061400000614000006340000063400000614000006140000080000000400",		-- 20
			INIT_09 => x"000006140000061400000634000006340000061400000614000008000000065c",		-- 24
			INIT_0A => x"0000061400000614000006340000063400000614000006140000080000000600",		-- 28
			INIT_0B => x"000006140000061400000634000006340000061400000614000008000000065c",		-- 2c
			INIT_0C => x"0000061400000614000004000000040000000614000006140000040000000400",		-- 30
			INIT_0D => x"000006140000061400000634000006340000061400000614000008000000065c",		-- 34
			INIT_0E => x"0000061400000614000008000000065c00000614000006140000040000000400",		-- 38
			INIT_0F => x"0000061400000614000006340000063400000614000006140000061400000614",		-- 3c
			INIT_10 => x"0000080000000614000006340000063400000800000006140000080000000400",		-- 40
			INIT_11 => x"0000080000000614000006340000063400000800000006140000080000000600",		-- 44
			INIT_12 => x"0000080000000614000006340000063400000800000006140000080000000600",		-- 48
			INIT_13 => x"0000080000000614000006340000063400000800000006140000080000000000",		-- 4c
			INIT_14 => x"0000080000000614000004440000040000000800000006140000040000000400",		-- 50
			INIT_15 => x"0000080000000614000006340000063400000800000006140000080000000600",		-- 54
			INIT_16 => x"0000080000000614000008000000080000000800000006140000044400000400",		-- 58
			INIT_17 => x"0000080000000614000006340000063400000800000006140000080000000614",		-- 5c
			INIT_18 => x"0000061e0000061e00000634000006340000061e0000061e0000080000000400",		-- 60
			INIT_19 => x"0000061e0000061e00000634000006340000061e0000061e0000080000000614",		-- 64
			INIT_1A => x"0000061e0000061e00000634000006340000061e0000061e0000080000000614",		-- 68
			INIT_1B => x"0000061e0000061e00000634000006340000061e0000061e0000080000000000",		-- 6c
			INIT_1C => x"0000061e0000061e00000400000004000000061e0000061e0000040000000400",		-- 70
			INIT_1D => x"0000061e0000061e00000634000006340000061e0000061e0000080000000614",		-- 74
			INIT_1E => x"0000061e0000061e00000800000008000000061e0000061e0000040000000400",		-- 78
			INIT_1F => x"0000061e0000061e00000634000006340000061e0000061e0000061e0000061e",		-- 7c
			INIT_20 => x"0000080000000e00000008000000080000000800000006000000080000000800",		-- 80
			INIT_21 => x"0000080000000614000008000000060000000800000006000000080000000600",		-- 84
			INIT_22 => x"0000080000000800000006140000061400000800000008000000061400000614",		-- 88
			INIT_23 => x"0000080000000600000008000000060000000800000006000000080000000600",		-- 8c
			INIT_24 => x"0000080000000800000004450000040100000800000006000000040000000400",		-- 90
			INIT_25 => x"0000080000000800000008000000060000000800000006000000080000000600",		-- 94
			INIT_26 => x"0000080000000800000006140000061400000800000006000000061400000614",		-- 98
			INIT_27 => x"0000040100000401000008000000060000000800000006000000080000000600",		-- 9c
			INIT_28 => x"0000080000000800000008000000061400000800000006140000080000000614",		-- a0
			INIT_29 => x"0000080000000800000008000000061400000800000006140000080000000614",		-- a4
			INIT_2A => x"0000080000000800000006140000061400000800000006140000061400000614",		-- a8
			INIT_2B => x"0000080000000614000008000000061400000800000006140000080000000614",		-- ac
			INIT_2C => x"0000080000000800000004010000040100000800000006140000040000000400",		-- b0
			INIT_2D => x"0000080000000800000008000000061400000800000006140000080000000614",		-- b4
			INIT_2E => x"0000080000000800000006140000061400000800000006140000044500000401",		-- b8
			INIT_2F => x"0000080000000800000008000000061400000800000006140000080000000614",		-- bc
			INIT_30 => x"0000065600000656000008000000080000000656000006560000065600000656",		-- c0
			INIT_31 => x"0000080000000800000006140000061400000656000006560000065600000656",		-- c4
			INIT_32 => x"0000080000000800000006140000061400000656000006560000080000000614",		-- c8
			INIT_33 => x"0000065600000656000006140000061400000656000006560000065600000656",		-- cc
			INIT_34 => x"0000065600000656000004440000040000000656000006560000040000000400",		-- d0
			INIT_35 => x"0000080000000800000006140000061400000656000006560000080000000800",		-- d4
			INIT_36 => x"0000080000000800000008000000080000000656000006560000044400000400",		-- d8
			INIT_37 => x"0000065600000656000008000000061400000656000006560000065600000656",		-- dc
			INIT_38 => x"000006160000061600000800000008000000061e0000061e0000065600000656",		-- e0
			INIT_39 => x"0000061e0000061e00000800000006140000061e0000061e0000065600000656",		-- e4
			INIT_3A => x"0000061e0000061e00000800000000000000061e0000061e0000080000000614",		-- e8
			INIT_3B => x"0000061e0000061e00000800000006140000061e0000061e0000065600000656",		-- ec
			INIT_3C => x"0000061e0000061e00000400000004000000061e0000061e0000040000000400",		-- f0
			INIT_3D => x"0000061e0000061e00000800000006140000061e0000061e0000080000000800",		-- f4
			INIT_3E => x"0000061e0000061e00000800000008000000061e0000061e0000040000000400",		-- f8
			INIT_3F => x"0000061e0000061e00000800000006140000061e0000061e0000061e0000061e"		-- fc
		)
		port map (
			ADDRA => romAddr,
			ADDRB => "00000000000000",

			DOA => data(63 downto 32),

			DIA => x"00000000",
			DIB => x"00000000",
			DIPA => "0000",
			DIPB => "0000",
			WEA => "0000",
			WEB => "0000",
			ENA => enabled,
			ENB => '0',
			CLKA => cpuClock,
			CLKB => '0',
			RSTA => '0',
			RSTB => '0',
			REGCEA => '0',
			REGCEB => '0'
		);

	romAddr <= opcode(7 downto 0) & opcode(15) & "00000";

	CSel <= data(1 downto 0);
	ShiftSel <= data(4 downto 2);
	ShifterRight <= data(5);
	ShifterRotate <= data(6);
	ShifterRotateWord <= data(7);
	ShifterExtend <= data(8);
	InvertB <= data(9);
	ConditionalInvertB <= data(10);
	NegAbsExtNot <= data(11);
	FlagsFromB <= data(12);
	ShiftSelOperandOrReg <= data(13);
	UseShifterC <= data(14);
	ALUOp <= data(17 downto 15);
	DefaultReg <= data(20 downto 18);
	RegMod <= data(23 downto 21);
	DefaultIndex <= data(26 downto 24);
	IndexMod <= data(28 downto 27);
	BaseAddr16 <= data(29);
	BitNum <= data(32 downto 30);
	FlagWrite <= data(37 downto 33);
	NoRegWrite <= data(38);
	MulDivOp <= data(40 downto 39);
	DataWidthSel <= data(42 downto 41);
	Illegal <= data(43);

	enabled <= not dmaActive;
end Structural;
-- width 23