#ifndef WRITEMICROCODEVHDL_H
#define WRITEMICROCODEVHDL_H

#include "ReadBitDefs.h"
#include <string>

bool WriteMicrocodeVHDL( uint64_t* values, const FieldList& fields, const std::string& filename );

#endif
