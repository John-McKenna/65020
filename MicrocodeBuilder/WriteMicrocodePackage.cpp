#include "WriteMicrocodePackage.h"
#include <algorithm>

std::string ToBinary( int value, int width )
{
	std::string result;
	for ( int i = 0; i < width; i++ )
	{
		result = std::to_string(value%2) + result;
		value = value/2;
	}
	return result;
}

void WriteConstants( FILE* f, const FieldList& fields, const BitDef_Values& values )
{
	struct ValueInfo {
		std::string name;
		std::string type;
		int value;

		bool operator <( const ValueInfo& rhs )
		{
			return value < rhs.value;
		}
	};
	std::vector<ValueInfo> valueList;
	for ( const auto& value : values )
	{
		valueList.push_back( {value.first, value.second.type, value.second.value} );
	}
	std::sort( valueList.begin(), valueList.end() );

	for ( const auto& field : fields )
	{
		if ( field.width > 1 )
		{
			fprintf( f, "\tsubtype %s_t is STD_LOGIC_VECTOR(%d downto 0);\n", field.name.c_str(), field.width-1 );
			for ( const auto& value : valueList )
			{
				if ( value.type == field.name )
				{
					fprintf( f, "\tconstant %s : %s_t := \"%s\";\n", value.name.c_str(), field.name.c_str(), ToBinary(value.value, field.width).c_str() );
				}
			}
			fprintf( f, "\n" );
		}
	}
}

bool WriteMicrocodePackage( const FieldList& microcodeFields, const BitDef_Values& microcodeValues,
	const FieldList& nanocodeFields, const BitDef_Values& nanocodeValues,
	const std::string& filename )
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
		"package MC is\n"
	);
	
	WriteConstants( f, microcodeFields, microcodeValues );
	WriteConstants( f, nanocodeFields, nanocodeValues );

	fprintf( f, "end package;\n" );
	fclose( f );
	return true;
}
