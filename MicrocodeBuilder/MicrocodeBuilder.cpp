#include <stdio.h>
#include <string>
#include "ReadBitDefs.h"
#include "ReadRoutineDefs.h"
#include "ReadBitfieldTable.h"
#include "WriteMicrocodeVHDL.h"
#include "WriteNanocodeVHDL.h"
#include "WriteMicrocodePackage.h"

int main( int argc, const char** argv )
{
	if ( argc != 2 )
	{
		printf( "%s <path>\n", argv[0] );
		return 1;
	}
	std::string sourcePath = argv[1];

	// Read bit definitions (microcode)
	BitDef_Fields microcodeFields;
	BitDef_Values microcodeValues;
	ReadBitDefs( microcodeFields, microcodeValues, sourcePath+"/"+"microcode.bitdef" );

	// Read bit definitions (nanocode)
	BitDef_Fields nanocodeFields;
	BitDef_Values nanocodeValues;
	ReadBitDefs( nanocodeFields, nanocodeValues, sourcePath+"/"+"nanocode.bitdef" );

	// Read nanocode routine definitions and table
	RoutineDefs routineDefs;
	RoutineValues routineValues;
	ReadRoutineDefs( routineDefs, routineValues, sourcePath+"/"+"nanocode.routinedef" );

	// Read microcode
	uint64_t microcode[512];
	ReadBitfieldTable( microcode, 512, microcodeFields, microcodeValues, sourcePath+"/"+"microcode.def" );

	// Read nanocode
	uint64_t nanocode[32*8];
	ReadBitfieldTable( nanocode, 32*8, nanocodeFields, nanocodeValues, sourcePath+"/"+"nanocode.def" );

	FieldList microcodeFieldList;
	SortBitFields( microcodeFields, microcodeFieldList );
	FieldList nanocodeFieldList;
	SortBitFields( nanocodeFields, nanocodeFieldList );

	// Write VHDL
	WriteMicrocodeVHDL( microcode, microcodeFieldList, sourcePath+"/microcode.vhd" );
	WriteNanocodeVHDL( nanocode, nanocodeFieldList, routineDefs, routineValues, sourcePath+"/nanocode.vhd" );
	WriteMicrocodePackage( microcodeFieldList, microcodeValues, nanocodeFieldList, nanocodeValues, sourcePath+"/microcode_package.vhd" );

	return 0;
}
