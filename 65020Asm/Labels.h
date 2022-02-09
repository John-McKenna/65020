#ifndef LABELS_H
#define LABELS_H

#include <vector>

class Source;
class Token;
struct Value;

void LabelResetPass();
void SetLabel( const Source& source, std::vector<Token>::const_iterator label, const Value& value );
void AddLabelReference( const Source& source, std::vector<Token>::const_iterator reference );
const Value GetLabel( const Source& source, const Token& label );
void WriteLabelReferences( FILE* file, const Source& source );

#endif
