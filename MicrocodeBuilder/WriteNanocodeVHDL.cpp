#include "WriteNanocodeVHDL.h"
#include <stdio.h>
#include <vector>
#include <algorithm>

bool WriteNanocodeVHDL( uint64_t* values, const FieldList& fields, const RoutineDefs& routineDefs, const RoutineValues& routineValues, const std::string& filename )
{
	std::vector<std::string> routineNames(32);
	for ( auto def : routineDefs )
	{
		routineNames[def.second] = def.first;
	}
	FILE* f = fopen( filename.c_str(), "wt" );

	fprintf( f,
		"-- Generated file --\n"
		"library IEEE;\n"
		"use IEEE.std_logic_1164.all;\n"
		"use IEEE.numeric_std.all;\n"
		"library UNISIM;\n"
		"use UNISIM.vcomponents.all;\n"
		"\n"
		"use work.all;\n"
		"\n"
		"entity NANOCODE is\n"
		"\tport (\n"
		"\t\tcpuClock : in STD_LOGIC;\n"
		"\t\tdmaActive : in STD_LOGIC;\n"
		"\t\topcode : in STD_LOGIC_VECTOR(15 downto 0);\n"
		"\t\tmemReadData : in STD_LOGIC_VECTOR(15 downto 0);\n"
		"\t\topcodeLoadEn : in STD_LOGIC;\n"
		"\t\tcycle : in STD_LOGIC_VECTOR(2 downto 0);\n"
		"\t\treset : in STD_LOGIC;\n"
		"\n"
	);
	bool first = true;
	for ( const auto& field : fields )
	{
		if ( !first ) fprintf( f, ";\n" );
		if ( field.width == 1 )
		{
			fprintf( f, "\t\t%s : out STD_LOGIC", field.name.c_str() );
		}
		else
		{
			fprintf( f, "\t\t%s : out MC.%s_t", field.name.c_str(), field.name.c_str() );
		}
		first = false;
	}
	fprintf( f,
		"\n\t);\n"
		"end NANOCODE;\n"
		"\n"
		"architecture Structural of NANOCODE is\n"
		"\tsignal addr : STD_LOGIC_VECTOR(7 downto 0) := x\"00\";\n"
		"\tsignal addr0 : STD_LOGIC_VECTOR(13 downto 0);\n"
		"\tsignal addr1 : STD_LOGIC_VECTOR(13 downto 0);\n"
		"\tsignal raw_data : STD_LOGIC_VECTOR(63 downto 0);\n"
		"\tsignal data : STD_LOGIC_VECTOR(63 downto 0);\n"
		"\tsignal enabled : STD_LOGIC;\n"
		"begin\n"
	);
	for ( int routineBit = 0; routineBit < 5; routineBit++ )
	{
		int bitMask = 1 << routineBit;
		uint32_t data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		for ( int bit = 0; bit < 32; bit++ )
		{
			for ( int word = 0; word < 8; word++ )
			{
				int index = 32*word + bit;
				data[word] |= ((routineValues[index] >> routineBit)%2) << bit;
			}
		}
		fprintf( f,
			"	ROUTINE_INST_%d : RAM256X1S\n"
			"		generic map ( INIT => x\"%08x%08x%08x%08x%08x%08x%08x%08x\" )\n"
			"		port map ( A => opcode(7 downto 0), O => addr(%d), D => '0', WE => '0', WCLK => '0' );\n",
			routineBit, data[7], data[6], data[5], data[4], data[3], data[2], data[1], data[0], routineBit+3 );
	}
	fprintf( f,
		"\tROM_INST : RAMB16BWER\n"
		"\t\tgeneric map (\n"
		"\t\t\tSIM_DEVICE => \"SPARTAN6\",\n"
		"\t\t\tDATA_WIDTH_A => 36,\n"
		"\t\t\tDATA_WIDTH_B => 36,\n"
		"\n"
	);
	for ( int romAddr = 0; romAddr < 64; romAddr += 2 )
	{
		fprintf( f, "\t\t\tINIT_%02X => x\"%08x%08x%08x%08x%08x%08x%08x%08x\",\t\t-- routine %d\t%s\n",
			romAddr,
			uint32_t(values[4*romAddr+3]>>32),
			uint32_t(values[4*romAddr+3]),
			uint32_t(values[4*romAddr+2]>>32),
			uint32_t(values[4*romAddr+2]),
			uint32_t(values[4*romAddr+1]>>32),
			uint32_t(values[4*romAddr+1]),
			uint32_t(values[4*romAddr]>>32),
			uint32_t(values[4*romAddr]),
			romAddr/2, routineNames[romAddr/2].c_str() );
		fprintf( f, "\t\t\tINIT_%02X => x\"%08x%08x%08x%08x%08x%08x%08x%08x\"%s\n", 
			romAddr+1,
			uint32_t(values[4*romAddr+7]>>32),
			uint32_t(values[4*romAddr+7]),
			uint32_t(values[4*romAddr+6]>>32),
			uint32_t(values[4*romAddr+6]),
			uint32_t(values[4*romAddr+5]>>32),
			uint32_t(values[4*romAddr+5]),
			uint32_t(values[4*romAddr+4]>>32),
			uint32_t(values[4*romAddr+4]),
			romAddr==62?"":"," );
	}
	fprintf( f,
"		)\n"
"		port map (\n"
"			ADDRA => addr0,\n"
"			ADDRB => addr1,\n"
"\n"
"			DOA => raw_data(31 downto 0),\n"
"			DOB => raw_data(63 downto 32),\n"
"\n"
"			DIA => x\"00000000\",\n"
"			DIB => x\"00000000\",\n"
"			DIPA => \"0000\",\n"
"			DIPB => \"0000\",\n"
"			WEA => \"0000\",\n"
"			WEB => \"0000\",\n"
"			ENA => enabled,\n"
"			ENB => enabled,\n"
"			CLKA => cpuClock,\n"
"			CLKB => cpuClock,\n"
"			RSTA => '0',\n"
"			RSTB => '0',\n"
"			REGCEA => '0',\n"
"			REGCEB => '0'\n"
"		);\n"
"\n"
"	addr(2 downto 0) <= cycle;\n"
"	addr0 <= addr & \"000000\";\n"
"	addr1 <= addr & \"100000\";\n"
"\n"
"	data <=\n"
"		raw_data when reset = '0' else\n"
"		x\"0000000000000000\";\n"
"\n"
	);
	for ( const auto& field : fields )
	{
		if ( field.width == 1 )
		{
			fprintf( f, "\t%s <= data(%d);\n", field.name.c_str(), field.index );
		}
		else
		{
			fprintf( f, "\t%s <= data(%d downto %d);\n", field.name.c_str(), field.index+field.width-1, field.index );
		}
	}
	fprintf( f,
		"\n"
		"\tenabled <= not dmaActive;\n"
		"end Structural;\n"
		"-- width 23\n"
	);
	fclose( f );
	return true;
}
