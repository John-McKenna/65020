#include <stdio.h>
#include "AsmOptions.h"
#include "Source.h"
#include "Assembler.h"
#include "Labels.h"
#include "InstructionInfo.h"

int main( int argc, char *argv[] )
{
	InitInstructionInfo();
	AsmOptions asmOptions;
	asmOptions.ParseCommandLine( argc, argv );
	printf( "input: " );
	for ( auto inputFileName : asmOptions.inputFileNames )
	{
		printf( "%s ", inputFileName );
	}
	printf( "\n" );
	if ( asmOptions.outputFileName != nullptr )
	{
		printf( "output: %s\n", asmOptions.outputFileName );
	}
	if ( asmOptions.memFileName != nullptr )
	{
		printf( "output: %s\n", asmOptions.memFileName );
	}

	Source source( asmOptions );
	for ( auto inputFileName : asmOptions.inputFileNames )
	{
		source.AppendFile( inputFileName );
	}
	Output output;
	Assembler assembler( source, output );
	assembler.Assemble();
	if ( asmOptions.outputFileName != nullptr )
	{
		FILE* outf = fopen( asmOptions.outputFileName, "wb" );
		output.Write( outf );
		fclose( outf );
	}
	if ( asmOptions.memFileName != nullptr )
	{
		FILE* outf = fopen( asmOptions.memFileName, "wt" );
		output.WriteMem( outf );
		fclose( outf );
	}
	if ( asmOptions.crossReferenceFileName != nullptr )
	{
		FILE* crossRef = fopen( asmOptions.crossReferenceFileName, "wt" );
		WriteLabelReferences( crossRef, source );
		fclose( crossRef );
	}
	if ( asmOptions.listingFileName != nullptr )
	{
		FILE* listing = fopen( asmOptions.listingFileName, "wt" );
		assembler.AssemblePass( listing );
		fclose( listing );
	}
	printf( "done\n" );
}
