#include "Labels.h"
#include "Source.h"
#include "Expression.h"
#include "Errors.h"
#include <unordered_map>
#include <algorithm>

struct LabelInfo
{
	bool seenThisPass;
	Value value;

	std::vector<Token>::const_iterator definition;
	std::vector<std::vector<Token>::const_iterator> references;
};

static std::unordered_map<String, LabelInfo> labelValues_g;

void LabelResetPass()
{
	for ( auto& label : labelValues_g )
	{
		label.second.seenThisPass = false;
		label.second.references.clear();
	}
}

void SetLabel( const Source& source, std::vector<Token>::const_iterator label, const Value& value )
{
	if ( value.known && (value.type != Value::Type::number) )
	{
		Error( &source, nullptr, "can't set a label to a non-number\n" );
	}
	const String& string = source.stringPool.GetString(label->value.labelStringIndex);
	auto iterator = labelValues_g.find( string );
	if ( iterator == labelValues_g.end() )
	{
		LabelInfo labelInfo;
		labelInfo.seenThisPass = true;
		labelInfo.value = value;
		labelInfo.definition = label;
		labelValues_g.emplace( string, labelInfo );
	}
	else
	{
		if ( iterator->second.seenThisPass )
		{
			std::string cstr( string.ptr, string.length );
			Error( &source, nullptr, "label %s redefined\n", cstr.c_str() );
		}
		iterator->second.seenThisPass = true;
		iterator->second.value = value;
		iterator->second.definition = label;
	}
}

void AddLabelReference( const Source& source, std::vector<Token>::const_iterator reference )
{
	const String& string = source.stringPool.GetString(reference->value.labelStringIndex);
	auto& iterator = labelValues_g.find( string );
	if ( iterator == labelValues_g.end() )
	{
		LabelInfo labelInfo;
		labelInfo.seenThisPass = false;
		labelInfo.value.known = false;
		labelInfo.references.push_back( reference );
		labelValues_g.emplace( string, labelInfo );
	}
	else
	{
		iterator->second.references.push_back( reference );
	}
}

const Value GetLabel( const Source& source, const Token& label )
{
	const String& string = source.stringPool.GetString(label.value.labelStringIndex);
	auto result = labelValues_g.find(string);
	if ( result == labelValues_g.end() )
	{
		Value result;
		result.known = false;
		return result;
	}
	return result->second.value;
}

struct LabelInfoPair
{
	LabelInfoPair( const String* label, const LabelInfo* info )
	{
		label_m = label;
		info_m = info;
	}
	bool operator <( const LabelInfoPair& rhs ) const
	{
		if ( info_m->value.value.number == rhs.info_m->value.value.number )
		{
			return *label_m < *rhs.label_m;
		}
		return info_m->value.value.number < rhs.info_m->value.value.number;
	}

	const String* label_m;
	const LabelInfo* info_m; 
};

void WriteLabelReferences( FILE* file, const Source& source )
{
	std::vector<LabelInfoPair> labelList;
	for ( auto& iterator : labelValues_g )
	{
		LabelInfoPair infoPair( &iterator.first, &iterator.second );
		labelList.push_back( infoPair );
	}
	std::sort( labelList.begin(), labelList.end() );
	for ( auto iterator : labelList )
	{
		const String& name = *iterator.label_m;
		const std::string cname(name.ptr, name.length);
		const LabelInfo& info = *iterator.info_m;
		fprintf( file, "%s = %08x: %s line %zd\n\t", cname.c_str(), info.value.value.number, source.GetFilename(info.definition->fileIndex).c_str(), info.definition->line );
		source.PrintLine( file, info.definition );
		fprintf( file, "\n" );
		if ( info.references.size() > 0 )
		{
			fprintf( file, "\t-----------------------------\n" );
		}
		for ( auto& reference : info.references )
		{
			fprintf( file, "\t%s:%zd\t", source.GetFilename(reference->fileIndex).c_str(), reference->line );
			source.PrintLine( file, reference );
			fprintf( file, "\n" );
		}
		fprintf( file, "\n" );
	}
}
