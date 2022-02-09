#include "Source.h"
#include "StringPool.h"
#include "AsmOptions.h"
#include "Errors.h"
#include "Output.h"
#include <stdio.h>
#include <unordered_map>

// enum names, for debugging
const char* Token::TokenName_g[] = {
	"none",
	"label", "instruction", "*", "directive", "reg", "stringLit", "charLit",
	"number",
	"=", "+", "-", "*_op", "/", "%",
	"unary+", "unary-",
	"&", "|", "^", "<<", ">>",
	"<", ">", ">=", "<=", "!=",
	"!", "(", ")",
	"#", ",", ".", "lowByte", "highByte",
	"lineEnd", "lineStart", "sourceEnd"
};
const char* Token::InstructionName_g[] = {
	"ABS", "ABX", "ABY",
	"ACX", "ACY", "ADC", "ADD", "ADX", "ADY", "AND", "ANX", "ANY",
	"ASL", "ASR", "BCC", "BCS", "BCX", "BCY", "BEQ", "BGE", "BGT",
	"BHI", "BHS", "BIC", "BIT", "BLE", "BLS", "BLT", "BMI", "BNE",
	"BNV", "BPL", "BRA", "BRK", "BVC", "BVS", "CBT", "CCX", "CCY",
	"CLC", "CLD", "CLI", "CLV", "CMP", "CPC", "CPX", "CPY", "DEC",
	"DEX", "DEY", "DIV", "DVS", "EOR", "EOX", "EOY", "ESL", "INC",
	"INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY", "LSR", "MDS",
	"MLS", "MOD", "MOV", "MUL", "NEG", "NGX", "NGY", "NOP", "ORA",
	"ORX", "ORY", "PHA", "PHP", "PHX", "PHY", "PLA", "PLP", "PLX",
	"PLY", "RLB", "ROL", "ROR", "RRB", "RSQ", "RTI", "RTS",
	"SBC", "SBT", "SBX", "SBY", "SCX", "SCY", "SEC", "SED",
	"SEI", "SEV", "SQR", "STA", "STX", "STY", "SUB",
	"TAX", "TAY", "TBT", "TSX", "TXA", "TXS", "TYA", "XBT",
	"NOT", "NTX", "NTY",
	"EXT", "EXX", "EXY",
	"TBT_C", "TBT_D", "TBT_I", "TBT_V",
	"XBT_C", "XBT_D", "XBT_I", "XBT_V",
	"LDR", "STR", "PSH", "PUL",
	"undefined"
};
const char* Token::DirectiveName_g[] = {
	".org", ".byte", ".word", ".long", ".include", ".space", ".section",
	".if", ".else", ".endif"
};

const char* Token::registerName_g[] = {
	"A0", "A1", "A2", "A3",
	"X0", "X1", "X2", "X3",
	"Y0", "Y1", "Y2", "Y3",
	"P", "Z", "SP", "PC",
	"undefined"
};

Token::RegisterType Token::registerType_g[] = {
	Token::RegisterType::A, Token::RegisterType::A, Token::RegisterType::A, Token::RegisterType::A,
	Token::RegisterType::X, Token::RegisterType::X, Token::RegisterType::X, Token::RegisterType::X,
	Token::RegisterType::Y, Token::RegisterType::Y, Token::RegisterType::Y, Token::RegisterType::Y,
	Token::RegisterType::P, Token::RegisterType::P, Token::RegisterType::P, Token::RegisterType::P,
	Token::RegisterType::unknown
};

