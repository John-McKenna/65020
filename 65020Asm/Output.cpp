#include "Output.h"
#include "StringPool.h"
#include "Options.h"
#include <algorithm>
#include <cinttypes>

Output::Output()
{
	Clear();
}

void Output::Clear()
{
	blocks_m.clear();
	blocksByName_m.clear();
	currentBlock_m = nullptr;
	NewBlock( 0 );
}

Value Output::CurrentLocation()
{
	Value result;
	result.known = true;
	result.type = Value::Type::number;
	result.value.number = currentBlock_m->addr;
	return result;
}

bool Output::Block::operator <( const Block& rhs ) const
{
	return start < rhs.start;
}

void Output::Write( FILE* file )
{
	std::sort( blocks_m.begin(), blocks_m.end() );
	uint32_t startPos;
	uint32_t prevBlockEnd = 0;
	bool firstBlock = true;
	for ( auto block : blocks_m )
	{
		if ( block.values.size() > 0 )
		{
			if ( firstBlock )
			{
				startPos = block.start;
#if ENABLE_OUTPUT_BLOCK_DEBUG
				printf( "first block at %08x\n", startPos );
#endif
				firstBlock = false;
			}
			uint32_t blockSize = uint32_t(block.values.size());
#if ENABLE_OUTPUT_BLOCK_DEBUG
			printf( "Write %08x bytes at %08x-%08x (addr %08x-%08x)\n", blockSize, block.start - startPos, block.start + blockSize - startPos, block.start, block.start + blockSize );
			if ( block.start < prevBlockEnd )
			{
				printf( "overlapping blocks\n" );
			}
#endif
			fseek( file, (block.start - startPos)*2, SEEK_SET );
			fwrite( &(block.values[0]), sizeof(uint16_t), block.values.size(), file );
			prevBlockEnd = block.start + int(block.values.size());
		}
	}
}

void Output::WriteMem( FILE* file )
{
	std::sort( blocks_m.begin(), blocks_m.end() );
	for ( auto block : blocks_m )
	{
		if ( block.values.size() > 0 )
		{
			uint32_t blockSize = uint32_t(block.values.size());
			fprintf( file, "@%08x ", block.start );
			for ( uint32_t i = 0; i < blockSize; i++ )
			{
				fprintf( file, "%04x ", block.values[i] );
				if ( (i < blockSize-1) && (i%8==7) )
				{
					fprintf( file, "\n          " );
				}
			}
			fprintf( file, "\n" );
		}
	}
}

size_t Output::NewBlock( uint32_t start )
{
	Block block;
	block.start = start;
	block.addr = start;
	int index = (int)blocks_m.size();
	blocks_m.push_back( block );
	currentBlock_m = &blocks_m.back();
	if ( currentSectionName_m.ptr != nullptr )
	{
		blocksByName_m[currentSectionName_m] = index;
	}
	return index;
}

void Output::BeginLine( FILE* listing, size_t lineNumber )
{
	bytesThisLine_m = 0;
	printedSourceLine_m = false;
	printedAddress_m = false;
	printedLabel_m = false;
	lineNumber_m = lineNumber;
}

void Output::EndLine( FILE* listing, Source& source, std::vector<Token>::const_iterator& token )
{
	if ( listing != nullptr )
	{
		if ( !printedLabel_m )
		{
			if ( !printedAddress_m )
			{
				fprintf( listing, "          " );
			}
			for ( int i = bytesThisLine_m; i < 4; i++ )
			{
				fprintf( listing, "     " );
			}
		}
		if ( !printedSourceLine_m )
		{
			fprintf( listing, "% 6" PRIdPTR " ", lineNumber_m );
			source.PrintLine( listing, token );
		}
		fprintf( listing, "\n" );
	}
}

void Output::PrintLabel( FILE* listing, uint32_t value )
{
	if ( listing != nullptr )
	{
		fprintf( listing, "          = %08x          ", value );
		printedLabel_m = true;
	}
}

void Output::PrintAddress( FILE* listing )
{
	if ( listing != nullptr )
	{
		fprintf( listing, "%08x: ", CurrentLocation().value.number );
		printedAddress_m = true;
	}
}

void Output::PrintByte( uint16_t byte, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	if ( (listing != nullptr) && !printedAddress_m )
	{
		fprintf( listing, "%08x: ", CurrentLocation().value.number );
		printedAddress_m = true;
	}
	if ( listing != nullptr )
	{
		if ( bytesThisLine_m == 4 )
		{
			if ( !printedSourceLine_m )
			{
				fprintf( listing, "% 6" PRIdPTR " ", lineNumber_m );
				source.PrintLine( listing, token );
			}
			printedSourceLine_m = true;
			fprintf( listing, "\n%08x: ", CurrentLocation().value.number );
			bytesThisLine_m = 0;
		}
		fprintf( listing, "%04x ", byte );
		bytesThisLine_m++;
	}
}

void Output::Emit( uint8_t value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	if ( currentBlock_m->addr - currentBlock_m->start != uint32_t(currentBlock_m->values.size()) )
	{
		NewBlock( currentBlock_m->addr );
	}
	PrintByte( value, listing, source, token );
	currentBlock_m->values.push_back( uint16_t(value) );
	currentBlock_m->addr += 1;
}

void Output::Emit( uint16_t value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	if ( currentBlock_m->addr - currentBlock_m->start != uint32_t(currentBlock_m->values.size()) )
	{
		NewBlock( currentBlock_m->addr );
	}
	PrintByte( value, listing, source, token );
	currentBlock_m->values.push_back( value );
	currentBlock_m->addr += 1;
}

void Output::Emit( uint32_t value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	uint8_t b0 = value & 0xff;
	uint8_t b1 = (value >> 8) & 0xff;
	uint8_t b2 = (value >> 16) & 0xff;
	uint8_t b3 = (value >> 24) & 0xff;
	Emit( uint16_t(b0 | (b2<<8)), listing, source, token );
	Emit( uint16_t(b1 | (b3<<8)), listing, source, token );
}

void Output::Emit( const String& value, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	if ( currentBlock_m->addr - currentBlock_m->start != uint32_t(currentBlock_m->values.size()) )
	{
		NewBlock( currentBlock_m->addr );
	}
	currentBlock_m->values.reserve( currentBlock_m->values.capacity() + value.length );
	for ( size_t i = 0; i < value.length; i++ )
	{
		PrintByte( value.ptr[i], listing, source, token );
		currentBlock_m->values.push_back( uint16_t(value.ptr[i]) );
	}
	currentBlock_m->addr += uint32_t(value.length);
}

void Output::Skip( uint32_t n )
{
	if ( currentBlock_m->values.size() != 0 )
	{
		NewBlock( currentBlock_m->addr );
	}
	currentBlock_m->addr += n;
}

void Output::SwitchToSection( const String& name )
{
	currentSectionName_m = name;
	auto iterator = blocksByName_m.find( name );
	if ( iterator == blocksByName_m.end() )
	{
		size_t blockIndex = NewBlock( currentBlock_m->addr );
		blocksByName_m.emplace( name, blockIndex );
		currentBlock_m = &blocks_m[blockIndex];
		std::string cstr( name.ptr, name.length );
	}
	else
	{
		currentBlock_m = &blocks_m[iterator->second];
		std::string cstr( name.ptr, name.length );
	}
}
