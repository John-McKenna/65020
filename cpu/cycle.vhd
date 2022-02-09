library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
library UNISIM;
use UNISIM.vcomponents.all;

use work.all;

entity CYCLE is
	port (
		cpuClock : in STD_LOGIC;
		dmaActive : in STD_LOGIC;
		cycleCond : in STD_LOGIC_VECTOR(2 downto 0);
		cycleJump : in STD_LOGIC_VECTOR(2 downto 0);
		opcode : in STD_LOGIC_VECTOR(15 downto 0);
		flagC : in STD_LOGIC;
		flagZ : in STD_LOGIC;
		flagV : in STD_LOGIC;
		flagN : in STD_LOGIC;
		baseAddr16 : in STD_LOGIC;
		data16 : in STD_LOGIC;
		mulDivRunning : in STD_LOGIC;
		reset : in STD_LOGIC;

		cycle : out STD_LOGIC_VECTOR(2 downto 0);
		nextCycle : out STD_LOGIC_VECTOR(2 downto 0);
		lastCycle : out STD_LOGIC
	);
end CYCLE;

architecture Behavioural of CYCLE is
	signal cycle_int : STD_LOGIC_VECTOR(2 downto 0) := "000";
	signal nextCycle_int : STD_LOGIC_VECTOR(2 downto 0) := "000";

	signal isBranch : STD_LOGIC := '0';
	signal branchCondAddr : STD_LOGIC_VECTOR(7 downto 0) := "00000000";

	signal takeBranch : STD_LOGIC := '0';
	signal offset32 : STD_LOGIC := '0';
	signal indirect : STD_LOGIC := '0';
	signal link : STD_LOGIC := '0';

	signal takeJump : STD_LOGIC := '0';

	signal branchCycleAddr : STD_LOGIC_VECTOR(6 downto 0) := "0000000";
	signal branchCycle : STD_LOGIC_VECTOR(2 downto 0) := "000";
begin
	BRANCH_COND_INST : ROM256X1
		-- 				C: 1010101010101010
		-- 				Z: 1100110011001100
		-- 				V: 1111000011110000
		-- 				N: 1111111100000000
		-- cond  0 BPL	   ........********	!n
		-- cond  1 BMI	   ********........	n
		-- cond  2 BVC	   ....****....****	!v
		-- cond  3 BVS	   ****....****....	v
		-- cond  4 BCC	   .*.*.*.*.*.*.*.*	!c
		-- cond  5 BCS	   *.*.*.*.*.*.*.*.	c
		-- cond  6 BNE	   ..**..**..**..**	!z
		-- cond  7 BEQ	   **..**..**..**..	z
		-- cond  8 BGE	   ****........**** (n&v) | (!n&!v)
		-- cond  9 BLT	   ....********.... (n&!v) | (!n&v)
		-- cond 10 BLE	   **..**********.. z | (n&!v) | (!n&v)
		-- cond 11 BGT	   ..**..........** !z & (n&v) | (!n&!v)
		-- cond 12 BLS	   ***.***.***.***. c | z
		-- cond 13 BHI	   ...*...*...*...* !c & !z
		-- cond 14 BNV	   ................ 0
		-- cond 15 BRA	   **************** 1
		generic map ( INIT => x"ffff00001111eeee3003cffc0ff0f00fcccc3333aaaa5555f0f00f0fff0000ff" )
		port map (
			A0 => branchCondAddr(0),
			A1 => branchCondAddr(1),
			A2 => branchCondAddr(2),
			A3 => branchCondAddr(3),
			A4 => branchCondAddr(4),
			A5 => branchCondAddr(5),
			A6 => branchCondAddr(6),
			A7 => branchCondAddr(7),
			O => takeBranch
		);
	BRANCH_CYCLE_INST_0 : ROM128X1
		generic map ( INIT => x"15351d3d16361e3e7f7f7f7f7f7f7f7f" )
		port map (
			A0 => branchCycleAddr(0),
			A1 => branchCycleAddr(1),
			A2 => branchCycleAddr(2),
			A3 => branchCycleAddr(3),
			A4 => branchCycleAddr(4),
			A5 => branchCycleAddr(5),
			A6 => branchCycleAddr(6),
			O => branchCycle(0)
		);
	BRANCH_CYCLE_INST_1 : ROM128X1
		generic map ( INIT => x"263e2c3e273f2e3f7e7e7e7e7f7f7f7f" )
		port map (
			A0 => branchCycleAddr(0),
			A1 => branchCycleAddr(1),
			A2 => branchCycleAddr(2),
			A3 => branchCycleAddr(3),
			A4 => branchCycleAddr(4),
			A5 => branchCycleAddr(5),
			A6 => branchCycleAddr(6),
			O => branchCycle(1)
		);
	BRANCH_CYCLE_INST_2 : ROM128X1
		generic map ( INIT => x"38383e3e3a3a3f3f7e7e7e7e7f7f7f7f" )
		port map (
			A0 => branchCycleAddr(0),
			A1 => branchCycleAddr(1),
			A2 => branchCycleAddr(2),
			A3 => branchCycleAddr(3),
			A4 => branchCycleAddr(4),
			A5 => branchCycleAddr(5),
			A6 => branchCycleAddr(6),
			O => branchCycle(2)
		);
	process(cpuClock)
	begin
		if rising_edge(cpuClock) and dmaActive = '0' then
			cycle_int <= nextCycle_int;
		end if;
	end process;
	nextCycle_int <= "000" when reset = '1' else
	             branchCycle when isBranch = '1' else
	             cycleJump when takeJump = '1' else
	             STD_LOGIC_VECTOR(unsigned(cycle_int) + 1);

	with opcode(4 downto 0) select isBranch <=
		'1' when "10000",
		'0' when others;
	offset32 <= opcode(14);
	indirect <= opcode(13);
	link <= opcode(12);
	-- Address for the ROM which maps condition+flags to takeBranch
	branchCondAddr <= opcode(15) & opcode(7 downto 5) & flagN & flagV & flagZ & flagC;
	-- Address for the ROM which maps signals and current cycle to next cycle for branches
	branchCycleAddr <= takeBranch & offset32 & indirect & link & cycle_int;
	-- Evaluated jump condition for non-branches
	takeJump <= '1' when cycleCond = MC.CycleCond_Always else
	            '1' when cycleCond = MC.CycleCond_BaseAddr16 and baseAddr16 = '1' else
	            '1' when cycleCond = MC.CycleCond_Data16 and data16 = '1' else
	            '1' when cycleCond = MC.CycleCond_MulDivRunning and mulDivRunning = '1' else
	            '0';
	cycle <= cycle_int;
	nextCycle <= nextCycle_int;

	lastCycle <=
		'1' when nextCycle_int = "000" and reset = '0' else
		'0';
end Behavioural;
-- width 14
