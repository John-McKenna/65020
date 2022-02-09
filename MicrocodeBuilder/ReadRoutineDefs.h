#ifndef READROUTINEDEFS_H
#define READROUTINTDEFS_H

#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, int> RoutineDefs;
typedef int RoutineValues[256];

bool ReadRoutineDefs( RoutineDefs& defs, RoutineValues& values, const std::string& filename );

#endif
