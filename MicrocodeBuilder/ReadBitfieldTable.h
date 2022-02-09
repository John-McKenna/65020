#ifndef READBITFIELDTABLE_H
#define READBITFIELDTABLE_H

#include <string>
#include "ReadBitDefs.h"

bool ReadBitfieldTable( uint64_t* result, int size, BitDef_Fields& fields, BitDef_Values& values, const std::string& filename );

#endif
