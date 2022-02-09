#ifndef READBITDEFS_H
#define READBITDEFS_H

#include <string>
#include <unordered_map>
#include <vector>

struct BitDef_Field
{
	int index;
	int width;
};

struct FieldInfo {
	std::string name;
	int index;
	int width;
};

struct BitDef_Value
{
	std::string type;
	int value;
};

typedef std::unordered_map<std::string, BitDef_Field> BitDef_Fields;
typedef std::unordered_map<std::string, BitDef_Value> BitDef_Values;
typedef std::vector<FieldInfo> FieldList;

bool ReadBitDefs( BitDef_Fields& fields, BitDef_Values& values, const std::string& filename );
void SortBitFields( const BitDef_Fields& fields, FieldList& result );

#endif
