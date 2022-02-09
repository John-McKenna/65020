#include "AsmOptions.h"
#include "Errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AsmOptions::AsmOptions()
{
	outputFileName = nullptr;
	memFileName = nullptr;
	listingFileName = nullptr;
	crossReferenceFileName = nullptr;
}

void AsmOptions::ParseCommandLine( int argc, char* argv[] )
{
	int i = 1;
	while ( i < argc )
	{
		if ( argv[i][0] == '-' )
		{
			if ( strcmp(argv[i], "-o") == 0 )
			{
				i++;
				outputFileName = ReadParameter( i, argc, argv, "filename" );
			}
			if ( strcmp(argv[i], "-om") == 0 )
			{
				i++;
				memFileName = ReadParameter( i, argc, argv, "filename" );
			}
			if ( strcmp(argv[i], "-i") == 0 )
			{
				i++;
				inputPaths.push_back( ReadParameter( i, argc, argv, "filepath" ) );
			}
			if ( strcmp(argv[i], "-l") == 0 )
			{
				i++;
				listingFileName = ReadParameter( i, argc, argv, "filename" );
			}
			if ( strcmp(argv[i], "-x") == 0 )
			{
				i++;
				crossReferenceFileName = ReadParameter( i, argc, argv, "filename" );
			}
		}
		else
		{
			inputFileNames.push_back( ReadParameter( i, argc, argv, "filename" ) );
		}
	}
}

const char* AsmOptions::ReadParameter( int& i, int argc, char* argv[], const char* parameterType )
{
	if ( i >= argc )
	{
		Error( nullptr, nullptr, "Command line parameter expecting a %s", parameterType );
	}
	return argv[i++];
}
