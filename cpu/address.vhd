library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

use work.all;
use work.CPU.all;

entity ADDRESS is
	port (
		addressSel : in MC.AddressInputSel_t;

		pcValue : in STD_LOGIC_VECTOR(31 downto 0);
		spValue : in STD_LOGIC_VECTOR(31 downto 0);
		aluValue : in STD_LOGIC_VECTOR(31 downto 0);
		opcode : in STD_LOGIC_VECTOR(15 downto 0);
		operandAddrValue : in STD_LOGIC_VECTOR(31 downto 0);
		regBValue : in STD_LOGIC_VECTOR(31 downto 0);
		reset : in STD_LOGIC;
		cycle : in STD_LOGIC_VECTOR(2 downto 0);

		incAddr : in STD_LOGIC;

		addressOut : out STD_LOGIC_VECTOR(31 downto 0)
	);
end ADDRESS;

architecture Behavioural of ADDRESS is
	signal address_int : STD_LOGIC_VECTOR(31 downto 0) := x"00000000";
	signal isBranch : boolean := false;
	signal isIndirect : boolean := false;
begin
	isBranch <= opcode(4 downto 0) = "10000";
	isIndirect <= opcode(13) = '1';
	address_int <=
		pcValue when addressSel = MC.AddressInputSel_PC else
		spValue when addressSel = MC.AddressInputSel_SP else
		aluValue when addressSel = MC.AddressInputSel_AluOut else
		x"0000fffc" when addressSel = MC.AddressInputSel_Vector and reset = '1' else
		x"0000fffe" xor (x"000000" & "000" & opcode(11 downto 8) & '0') when addressSel = MC.AddressInputSel_Vector else
		operandAddrValue when addressSel = MC.AddressInputSel_OperandAddrIndexed and isBranch and not isIndirect else
		STD_LOGIC_VECTOR(unsigned(operandAddrValue) + unsigned(regBValue)) when addressSel = MC.AddressInputSel_OperandAddrIndexed and not isBranch else
		operandAddrValue when addressSel = MC.AddressInputSel_OperandAddr else
		operandAddrValue;

	addressOut <=
		STD_LOGIC_VECTOR(unsigned(address_int)+1) when incAddr = '1' else
		address_int;
end Behavioural;
-- width 18
