#ifndef ERRORS_H
#define ERRORS_H

#include "Source.h"
#include <vector>
#include <stdarg.h>

void Error( const Source* source, const std::vector<Token>::iterator* lineStart, const char* message, va_list args );
void Error( const Source* source, const std::vector<Token>::iterator* lineStart, const char* message, ... );

#endif
