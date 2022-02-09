library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity REGISTERS is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;

	 	dataWidth : in STD_LOGIC_VECTOR(1 downto 0);

	 	regASource : in MC.RegASel_t;
		
	 	regBSource : in MC.RegBSel_t;
	 	regBIsIndex : in STD_LOGIC;

	 	regIndex : in STD_LOGIC_VECTOR(3 downto 0);
	 	indexIndex : in STD_LOGIC_VECTOR(3 downto 0);
	 	debugIndex : in STD_LOGIC_VECTOR(3 downto 0);

	 	operand : in STD_LOGIC_VECTOR(31 downto 0);

	 	regWriteSel : MC.RegWriteSel_t;
	 	regWriteEnable : in STD_LOGIC;		-- regWriteEnable (nanocode) and !noRegWrite (microcode)
	 	regWriteALUVal : in STD_LOGIC_VECTOR(31 downto 0);
	 	regWriteMulDivVal : in STD_LOGIC_VECTOR(31 downto 0);
	 	regWriteDataVal : in STD_LOGIC_VECTOR(31 downto 0);

	 	pcIncEnable : in STD_LOGIC;
	 	pcWriteEnable : in STD_LOGIC;
	 	pcWriteValue : in STD_LOGIC_VECTOR(31 downto 0);
	 	startIRQ : in STD_LOGIC;

	 	spDecEnable : in STD_LOGIC;
	 	spIncEnable : in STD_LOGIC;

	 	setI : in STD_LOGIC;
	 	handleIRQ : in STD_LOGIC;

		regAOut : out STD_LOGIC_VECTOR(31 downto 0);
		regBOut : out STD_LOGIC_VECTOR(31 downto 0);

	 	pcReadValue : out STD_LOGIC_VECTOR(31 downto 0);
	 	spReadValue : out STD_LOGIC_VECTOR(31 downto 0);

	 	flagOutC : out STD_LOGIC;
	 	flagOutZ : out STD_LOGIC;
	 	flagOutI : out STD_LOGIC;
	 	flagOutD : out STD_LOGIC;
	 	flagOutV : out STD_LOGIC;
	 	flagOutN : out STD_LOGIC;
	 	flagInC : in STD_LOGIC;
	 	flagInShifterC : in STD_LOGIC;
	 	flagInZ : in STD_LOGIC;
	 	flagInV : in STD_LOGIC;
	 	flagInN : in STD_LOGIC;
	 	flagWriteEnableC : in STD_LOGIC;
	 	flagWriteEnableShifterC : in STD_LOGIC;
	 	flagWriteEnableZ : in STD_LOGIC;
	 	flagWriteEnableV : in STD_LOGIC;
	 	flagWriteEnableN : in STD_LOGIC;
	 	flagsWriteEnable : in STD_LOGIC
	);
end REGISTERS;

architecture Behavioural of REGISTERS is
	signal addrA : STD_LOGIC_VECTOR(3 downto 0);
	signal rValA : STD_LOGIC_VECTOR(31 downto 0);
	signal wValA : STD_LOGIC_VECTOR(31 downto 0);

	signal addrB : STD_LOGIC_VECTOR(3 downto 0);
	signal rValB : STD_LOGIC_VECTOR(31 downto 0);

	signal regWriteValue : STD_LOGIC_VECTOR(31 downto 0);
	signal regWriteEnable_int : STD_LOGIC;

	signal regPCValue : STD_LOGIC_VECTOR(31 downto 0) := x"00000000";
	signal regSPValue : STD_LOGIC_VECTOR(31 downto 0) := x"000001ff";
	signal regPValue : STD_LOGIC_VECTOR(31 downto 0) := x"00000014";

	signal regAOut_int : STD_LOGIC_VECTOR(31 downto 0);

	signal regAOutIsPC : boolean;
	signal regAOutIsSP : boolean;
	signal regAOutIsP : boolean;