// instructions and directives don't need interning.  They are only stored
// as keys in these maps.  We never need to retrieve their text.
static const std::unordered_map<String, Token::Instruction> instructions_g({
	{"ABS", Token::Instruction::ABS},
	{"ADC", Token::Instruction::ADC},
	{"ADD", Token::Instruction::ADD},
	{"AND", Token::Instruction::AND},
	{"ASL", Token::Instruction::ASL}, {"ASR", Token::Instruction::ASR}, {"BCC", Token::Instruction::BCC},
	{"BCS", Token::Instruction::BCS}, {"BEQ", Token::Instruction::BEQ},
	{"BGE", Token::Instruction::BGE}, {"BGT", Token::Instruction::BGT}, {"BHI", Token::Instruction::BHI},
	{"BHS", Token::Instruction::BHS}, {"BIC", Token::Instruction::BIC},
	{"BIT", Token::Instruction::BIT}, {"BLE", Token::Instruction::BLE}, {"BLS", Token::Instruction::BLS},
	{"BLT", Token::Instruction::BLT}, {"BMI", Token::Instruction::BMI}, {"BNE", Token::Instruction::BNE},
	{"BNV", Token::Instruction::BNV}, {"BPL", Token::Instruction::BPL}, {"BRA", Token::Instruction::BRA},
	{"BRK", Token::Instruction::BRK}, {"BVC", Token::Instruction::BVC}, {"BVS", Token::Instruction::BVS},
	{"CBT", Token::Instruction::CBT},
	{"CLC", Token::Instruction::CLC}, {"CLD", Token::Instruction::CLD}, {"CLI", Token::Instruction::CLI},
	{"CLV", Token::Instruction::CLV}, {"CMP", Token::Instruction::CMP}, {"CPC", Token::Instruction::CPC},
	{"DEC", Token::Instruction::DEC},
	{"DEX", Token::Instruction::DEX}, {"DEY", Token::Instruction::DEY}, {"DIV", Token::Instruction::DIV},
	{"DVS", Token::Instruction::DVS}, {"EOR", Token::Instruction::EOR},
	{"ESL", Token::Instruction::ESL}, {"INC", Token::Instruction::INC},
	{"INX", Token::Instruction::INX}, {"INY", Token::Instruction::INY}, {"JMP", Token::Instruction::JMP},
	{"JSR", Token::Instruction::JSR}, {"LDA", Token::Instruction::LDA}, {"LDX", Token::Instruction::LDX},
	{"LDY", Token::Instruction::LDY}, {"LSR", Token::Instruction::LSR}, {"MDS", Token::Instruction::MDS},
	{"MLS", Token::Instruction::MLS}, {"MOD", Token::Instruction::MOD}, {"MOV", Token::Instruction::MOV},
	{"MUL", Token::Instruction::MUL},
	{"NEG", Token::Instruction::NEG},
	{"NOP", Token::Instruction::NOP}, {"ORA", Token::Instruction::ORA},
	{"PHA", Token::Instruction::PHA}, {"PHP", Token::Instruction::PHP},
	{"PLA", Token::Instruction::PLA},
	{"PLP", Token::Instruction::PLP},
	{"RLB", Token::Instruction::RLB}, {"ROL", Token::Instruction::ROL},
	{"ROR", Token::Instruction::ROR}, {"RRB", Token::Instruction::RRB}, {"RSQ", Token::Instruction::RSQ},
	{"RTI", Token::Instruction::RTI}, {"RTS", Token::Instruction::RTS},
	{"SBC", Token::Instruction::SBC}, {"SBT", Token::Instruction::SBT},
	{"SEC", Token::Instruction::SEC}, {"SED", Token::Instruction::SED}, {"SEI", Token::Instruction::SEI},
	{"SEV", Token::Instruction::SEV}, 
	{"SQR", Token::Instruction::SQR}, {"STA", Token::Instruction::STA},
	{"STX", Token::Instruction::STX}, {"STY", Token::Instruction::STY}, {"SUB", Token::Instruction::SUB},
	{"TAX", Token::Instruction::TAX}, {"TAY", Token::Instruction::TAY}, {"TBT", Token::Instruction::TBT},
	{"TSX", Token::Instruction::TSX}, {"TXA", Token::Instruction::TXA}, {"TXS", Token::Instruction::TXS},
	{"TYA", Token::Instruction::TYA}, {"XBT", Token::Instruction::XBT},
	{"LDR", Token::Instruction::LDR}, {"STR", Token::Instruction::STR},
	{"PSH", Token::Instruction::PSH}, {"PUL", Token::Instruction::PUL},
	{"NOT", Token::Instruction::NOT},
	{"EXT", Token::Instruction::EXT},
});

static const std::unordered_map<String, Token::Directive> directives_g({
	{"org", Token::Directive::orgDir},
	{"byte", Token::Directive::byteDir},
	{"word", Token::Directive::wordDir},
	{"long", Token::Directive::longDir},
	{"include", Token::Directive::includeDir},
	{"space", Token::Directive::spaceDir},
	{"section", Token::Directive::sectionDir},
	{"if", Token::Directive::ifDir},
	{"else", Token::Directive::elseDir},
	{"endif", Token::Directive::endifDir},
});

