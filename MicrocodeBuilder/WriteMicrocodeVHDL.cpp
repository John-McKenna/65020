#include "WriteMicrocodeVHDL.h"
#include <stdio.h>
#include <vector>

bool WriteMicrocodeVHDL( uint64_t* values, const FieldList& fields, const std::string& filename )
{
	FILE* f = fopen( filename.c_str(), "wt" );
	if ( f == nullptr )
	{
		printf( "can't open %s\n", filename.c_str() );
		return false;
	}
	fprintf( f,
		"-- Generated file --\n"
		"library IEEE;\n"
		"use IEEE.std_logic_1164.all;\n"
		"use IEEE.numeric_std.all;\n"
		"\n"
		"library UNISIM;\n"
		"use UNISIM.vcomponents.all;\n"
		"\n"
		"use work.all;\n"
		"\n"
		"entity MICROCODE is\n"
		"\tport (\n"
		"\t\tcpuClock : in STD_LOGIC;\n"
		"\t\tdmaActive : in STD_LOGIC;\n"
		"\t\topcode : in STD_LOGIC_VECTOR(15 downto 0);\n"
		"\t\tmemReadData : in STD_LOGIC_VECTOR(15 downto 0);\n"
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
		"end MICROCODE;\n"
		"\n"
		"architecture Structural of MICROCODE is\n"
		"\tsignal romAddr : STD_LOGIC_VECTOR(13 downto 0);\n"
		"\tsignal data : STD_LOGIC_VECTOR(63 downto 0);\n"
		"\tsignal enabled : STD_LOGIC;\n"
		"begin\n"
		"\tROM_LOW_INST : RAMB16BWER\n"
		"\tgeneric map (\n"
		"\t\t\tSIM_DEVICE => \"SPARTAN6\",\n"
		"\t\t\tDATA_WIDTH_A => 36,\n"
		"\t\t\tDATA_WIDTH_B => 36,\n"
	);
	for ( int romAddr = 0; romAddr < 64; romAddr++ )
	{
		fprintf( f, "\t\t\tINIT_%02X => x\"%08x%08x%08x%08x%08x%08x%08x%08x\"%s\t\t-- %02x\n", 
			romAddr,
			uint32_t(values[8*romAddr+7]),
			uint32_t(values[8*romAddr+6]),
			uint32_t(values[8*romAddr+5]),
			uint32_t(values[8*romAddr+4]),
			uint32_t(values[8*romAddr+3]),
			uint32_t(values[8*romAddr+2]),
			uint32_t(values[8*romAddr+1]),
			uint32_t(values[8*romAddr]),
			romAddr==63?"":",", romAddr*4 );
	}
	fprintf( f,
		"\t\t)\n"
		"\t\tport map (\n"
		"\t\t\tADDRA => romAddr,\n"
		"\t\t\tADDRB => \"00000000000000\",\n"
		"\n"
		"\t\t\tDOA => data(31 downto 0),\n"
		"\n"
		"\t\t\tDIA => x\"00000000\",\n"
		"\t\t\tDIB => x\"00000000\",\n"
		"\t\t\tDIPA => \"0000\",\n"
		"\t\t\tDIPB => \"0000\",\n"
		"\t\t\tWEA => \"0000\",\n"
		"\t\t\tWEB => \"0000\",\n"
		"\t\t\tENA => enabled,\n"
		"\t\t\tENB => '0',\n"
		"\t\t\tCLKA => cpuClock,\n"
		"\t\t\tCLKB => '0',\n"
		"\t\t\tRSTA => '0',\n"
		"\t\t\tRSTB => '0',\n"
		"\t\t\tREGCEA => '0',\n"
		"\t\t\tREGCEB => '0'\n"
		"\t\t);\n"
		"\tROM_HIGH_INST : RAMB16BWER\n"
		"\t\tgeneric map (\n"
		"\t\t\tSIM_DEVICE => \"SPARTAN6\",\n"
		"\t\t\tDATA_WIDTH_A => 36,\n"
		"\t\t\tDATA_WIDTH_B => 36,\n"
	);
	for ( int romAddr = 0; romAddr < 64; romAddr++ )
	{
		fprintf( f, "\t\t\tINIT_%02X => x\"%08x%08x%08x%08x%08x%08x%08x%08x\"%s\t\t-- %02x\n", 
			romAddr,
			uint32_t(values[8*romAddr+7]>>32),
			uint32_t(values[8*romAddr+6]>>32),
			uint32_t(values[8*romAddr+5]>>32),
			uint32_t(values[8*romAddr+4]>>32),
			uint32_t(values[8*romAddr+3]>>32),
			uint32_t(values[8*romAddr+2]>>32),
			uint32_t(values[8*romAddr+1]>>32),
			uint32_t(values[8*romAddr]>>32),
			romAddr==63?"":",", romAddr*4 );
	}
	fprintf( f,
		"\t\t)\n"
		"\t\tport map (\n"
		"\t\t\tADDRA => romAddr,\n"
		"\t\t\tADDRB => \"00000000000000\",\n"
		"\n"
		"\t\t\tDOA => data(63 downto 32),\n"
		"\n"
		"\t\t\tDIA => x\"00000000\",\n"
		"\t\t\tDIB => x\"00000000\",\n"
		"\t\t\tDIPA => \"0000\",\n"
		"\t\t\tDIPB => \"0000\",\n"
		"\t\t\tWEA => \"0000\",\n"
		"\t\t\tWEB => \"0000\",\n"
		"\t\t\tENA => enabled,\n"
		"\t\t\tENB => '0',\n"
		"\t\t\tCLKA => cpuClock,\n"
		"\t\t\tCLKB => '0',\n"
		"\t\t\tRSTA => '0',\n"
		"\t\t\tRSTB => '0',\n"
		"\t\t\tREGCEA => '0',\n"
		"\t\t\tREGCEB => '0'\n"
		"\t\t);\n"
		"\n"
		"\tromAddr <= opcode(7 downto 0) & opcode(15) & \"00000\";\n"
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
