#ifndef WRITENANOCODEVHDL_H
#define WRITENANOCODEVHDL_H

#include "ReadBitDefs.h"
#include "ReadROutineDefs.h"
#include <string>

bool WriteNanocodeVHDL( uint64_t* values, const FieldList& fields, const RoutineDefs& routineDefs, const RoutineValues& routineValues, const std::string& filename );

#endif