static const std::unordered_map<String, Token::Register> registers_g({
	{"A0", Token::Register::A0}, {"A1", Token::Register::A1}, {"A2", Token::Register::A2}, {"A3", Token::Register::A3},
	{"X0", Token::Register::X0}, {"X1", Token::Register::X1}, {"X2", Token::Register::X2}, {"X3", Token::Register::X3},
	{"Y0", Token::Register::Y0}, {"Y1", Token::Register::Y1}, {"Y2", Token::Register::Y2}, {"Y3", Token::Register::Y3},
	{"P", Token::Register::P}, {"Z", Token::Register::Z}, {"SP", Token::Register::SP}, {"PC", Token::Register::PC},

	{"A", Token::Register::A0}, {"X", Token::Register::X0}, {"Y", Token::Register::Y0}
});

Token::Token( size_t pfileIndex, size_t pline, Type tokenType )
{
	fileIndex = pfileIndex;
	line = pline;
	type = tokenType;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, Type tokenType, size_t pos )
{
	fileIndex = pfileIndex;
	line = pline;
	type = tokenType;
	value.pos = pos;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, Instruction instruction )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::instruction;
	value.instruction = instruction;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, Directive directive )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::directive;
	value.directive = directive;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, Register reg )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::reg;
	value.reg = reg;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, uint32_t number )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::number;
	value.number = number;
	labelIsDefinition = false;
}

Token::Token( size_t pfileIndex, size_t pline, const String& string, size_t stringIndex, bool isDefinition )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::label;
	value.labelStringIndex = stringIndex;
	labelIsDefinition = isDefinition;
}

Token::Token( size_t pfileIndex, size_t pline, const String& string )
{
	fileIndex = pfileIndex;
	line = pline;
	type = Type::stringLit;
	value.string = string;
	labelIsDefinition = false;
}

void Token::Print( const Source& source ) const
{
	switch( type )
	{
		case Type::label:
		{
			String str = source.stringPool.GetString(value.labelStringIndex);
			std::string cstr( str.ptr, str.length );
			printf( "l:%s", cstr.c_str() );
			break;
		}
		case Type::stringLit:
		{
			String str = value.string;
			std::string cstr( str.ptr, str.length );
			printf( "\"%s\"", cstr.c_str() );
			break;
		}
		case Type::instruction:
		{
			printf( "i:%s", InstructionName_g[int(value.instruction)] );
			break;
		}
		case Type::directive:
			printf( "%s", DirectiveName_g[int(value.directive)] );
			break;
		case Type::number:
			printf( "%08x", value.number );
			break;
		case Type::reg:
			printf( "r:%s", registerName_g[int(value.reg)] );
			break;
		case Type::lineStart:
		case Type::lineEnd:
		{
			std::string str = source.filenames_m[fileIndex];
			printf( "%s:%s:%08zx", TokenName_g[int(type)], str.c_str(), value.pos );
			break;
		}
		default:
			printf( "%s", TokenName_g[int(type)] );
	}
}

Source::Source( const AsmOptions& options ) : options_m(options)
{
	lineNumber_m = 1;
}

Source::~Source()
{
	for ( auto buffer : sources_m )
	{
		free( buffer );
	}
}

std::string Source::FilePath( const std::string& filename )
{
	size_t pos = filename.find_last_of( "/\\" );
	if ( pos != std::string::npos )
	{
		return filename.substr( 0, pos );
	}
	else
	{
		return std::string("");
	}
}

FILE* Source::FindFile( const char* filename )
{
	FILE* result;
	result = fopen( filename, "rb" );
	if ( result != nullptr )
	{
		currentFile_m = filename;
		return result;
	}
	if ( currentFile_m != "" )
	{
		std::string name = FilePath( currentFile_m ) + "/" + filename;
		result = fopen( name.c_str(), "rb" );
		if ( result != nullptr )
		{
			currentFile_m = name;
			return result;
		}
	}
	for ( auto path : options_m.inputPaths )
	{
		std::string name = path + std::string("/") + filename;
		result = fopen( name.c_str(), "rb" );
		if ( result != nullptr )
		{
			currentFile_m = name;
			return result;
		}
	}
	return nullptr;
}

