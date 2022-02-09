#include "ReadBitfieldTable.h"

bool ReadBitfieldTable( uint64_t* result, int size, BitDef_Fields& fields, BitDef_Values& values, const std::string& filename )
{
	FILE* f = fopen( filename.c_str(), "rt" );
	if ( f == nullptr )
	{
		printf( "can't open %s\n", filename.c_str() );
		return false;
	}
	int index = 0;
	uint64_t entry = 0;
	while ( !feof(f) )
	{
		char name[256];
		if ( fscanf(f, "--%[^\n]\n", name) == 1 ) continue;
		if ( fscanf(f, "%255[;]\n", &name) == 1 )
		{
			if ( index >= size )
			{
				fclose( f );
				return false;
			}
			result[index] = entry;
			index++;
			entry = 0;
			continue;
		}
		if ( fscanf(f, "%255[^; \n]\n", &name) != 1 )
		{
			fclose( f );
			return false;
		}
		if ( strcmp(name, "0") == 0 ) continue;
		if ( values.count(name) == 0 )
		{
			size_t pos = ftell(f);
			printf( "Unkown value %s\n", name );
			return false;
		}
		BitDef_Value& value = values[name];
		if ( fields.count(value.type) == 0 )
		{
			printf( "Unknown type %s for value %s\n", value.type.c_str(), name );
		}
		BitDef_Field& field = fields[value.type];
		entry |= uint64_t(value.value) << field.index;
	}
	return true;
}