begin
	RegisterGenerate:
	for i in 0 to 31 generate
		PortAx : RAM32X1D
		generic map (
			INIT => x"00000000"
		)
		port map (
			WCLK => cpuClock, WE => regWriteEnable_int,
			A0 => addrA(0), DPRA0 => addrB(0),
			A1 => addrA(1), DPRA1 => addrB(1),
			A2 => addrA(2), DPRA2 => addrB(2),
			A3 => addrA(3), DPRA3 => addrB(3),
			A4 => '0', DPRA4 => '0',
			D => wValA(i),
			DPO => rValB(i),
			SPO => rValA(i)
		);
	end generate RegisterGenerate;

	process ( cpuClock )
		variable newPC : STD_LOGIC_VECTOR(31 downto 0);
	begin
		if rising_edge(cpuClock) and dmaActive = '0' then
			-- Handle PC
			-- if write and inc are both set, we need to do both
			-- this requires a variable
			newPC := regPCValue;
			if pcWriteEnable = '1' then
				newPC := pcWriteValue;
			end if;
			if pcIncEnable = '1' and startIRQ = '0' then
				newPC := STD_LOGIC_VECTOR( unsigned(newPC) + 1 );
			end if;
			regPCValue <= newPC;
			-- Handle SP
			if spDecEnable = '1' then
				regSPValue <= STD_LOGIC_VECTOR( signed(regSPValue) - 1 );
			elsif spIncEnable = '1' then
				regSPValue <= STD_LOGIC_VECTOR( unsigned(regSPValue) + 1 );
			end if;
			-- Handle P
			if flagsWriteEnable = '1' then
				if flagWriteEnableC = '1' then
					regPValue(CPU.regP_C) <= flagInC;
				end if;
				if flagWriteEnableShifterC = '1' then
					regPValue(CPU.regP_C) <= flagInShifterC;
				end if;
				if flagWriteEnableZ = '1' then
					regPValue(CPU.regP_Z) <= flagInZ;
				end if;
				if flagWriteEnableV = '1' then
					regPValue(CPU.regP_V) <= flagInV;
				end if;
				if flagWriteEnableN = '1' then
					regPValue(CPU.regP_N) <= flagInN;
				end if;
			end if;
			if setI = '1' then
				regPValue(CPU.regP_I) <= '1';
			end if;
			-- Handle writes to SP/P (PC can't be written to this way)
			if regWriteEnable = '1' then
				if to_integer(unsigned(addrA)) = CPU.regSP then regSPValue <= wValA; end if;
				if to_integer(unsigned(addrA)) = CPU.regP then regPValue <= wValA; end if;
			end if;
		end if;
	end process;

	regAOutIsPC <= ((regASource = MC.RegASel_Reg or regASource = MC.RegASel_Operand)
					and addrA = STD_LOGIC_VECTOR(to_unsigned(CPU.regPC,4)))
				 or regASource = MC.RegASel_PC;
	regAOutIsSP <= (regASource = MC.RegASel_Reg or regASource = MC.RegASel_Operand)
					and addrA = STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4));
	regAOutIsP <= ((regASource = MC.RegASel_Reg or regASource = MC.RegASel_Operand)
						and addrA = STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)))
				or regASource = MC.RegASel_P;

	regAOut_int <=
		regPCValue	when regAOutIsPC else
		regSPValue	when regAOutIsSP else
		regPValue	when regAOutIsP else
		rValA;

	wValA <= 
		x"000000" & regWriteValue(7 downto 0)	when addrA /= STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4)) and dataWidth = "00" else
		x"000001" & regWriteValue(7 downto 0)	when addrA = STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4)) and dataWidth = "00" else
		x"0000" & regWriteValue(15 downto 0)	when dataWidth = "01" else
		regWriteValue;

	regBOut <=
		regPCValue								when addrB = STD_LOGIC_VECTOR(to_unsigned(CPU.regPC,4)) else
		regSPValue								when addrB = STD_LOGIC_VECTOR(to_unsigned(CPU.regSP,4)) else
		regPValue								when addrB = STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) and regBIsIndex = '0' else
		x"00000000"								when addrB = STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) and regBIsIndex = '1' else
		rValB;

	addrA <=
		STD_LOGIC_VECTOR(to_unsigned(CPU.regPC,4)) when regASource = MC.RegASel_PC else
		STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) when regASource = MC.RegASel_P else
		regIndex when regASource = MC.RegASel_Reg else
		operand(3 downto 0) when regASource = MC.RegASel_Operand else
		operand(3 downto 0);

	addrB <=
		debugIndex when dmaActive = '1' else
		regIndex when regBSource = MC.RegBSel_Reg else
		indexIndex when regBSource = MC.RegBSel_Index else
		STD_LOGIC_VECTOR(to_unsigned(CPU.regP,4)) when regBSource = MC.RegBSel_Zero else		-- not used.
		operand(3 downto 0) when regBSource = MC.RegBSel_Operand else
		operand(3 downto 0);

	pcReadValue <= regPCValue;
	spReadValue <= regSPValue;

	flagOutC <= regPValue(CPU.regP_C);
	flagOutZ <= regPValue(CPU.regP_Z);
	flagOutI <= regPValue(CPU.regP_I);
	flagOutD <= regPValue(CPU.regP_D);
	flagOutV <= regPValue(CPU.regP_V);
	flagOutN <= regPValue(CPU.regP_N);

	regAOut(31 downto CPU.regP_B+1) <= regAOut_int(31 downto CPU.regP_B+1);
	regAOut(CPU.regP_B) <= not handleIRQ when regASource = MC.RegASel_P else regAOut_int(CPU.regP_B);
	regAOut(CPU.regP_B-1 downto 0) <= regAOut_int(CPU.regP_B-1 downto 0);

	regWriteValue <=
	 	regWriteALUVal when regWriteSel = MC.RegWriteSel_Alu else
	 	regWriteMulDivVal when regWriteSel = MC.RegWriteSel_MulDiv else
	 	regWriteDataVal;

	regWriteEnable_int <= regWriteEnable and not dmaActive;

end Behavioural;
-- width 18