void Source::AppendFile( const char* filename )
{
	size_t fileIndex = filenames_m.size();
	filenames_m.push_back( std::string(filename) );
	FILE* file = FindFile( filename );
	if ( file == nullptr )
	{
		Error( nullptr, nullptr, "Couldn't open file %s", filename );
	}
	fseek( file, 0, SEEK_END );
	size_t inputLength = ftell( file );
	fseek( file, 0, SEEK_SET );

#if ENABLE_SOURCE_APPEND_DEBUG
	printf( "Appending %s: length %d\n", filename, int(inputLength) );
#endif
	char* text = (char*)malloc( inputLength );
	sources_m.push_back( text );
	fread( text, 1, inputLength, file );
	int currentLineNumber = lineNumber_m;
	lineNumber_m = 1;
	AppendText( text, fileIndex, inputLength );
	// Make sure each file ends with lineEnd
	if ( tokens.back().type != Token::Type::lineEnd )
	{
		tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineEnd, inputLength) );
	}
	lineNumber_m = currentLineNumber;
}

void Source::AppendText( const char* text, size_t fileIndex, size_t length )
{
	size_t pos = 0;
	State state = State::Idle;
	size_t labelStart;
	size_t stringLiteralStart;
	size_t directiveStart;
	int64_t number;
	bool newLine = true;
	bool labelIsDefinition = true;
	int base;
	bool includeDirective = false;
	bool noLineEnd = false;
	char closeQuote = '"';
	bool allowBinaryOp = false;
	while ( pos <= length )
	{
		if ( newLine )
		{
			tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineStart, pos) );
			newLine = false;
		}
		char nextChar = pos < length ? text[pos] : EOF;
		switch( state )
		{
			case State::Idle:
			{
				if ( nextChar == ';' )
				{
					state = State::ReadingComment;
				}
				else if ( nextChar == '.' )
				{
					state = State::ReadingDirective;
					directiveStart = pos+1;
				}
				else if ( nextChar == '\'' )
				{
					state = State::ReadingCharLiteral;
				}
				else if ( nextChar == '"' )
				{
					state = State::ReadingStringLiteral;
					closeQuote = nextChar;
					stringLiteralStart = pos+1;
				}
				else if ( IsDigit(nextChar) )
				{
					state = State::ReadingNumber;
					number = int64_t(nextChar - '0');
					base = 10;
				}
				else if ( nextChar == '$' )
				{
					state = State::ReadingNumberWithBase;
					number = 0;
					base = 16;
				}
				else if ( nextChar == '%' )
				{
					Token* previousToken = nullptr;
					if ( tokens.size() > 0 )
					{
						previousToken = &tokens.back();
					}
					// % can appear in two contexts.  In one, it's a numeric literal prefix for 'binary'
					// In the other, it's the 'mod' operator
					// If the previous token was a label-use (a label that isn't the first thing on a line)
					// a numeric literal, or ')', it's an operator
					bool isOperator = false;
					if ( previousToken != nullptr )
					{
						if ( (previousToken->type == Token::Type::label) && !previousToken->labelIsDefinition ) isOperator = true;
						if ( previousToken->type == Token::Type::number ) isOperator = true;
						if ( previousToken->type == Token::Type::closeParen ) isOperator = true;
					}
					if ( isOperator )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::mod) );
						state = State::Idle;
					}
					else
					{
						state = State::ReadingNumberWithBase;
						number = 0;
						base = 2;
					}
				}
				else if ( IsLetter(nextChar) )
				{
					state = State::ReadingLabel;
					labelStart = pos;
				}
				else if ( nextChar == '=' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::equals) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '(' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::openParen) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == ')' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::closeParen) );
					labelIsDefinition = false;
					allowBinaryOp = true;
				}
				else if ( nextChar == '#' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::hash) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == ',' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::comma) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '+' )
				{
					if ( allowBinaryOp )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::plus) );
					}
					else
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::unaryPlus) );
					}
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '-' )
				{
					if ( allowBinaryOp )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::minus) );
					}
					else
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::unaryMinus) );
					}
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '*' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::star) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '/' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::divide) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '&' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::and) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '|' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::or) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '^' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::xor) );
					labelIsDefinition = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '<' )
				{
					state = State::ReadingLessThan;
					allowBinaryOp = false;
				}
				else if ( nextChar == '>' )
				{
					state = State::ReadingGreaterThan;
					allowBinaryOp = false;
				}
				else if ( nextChar == '!' )
				{
					state = State::ReadingNot;
					allowBinaryOp = false;
				}
				else if ( nextChar == '\r' )
				{
					state = State::ReadingEOL;
					if ( !noLineEnd )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineEnd, pos) );
					}
					includeDirective = false;
					noLineEnd = false;
					allowBinaryOp = false;
				}
				else if ( nextChar == '\n' )
				{
					if ( !noLineEnd )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineEnd, pos) );
					}
					lineNumber_m++;
					includeDirective = false;
					newLine = true;
					noLineEnd = false;
					labelIsDefinition = true;
					allowBinaryOp = false;
				}
				else if ( IsWhiteSpace(nextChar) )
				{
					// whitespace - ignore
				}
				else
				{
					char thisChar = nextChar;
					while ( (nextChar != '\n') && (nextChar != EOF) )
					{
						pos++;
						nextChar = pos < length ? text[pos] : EOF;
					}
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineEnd, pos) );
					labelIsDefinition = true;
					Error( this, &tokens.end(), "syntax error near %c", thisChar );
				}
				pos++;
				break;
			}
			case State::ReadingEOL:
			{
				if ( nextChar == '\n' )
				{
					pos++;
				}
				state = State::Idle;
				newLine = true;
				labelIsDefinition = true;
				lineNumber_m++;
				break;
			}
			case State::ReadingLabel:
			{
				if ( !IsLabelChar(nextChar) )
				{
					String str( text+labelStart, pos-labelStart );
					auto instructionInfo = instructions_g.find( str );
					auto registerInfo = registers_g.find( str );
					bool isLabel = false;
					if ( instructionInfo != instructions_g.end() )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, instructionInfo->second) );
					}
					else if ( registerInfo != registers_g.end() )
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, registerInfo->second) );
					}
					else
					{
						size_t index = stringPool.AddString( str );
						tokens.push_back( Token(fileIndex, lineNumber_m, str, index, labelIsDefinition) );
						isLabel = true;
					}
					allowBinaryOp = isLabel && !labelIsDefinition;
					if ( isLabel && (nextChar == ':') ) pos++;
					labelIsDefinition = false;
					state = State::Idle;
				}
				else
				{
					pos++;
				}
				break;
			}
			case State::ReadingStringLiteral:
			{
				if ( IsEndOfLine(nextChar) )
				{
					Error( this, &tokens.end(), "unterminated string literal" );
				}
				if ( nextChar == closeQuote )
				{
					String str( text+stringLiteralStart, pos-stringLiteralStart );
					if ( includeDirective )
					{
						includeDirective = false;
						std::string cstr( str.ptr, str.length );
						std::string prevFile = currentFile_m;
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lineEnd, pos) );
						labelIsDefinition = true;
						AppendFile( cstr.c_str() );
						currentFile_m = prevFile;
						noLineEnd = true;
						allowBinaryOp = false;
					}
					else
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, str) );
						labelIsDefinition = false;
						allowBinaryOp = false;
					}
					state = State::Idle;
				}
				pos++;
				break;
			}
			case State::ReadingCharLiteral:
			{
				tokens.push_back( Token(fileIndex, lineNumber_m, uint32_t(nextChar)) );
				labelIsDefinition = false;
				allowBinaryOp = true;
				state = State::Idle;
				pos++;
				break;
			}
			case State::ReadingNumber:
			{
				if ( nextChar == '$' )
				{
					base = int(number);
					number = 0;
					state = State::ReadingNumberWithBase;
					pos++;
				}
				else if ( nextChar == '_' )
				{
					pos++;
				}
				else if ( !IsDigit(nextChar) )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, uint32_t(number)) );
					labelIsDefinition = false;
					allowBinaryOp = true;
					state = State::Idle;
				}
				else
				{
					number = base*number + Digit(nextChar, base);
					pos++;
				}
				break;
			}
			case State::ReadingNumberWithBase:
			{
				if ( nextChar == '_' )
				{
					pos++;
				}
				else if ( !IsDigit(nextChar, base) )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, uint32_t(number)) );
					allowBinaryOp = true;
					labelIsDefinition = false;
					state = State::Idle;
				}
				else
				{
					number = base*number + Digit(nextChar, base);
					pos++;
				}
				break;
			}
			case State::ReadingComment:
			{
				if ( IsEndOfLine(nextChar) )
				{
					labelIsDefinition = true;
					state = State::Idle;
				}
				else
				{
					pos++;
				}
				break;
			}
			case State::ReadingDirective:
			{
				if ( !IsLetter(nextChar) )
				{
					String str( text+directiveStart, pos-directiveStart );
					auto directiveInfo = directives_g.find( str );
					if ( directiveInfo != directives_g.end() )
					{
						if ( directiveInfo->second == Token::Directive::includeDir )
						{
							includeDirective = true;
						}
						else
						{
							tokens.push_back( Token(fileIndex, lineNumber_m, directiveInfo->second) );
							labelIsDefinition = true;
						}
					}
					else
					{
						tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::dot) );
						tokens.push_back( Token(fileIndex, lineNumber_m, str) );
						labelIsDefinition = false;
					}
					state = State::Idle;
				}
				else
				{
					pos++;
				}
				break;
			}
			case State::ReadingNot:
			{
				if ( nextChar == '=' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::notEqual) );
					labelIsDefinition = false;
					allowBinaryOp = false;
					state = State::Idle;
					pos++;
				}
				else
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::not) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
				}
				break;
			}
			case State::ReadingLessThan:
			{
				if ( nextChar == '=' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lessEqual) );
					labelIsDefinition = false;
					allowBinaryOp = false;
					state = State::Idle;
					pos++;
				}
				else if ( nextChar == '<' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::shiftLeft) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
					pos++;
				}
				else
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::lowByte) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
				}
				break;
			}
			case State::ReadingGreaterThan:
			{
				if ( nextChar == '=' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::greaterEqual) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
					pos++;
				}
				else if ( nextChar == '>' )
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::shiftRight) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
					pos++;
				}
				else
				{
					tokens.push_back( Token(fileIndex, lineNumber_m, Token::Type::highByte) );
					allowBinaryOp = false;
					labelIsDefinition = false;
					state = State::Idle;
				}
				break;
			}
		}
	}
}

