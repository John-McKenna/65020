#include "Errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void Error( const Source* source, const std::vector<Token>::iterator* token, const char* message, va_list args )
{
	if ( (source == nullptr) || (token == nullptr) )
	{
		printf( "error " );
		vprintf( message, args );
		printf( "\n" );
	}
	else
	{
		std::vector<Token>::iterator t = *token;
		if ( t == source->tokens.end() ) t--;
		printf( "file %s(%zd): error ", source->GetFilename(t->fileIndex).c_str(), t->line );
		vprintf( message, args );
		printf( "\n" );
		source->PrintLine( stdout, *token );
	}

	printf( "\nbye\n" );
	exit( 1 );
}

void Error( const Source* source, const std::vector<Token>::iterator* token, const char* message, ... )
{
	va_list args;
	va_start( args, message );
	Error( source, token, message, args );
	va_end( args );
}
