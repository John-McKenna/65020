#include "ReadBitDefs.h"
#include <algorithm>

bool ReadBitDefs( BitDef_Fields& fields, BitDef_Values& values, const std::string& filename )
{
	FILE* f = fopen( filename.c_str(), "rt" );
	if ( f == nullptr )
	{
		printf( "can't open %s\n", filename.c_str() );
		return false;
	}
	int index = 0;
	// read widths, calculate indices
	while ( !feof(f) )
	{
		char name[256];
		int width;
		if ( fscanf(f, "--%[^\n]\n", name) == 1 ) continue;
		if ( fscanf(f, "%[=]\n", name) == 1 )
		{
			break;
		}
		if ( fscanf(f, "%255[^:]: %d\n", &name, &width) != 2 )
		{
			fclose( f );
			return false;
		}
		fields[name] = BitDef_Field{index, width};
		index += width;
	}
	// read field values
	while ( !feof(f) )
	{
		char name[256];
		char fieldName[256];
		int value;
		if ( fscanf(f, "--%[^\n]\n", name) == 1 ) continue;
		if ( fscanf(f, "%255[^:]:%255s = %d\n", &name, &fieldName, &value) != 3 )
		{
			fclose( f );
			return false;
		}
		if ( fields.count(fieldName) == 0 )
		{
			printf( "Undefined field %s\n", fieldName );
		}
		BitDef_Field& field = fields[fieldName];
		if ( value >= (1 <<field.width) )
		{
			printf( "Value %s = %d too large for field %s (width %d)\n", name, value, fieldName, field.width );
			return false;
		}
		values[name] = {fieldName, value};
	}
	return true;
}

bool operator <( const FieldInfo& lhs, const FieldInfo& rhs )
{
	return lhs.index < rhs.index;
}

void SortBitFields( const BitDef_Fields& fields, FieldList& result )
{
	for ( const auto& field : fields )
	{
		result.push_back( {field.first, field.second.index, field.second.width} );
	}
	std::sort( result.begin(), result.end() );
}
