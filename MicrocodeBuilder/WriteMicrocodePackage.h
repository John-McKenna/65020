#ifndef WRITEMICROCODEPACKAGE_H
#define WRITEMICROCODEPACKAGE_H

#include "ReadBitDefs.h"

bool WriteMicrocodePackage( const FieldList& microcodeFields, const BitDef_Values& microcodeValues,
	const FieldList& nanocodeFields, const BitDef_Values& nanocodeValues,
	const std::string& filename );

#endif
