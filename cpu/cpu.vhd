library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;

entity CPUMain is
	port (
		cpuClock : in STD_LOGIC;
		cpuAddress : out STD_LOGIC_VECTOR(31 downto 0);
		cpuWriteData : out STD_LOGIC_VECTOR(15 downto 0);
		cpuWriteEnable : out STD_LOGIC;
		cpuWrite8 : out STD_LOGIC;
		cpuReadData : in STD_LOGIC_VECTOR(15 downto 0);
		dmaActive : in STD_LOGIC;
		requestIRQ : in STD_LOGIC;
		reset : in STD_LOGIC;

		illegalInstruction : out STD_LOGIC;
		debugOpcodeLoad : out STD_LOGIC;
		debugRegisterIndex : in STD_LOGIC_VECTOR(3 downto 0);
		debugRegisterValue : out STD_LOGIC_VECTOR(31 downto 0)
	);
end CPUMain;

architecture Behavioural of CPUMain is
	-- output from microcode
	signal mc_aluCSel : MC.CSel_t;
	signal mc_aluShiftSel : MC.ShiftSel_t;
	signal mc_aluShifterRight : STD_LOGIC;
	signal mc_alushifterRotate : STD_LOGIC;
	signal mc_aluShifterRotateWord : STD_LOGIC;
	signal mc_aluShifterExtend : STD_LOGIC;
	signal mc_aluInvertB : STD_LOGIC;
	signal mc_aluConditionalInvertB : STD_LOGIC;
	signal mc_aluNegAbsExtNot : STD_LOGIC;
	signal mc_aluFlagsFromB : STD_LOGIC;
	signal mc_aluShiftSelOperandOrReg : STD_LOGIC;
	signal mc_aluUseShifterC : STD_LOGIC;			-- not used by microcode
	signal mc_aluOp : MC.ALUOp_t;
	signal mc_defaultReg : MC.DefaultReg_t;
	signal mc_regMod : MC.RegMod_t;
	signal mc_defaultIndex : MC.DefaultIndex_t;
	signal mc_indexMod : MC.IndexMod_t;
	signal mc_baseAddr16 : STD_LOGIC;
	signal mc_bitNum : STD_LOGIC_VECTOR(2 downto 0);
	signal mc_flagWrite : STD_LOGIC_VECTOR(4 downto 0);
	signal mc_flagWriteC : STD_LOGIC;
	signal mc_flagWriteZ : STD_LOGIC;
	signal mc_flagWriteV : STD_LOGIC;
	signal mc_flagWriteN : STD_LOGIC;
	signal mc_flagWriteShifterC : STD_LOGIC;
	signal mc_noRegWrite : STD_LOGIC;
	signal mc_mulDivOp : MC.MulDivOp_t;
	signal mc_dataWidthSel : MC.DataWidthSel_t;
	signal mc_illegal : STD_LOGIC;

	-- output from Nanocode
	signal nc_aluASel : MC.ALUASel_t;
	signal nc_aluBSel : MC.ALUBSel_t;
	signal nc_pcInc : STD_LOGIC;
	signal nc_addressInputSel : MC.AddressInputSel_t;
	signal nc_memWriteDataSel : MC.MemWriteDataSel_t;
	signal nc_memWriteEnable : STD_LOGIC;
	signal nc_spLoad : STD_LOGIC;				-- Not used.  SP always written by regular register writes
	signal nc_spInc : STD_LOGIC;
	signal nc_spDec : STD_LOGIC;
	signal nc_operandLoad : STD_LOGIC;
	signal nc_operandExtend : STD_LOGIC;
	signal nc_operandAddrLoad : STD_LOGIC;
	signal nc_operandAddrExtend : STD_LOGIC;
	signal nc_operandAddrExtendFromOperand : STD_LOGIC;
	signal nc_addressInc : STD_LOGIC;
	signal nc_pcLoad : STD_LOGIC;
	signal nc_opcodeLoad : STD_LOGIC;
	signal nc_cycleCond : MC.CycleCond_t;
	signal nc_cycleJump : STD_LOGIC_VECTOR(2 downto 0);
	signal nc_regASel	: MC.RegASel_t;
	signal nc_regBSel : MC.RegBSel_t;
	signal nc_regWriteSel : MC.RegWriteSel_t;
	signal nc_regWriteEnable : STD_LOGIC;
	signal nc_flagsWriteEnable : STD_LOGIC;
	signal nc_memWriteWidth : MC.MemWriteWidth_t;
	signal nc_regBIsIndex : STD_LOGIC;
	signal nc_runMulDiv : STD_LOGIC;
	signal nc_setI : STD_LOGIC;
	signal nc_setB : STD_LOGIC;					-- Not connected
	signal nc_exitReset : STD_LOGIC;

	-- output from ALU
	signal alu_result : STD_LOGIC_VECTOR(31 downto 0);
	signal alu_flag_AdderC : STD_LOGIC;
	signal alu_flag_ShifterC : STD_LOGIC;
	signal alu_flag_Z : STD_LOGIC;
	signal alu_flag_V : STD_LOGIC;
	signal alu_flag_N : STD_LOGIC;

	-- output from Registers
	signal reg_A : STD_LOGIC_VECTOR(31 downto 0);
	signal reg_B : STD_LOGIC_VECTOR(31 downto 0);
	signal reg_PC : STD_LOGIC_VECTOR(31 downto 0);
	signal reg_SP : STD_LOGIC_VECTOR(31 downto 0);
	signal reg_flag_C : STD_LOGIC;
	signal reg_flag_Z : STD_LOGIC;
	signal reg_flag_I : STD_LOGIC;
	signal reg_flag_D : STD_LOGIC;
	signal reg_flag_V : STD_LOGIC;
	signal reg_flag_N : STD_LOGIC;

	-- output from RegAddr
	signal regAddr_reg : STD_LOGIC_VECTOR(3 downto 0);
	signal regAddr_index : STD_LOGIC_VECTOR(3 downto 0);

	-- output from Operand
	signal operand : STD_LOGIC_VECTOR(31 downto 0);

	-- output from OperandAddr
	signal operandAddr : STD_LOGIC_VECTOR(31 downto 0);

	-- output from MemInterface
	signal memInterface_writeData : STD_LOGIC_VECTOR(15 downto 0);

	-- output from Address
	signal address : STD_LOGIC_VECTOR(31 downto 0);

	-- output from OpcodeReg
	signal opcode : STD_LOGIC_VECTOR(15 downto 0);
	signal nextOpcode : STD_LOGIC_VECTOR(15 downto 0);

	-- output from MiscLogic
	signal aluOp : MC.ALUOp_t;
	signal aluASel : MC.ALUASel_t;
	signal aluBSel : MC.ALUBSel_t;
	signal aluInvertB : STD_LOGIC;
	signal aluConditionalInvertB: STD_LOGIC;
	signal aluCSel : MC.CSel_t;
	signal aluSignForExt : STD_LOGIC;
	signal aluShiftSel : MC.ShiftSel_t;
	signal aluDecimal : STD_LOGIC;
	signal dataWidth : STD_LOGIC_VECTOR(1 downto 0);
	signal bitNum: STD_LOGIC_VECTOR(4 downto 0);
	signal memWriteDataSel : MC.MemWriteDataSel_t;

	-- output from Cycle
	signal cycle : STD_LOGIC_VECTOR(2 downto 0);
	signal nextCycle : STD_LOGIC_VECTOR(2 downto 0);
	signal lastCycle : STD_LOGIC;

	-- output from CPUState
	signal startIRQ : STD_LOGIC;
	signal handleIRQ : STD_LOGIC;
	signal inReset : STD_LOGIC;

	-- stray signals
	signal data16 : STD_LOGIC;
	signal regWriteEnable : STD_LOGIC;
	signal regWriteDataVal : STD_LOGIC_VECTOR(31 downto 0);