bool Source::IsLetter( char c )
{
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

bool Source::IsDigit( char c, int base )
{
	if ( (base > 10) )
	{
		if ( ((c >= 'a') && (c <= ('a'+base-10))) || ((c >= 'A') && (c <= ('A'+base-10))) )
		{
			return true;
		}
	}
	return (c >= '0') && (c <= '9');
}

bool Source::IsWhiteSpace( char c )
{
	return (c == ' ') || (c == '\t') || IsEndOfLine(c);
}

bool Source::IsEndOfLine( char c )
{
	return (c == '\n') || (c == '\r') || (c == EOF);
}

bool Source::IsLabelChar( char c )
{
	return (c == '_') || IsDigit(c) || IsLetter(c);
}

int Source::Digit( char c, int base )
{
	int result = 0;
	if ( (c >= '0') && (c <= '9') )
	{
		result = c - '0';
	}
	else if ( (c >= 'a') && (c <= 'z') )
	{
		result = c - 'a' + 10;
	}
	else if ( (c >= 'A') && (c <= 'Z') )
	{
		result = c - 'A' + 10;
	}
	else
	{
		Error( this, &tokens.end(), "syntax error: expected a digit" );
	}
	if ( result >= base )
	{
		Error( this, &tokens.end(), "syntax error: digit %s invalid for base %d", c, base );
	}
	return result;
}

void Source::PrintLine( FILE* listing, std::vector<Token>::const_iterator token ) const
{
	if ( tokens.size() == 0 )
	{
		return;
	}
	if ( token == tokens.end() )
	{
		--token;
	}
	while ( (token != tokens.begin()) && (token->type != Token::Type::lineStart) )
	{
		token--;
	}
	size_t start = token->value.pos;
	size_t fileIndex = token->fileIndex;
	while ( (token+1 != tokens.end()) && (token->type != Token::Type::lineEnd) )
	{
		token++;
	}
	size_t end = token->value.pos;
	fwrite( sources_m[fileIndex]+start, 1, end-start, listing );
}

const std::string& Source::GetFilename( size_t index ) const
{
	return filenames_m[index];
}
