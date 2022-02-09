#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <stdio.h>
#include "Expression.h"

struct String;

class Output
{
	public:
		Output();

		Value CurrentLocation();

		void Clear();
		size_t NewBlock( uint32_t start );

		void BeginLine( FILE* listing, size_t lineNumber );
		void EndLine( FILE* listing, Source& source, std::vector<Token>::const_iterator& token );
		void PrintLabel( FILE* listing, uint32_t value );
		void PrintAddress( FILE* listing );

		void Emit( uint8_t value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token );
		void Emit( uint16_t value, FILE* listinge, const Source& source, std::vector<Token>::const_iterator& token );
		void Emit( uint32_t value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token );
		void Emit( const String& value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token );

		void Skip( uint32_t n );

		void SwitchToSection( const String& name );

		void Write( FILE* file );
		void WriteMem( FILE* file );

	private:
		struct Block
		{
			bool operator <( const Block& rhs ) const;

			uint32_t start;
			uint32_t addr;
			std::vector<uint16_t> values;
		};

		void PrintByte( uint16_t byte, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token );

		Block* currentBlock_m;
		std::vector<Block> blocks_m;
		std::unordered_map<String, size_t> blocksByName_m;
		String currentSectionName_m;
		int bytesThisLine_m;
		bool printedAddress_m;
		bool printedSourceLine_m;
		bool printedLabel_m;
		size_t lineNumber_m;
};

#endif