begin
	ADDRESS_INT : entity work.ADDRESS
		port map (
			addressSel => nc_addressInputSel,
			pcValue => reg_PC,
			spValue => reg_SP,
			aluValue => alu_result,
			opcode => opcode,
			operandAddrValue => operandAddr,
			regBValue => reg_B,
			reset => inReset,
			incAddr => nc_addressInc,
			cycle => nextCycle,
			addressOut => address
		);
	ALU_INT : entity work.ALU
		port map (
			inRegA => reg_A,
			inRegB => reg_B,
			inOperand => operand,
			N => opcode(14 downto 13),
			bitNum => bitNum,
			inCarry => reg_flag_C,
			ASel => aluASel,
			BSel => aluBSel,
			CSel => aluCSel,
			shiftSel => aluShiftSel,
			shifterRight => mc_aluShifterRight,
			shifterRotate => mc_aluShifterRotate,
			shifterRotateWord => mc_aluShifterRotateWord,
			shifterExtend => mc_aluShifterExtend,
			invertB_in => aluInvertB,
			conditionalInvertB => aluConditionalInvertB,
			signForEXT => aluSignForExt,
			decimal => aluDecimal,
			flagsFromB => mc_aluFlagsFromB,
			size => dataWidth,
			op => aluOp,
			result => alu_result,
			outAdderC => alu_flag_AdderC,
			outShifterC => alu_flag_ShifterC,
			outZ => alu_flag_Z,
			outV => alu_flag_V,
			outN => alu_flag_N
		);
	CPUSTATE_INT : entity work.CPUSTATE
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			lastCycle => lastCycle,
			requestIRQ => requestIRQ,
			startIRQ => startIRQ,
			handleIRQ => handleIRQ,
			flagI => reg_flag_I,
			requestReset => reset,
			finishedReset => nc_exitReset,
			inReset => inReset
		);
	CYCLE_INT : entity work.CYCLE
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			cycleCond => nc_cycleCond,
			cycleJump => nc_cycleJump,
			opcode => opcode,
			flagC => reg_flag_C,
			flagZ => reg_flag_Z,
			flagV => reg_flag_V,
			flagN => reg_flag_N,
			baseAddr16 => mc_baseAddr16,
			data16 => data16,
			mulDivRunning => '0',
			cycle => cycle,
			nextCycle => nextCycle,
			lastCycle => lastCycle,
			reset => reset
		);
	MEMINTERFACE_INT : entity work.MEM_INTERFACE
		port map (
			writeDataSel => memWriteDataSel,
			data16 => data16,
			regAData => reg_A,
			aluData => alu_result,
			memWriteData => cpuWriteData
		);
	MICROCODE_INT : entity work.MICROCODE
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			opcode => nextOpcode,
			memReadData => cpuReadData,
	
			CSel => mc_aluCSel,
			ShiftSel => mc_aluShiftSel,
			ShifterRight => mc_aluShifterRight,
			ShifterRotate => mc_alushifterRotate,
			ShifterRotateWord => mc_aluShifterRotateWord,
			ShifterExtend => mc_aluShifterExtend,
			InvertB => mc_aluInvertB,
			ConditionalInvertB => mc_aluConditionalInvertB,
			NegAbsExtNot => mc_aluNegAbsExtNot,
			FlagsFromB => mc_aluFlagsFromB,
			ShiftSelOperandOrReg => mc_aluShiftSelOperandOrReg,
			UseShifterC => mc_aluUseShifterC,
			ALUOp => mc_aluOp,
			DefaultReg => mc_defaultReg,
			RegMod => mc_regMod,
			DefaultIndex => mc_defaultIndex,
			IndexMod => mc_indexMod,
			BaseAddr16 => mc_baseAddr16,
			BitNum => mc_bitNum,
			FlagWrite => mc_flagWrite,
			NoRegWrite => mc_noRegWrite,
			MulDivOp => mc_mulDivOp,
			DataWidthSel => mc_dataWidthSel,
			Illegal => mc_illegal
		);
	MISCLOGIC_INT : entity work.MISC_LOGIC
		port map (
			opcode => opcode,
			negAbsExtNot => mc_aluNegAbsExtNot,
			aluOpIn => mc_aluOp,
			aluASelIn => nc_aluASel,
			aluBSelIn => nc_aluBSel,
			aluInvertBIn => mc_aluInvertB,
			aluConditionalInvertBIn => mc_aluConditionalInvertB,
			aluCSelIn => mc_aluCSel,
			aluOpOut => aluOp,
			aluASelOut => aluASel,
			aluBSelOut => aluBSel,
			aluInvertBOut => aluInvertB,
			aluConditionalInvertBOut => aluConditionalInvertB,
			aluCSelOut => aluCSel,
			aluSignForExtOut => aluSignForExt,
			aluShiftSelOperandOrReg => mc_aluShiftSelOperandOrReg,
			aluShiftSelIn => mc_aluShiftSel,
			aluShiftSelOut => aluShiftSel,
			aluDecimalIn => reg_flag_D,
			aluDecimalOut => aluDecimal,
			dataWidthSel => mc_dataWidthSel,
			dataWidth => dataWidth,
			bitNumIn => mc_bitNum,
			bitNumOut => bitNum,
			memWriteDataSelIn => nc_memWriteDataSel,
			memWriteDataSelOut => memWriteDataSel
		);
	NANOCODE_INT : entity work.NANOCODE
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			opcode => nextOpcode,
			memReadData => cpuReadData,
			opcodeLoadEn => nc_opcodeLoad,
			cycle => nextCycle,
			reset => reset,
	
			ALUASel => nc_aluASel,
			ALUBSel => nc_aluBSel,
			PCInc => nc_pcInc,
			AddressInputSel => nc_addressInputSel,
			MemWriteDataSel => nc_memWriteDataSel,
			WriteEnable => nc_memWriteEnable,
			SPLoad => nc_spLoad,
			SPInc => nc_spInc,
			SPDec => nc_spDec,
			OperandLoad => nc_operandLoad,
			OperandExtend => nc_operandExtend,
			OperandAddrLoad => nc_operandAddrLoad,
			OperandAddrExtend => nc_operandAddrExtend,
			OperandAddrExtendFromOperand => nc_operandAddrExtendFromOperand,
			AddressInc => nc_addressInc,
			PCLoad => nc_pcLoad,
			OpcodeLoad => nc_opcodeLoad,
			CycleCond => nc_cycleCond,
			CycleJump => nc_cycleJump,
			RegASel	=> nc_regASel,
			RegBSel => nc_regBSel,
			RegWriteSel => nc_regWriteSel,
			RegWriteEnable => nc_regWriteEnable,
			FlagsWriteEnable => nc_flagsWriteEnable,
			MemWriteWidth => nc_memWriteWidth,
			RegBIsIndex => nc_regBIsIndex,
			RunMulDiv => nc_runMulDiv,
			SetI => nc_setI,
			SetB => nc_setB,
			ExitReset => nc_exitReset
		);
	OPCODE_REG_INT : entity work.OPCODE_REG
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			memReadData => cpuReadData,
			opcodeLoad => nc_opcodeLoad,
			opcodeOut => opcode,
			nextOpcode => nextOpcode,
			startIRQ => startIRQ,
			reset => reset
		);
	OPERAND_INT : entity work.OPERAND
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			memReadData => cpuReadData,
			operandLoad => nc_operandLoad,
			operandExtend => nc_operandExtend,
			operandOut => operand
		);
	OPERANDADDR_INT : entity work.OPERANDADDR
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
			memReadData => cpuReadData,
			operandAddrLoad => nc_operandAddrLoad,
			operandAddrExtend => nc_operandAddrExtend,
			operandAddrExtendFromOperand => nc_operandAddrExtendFromOperand,
			operand => operand(15 downto 0),
			opcode => opcode,
			cycle => cycle,
			pcValue => reg_B,
			operandAddrOut => operandAddr
		);
	REGADDR_INT : entity work.REGADDR
		port map (
			defaultReg => mc_defaultReg,
			regMod => mc_regMod,
			regIndex => regAddr_reg,
			opcode => opcode,
			defaultIndex => mc_defaultIndex,
			indexMod => mc_indexMod,
			indexIndex => regAddr_index
		);
	REGISTERS_INT : entity work.REGISTERS
		port map (
			cpuClock => cpuClock,
			dmaActive => dmaActive,
		 	dataWidth => dataWidth,
		 	regASource => nc_regASel,
		 	regBSource => nc_regBSel,
		 	regBIsIndex => nc_regBIsIndex,
		 	regIndex => regAddr_reg,
		 	indexIndex => regAddr_index,
		 	debugIndex => debugRegisterIndex,
		 	operand => operand,
		 	regWriteSel => nc_regWriteSel,
		 	regWriteEnable => regWriteEnable,
		 	regWriteALUVal => alu_result,
		 	regWriteMulDivVal => x"00000000",
		 	regWriteDataVal => regWriteDataVal,
		 	pcIncEnable => nc_pcInc,
		 	pcWriteEnable => nc_pcLoad,
		 	pcWriteValue => address,
		 	startIRQ => startIRQ,
		 	spDecEnable => nc_spDec,
		 	spIncEnable => nc_spInc,
		 	setI => nc_setI,
		 	handleIRQ => handleIRQ,
			regAOut => reg_A,
			regBOut => reg_B,
		 	pcReadValue => reg_PC,
		 	spReadValue => reg_SP,
		 	flagOutC => reg_flag_C,
		 	flagOutZ => reg_flag_Z,
		 	flagOutI => reg_flag_I,
		 	flagOutD => reg_flag_D,
		 	flagOutV => reg_flag_V,
		 	flagOutN => reg_flag_N,
		 	flagInC => alu_flag_AdderC,
		 	flagInShifterC => alu_flag_ShifterC,
		 	flagInZ => alu_flag_Z,
		 	flagInV => alu_flag_V,
		 	flagInN => alu_flag_N,
		 	flagWriteEnableC => mc_flagWriteC,
		 	flagWriteEnableShifterC => mc_flagWriteShifterC,
		 	flagWriteEnableZ => mc_flagWriteZ,
		 	flagWriteEnableV => mc_flagWriteV,
		 	flagWriteEnableN => mc_flagWriteN,
		 	flagsWriteEnable => nc_flagsWriteEnable
		);

	cpuAddress <= address;
	cpuWriteEnable <= nc_memWriteEnable and not mc_noRegWrite and not dmaActive and not inReset;
	with nc_memWriteWidth & dataWidth select cpuWrite8 <=
		'1' when "0000" | "0001" | "0010" | "0011",		-- MemWriteWidth_8
		'1' when "1100",								-- MemWriteWidth_D, opcode bits = 00
		'0' when others;

	with dataWidth select data16 <= 
		'1' when "00" | "01",
		'0' when others;
	regWriteEnable <= nc_regWriteEnable and not mc_noRegWrite;
	regWriteDataVal <= x"0000" & cpuReadData;

	illegalInstruction <= mc_illegal;
	debugOpcodeLoad <= nc_opcodeLoad;
	debugRegisterValue <= reg_B;

	mc_flagWriteC <= mc_flagWrite(0);
	mc_flagWriteZ <= mc_flagWrite(1);
	mc_flagWriteV <= mc_flagWrite(2);
	mc_flagWriteN <= mc_flagWrite(3);
	mc_flagWriteShifterC <= mc_flagWrite(4);
end Behavioural;
-- width 19
