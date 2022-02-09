#include "ReadRoutineDefs.h"

bool ReadRoutineDefs( RoutineDefs& defs, RoutineValues& values, const std::string& filename )
{
	FILE* f = fopen( filename.c_str(), "rt" );
	if ( f == nullptr )
	{
		printf( "can't open %s\n", filename.c_str() );
		return false;
	}
	while ( !feof(f) )
	{
		char name[256];
		int value;
		if ( fscanf(f, "--%[^\n]\n", name) == 1 ) continue;
		if ( fscanf(f, "%[=]\n", name) == 1 )
		{
			break;
		}
		if ( fscanf(f, "%255s = %d\n", &name, &value) != 2 )
		{
			fclose( f );
			return false;
		}
		defs[name] = value;
	}
	int index = 0;
	memset( values, 0, sizeof(values) );
	while ( !feof(f) )
	{
		char name[256];
		if ( fscanf(f, "--%[^\n]\n", name) == 1 ) continue;
		if ( fscanf(f, "%255s\n", &name) != 1 )
		{
			fclose( f );
			return false;
		}
		if ( defs.count(name) == 0 )
		{
			printf( "Undefined routine %s\n", name );
			return false;
		}
		values[index] = defs[name];
		index++;
	}

	return true;
}
