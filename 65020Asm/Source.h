#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <new>
#include "StringPool.h"

class Source;

class Token
{
	public:
		enum class Type
		{
			none,
			// label-like tokens
			label, instruction, star, directive, reg, stringLit, charLit,
			// numbers
			number,
			// operators
			// times, less, greater are never produced by the tokeniser.
			// The expression evaluator will substitute it if
			// a *, <, or >  is seen in the right context
			equals, plus, minus, times, divide, mod,
			unaryPlus, unaryMinus,
			and, or, xor, shiftLeft, shiftRight,
			less, greater, greaterEqual, lessEqual, notEqual,
			not, openParen, closeParen,
			// others
			hash, comma, dot, lowByte, highByte,
			// line management
			lineEnd, lineStart,
			// end of source
			sourceEnd
		};
		enum class Instruction
		{
			ABS, ABX, ABY,
			ACX, ACY, ADC, ADD, ADX, ADY, AND, ANX, ANY,
			ASL, ASR, BCC, BCS, BCX, BCY, BEQ, BGE, BGT,
			BHI, BHS, BIC, BIT, BLE, BLS, BLT, BMI, BNE,
			BNV, BPL, BRA, BRK, BVC, BVS, CBT, CCX, CCY,
			CLC, CLD, CLI, CLV, CMP, CPC, CPX, CPY, DEC,
			DEX, DEY, DIV, DVS, EOR, EOX, EOY, ESL, INC,
			INX, INY, JMP, JSR, LDA, LDX, LDY, LSR, MDS,
			MLS, MOD, MOV, MUL, NEG, NGX, NGY, NOP, ORA,
			ORX, ORY, PHA, PHP, PHX, PHY, PLA, PLP, PLX,
			PLY, RLB, ROL, ROR, RRB, RSQ, RTI, RTS,
			SBC, SBT, SBX, SBY, SCX, SCY, SEC, SED,
			SEI, SEV, SQR, STA, STX, STY, SUB, TAX, TAY,
			TBT, TSX, TXA, TXS, TYA, XBT, NOT, NTX, NTY,
			EXT, EXX, EXY,
			// Not permitted in source, used to translate
			// TBT and XBT
			TBT_C, TBT_D, TBT_I, TBT_V,
			XBT_C, XBT_D, XBT_I, XBT_V,
			// Not in InstructionInfo.  Translated into LDx, STx, PHx, PLx
			LDR, STR, PSH, PUL,
			undefined
		};
		enum class Directive
		{
			orgDir, byteDir, wordDir, longDir, includeDir, spaceDir, sectionDir,
			ifDir, elseDir, endifDir
		};
		enum class Register
		{
			A0, A1, A2, A3,
			X0, X1, X2, X3,
			Y0, Y1, Y2, Y3,
			P, Z, SP, PC,
			undefined
		};
		enum class RegisterType { A, X, Y, P, unknown };
		static RegisterType registerType_g[];
		static const char* TokenName_g[];
		static const char* InstructionName_g[];
		static const char* DirectiveName_g[];
		static const char* registerName_g[];

		Token( size_t fileIndex, size_t line, Type tokenType );
		Token( size_t fileIndex, size_t line, Type tokenType, size_t pos );
		Token( size_t fileIndex, size_t line, Instruction instruction );
		Token( size_t fileIndex, size_t line, Directive directive );
		Token( size_t fileIndex, size_t line, Register reg );
		Token( size_t fileIndex, size_t line, uint32_t value );
		Token( size_t fileIndex, size_t line, const String& string, size_t stringIndex, bool isDefinition );	// label
		Token( size_t fileIndex, size_t line, const String& string );						// string literal

		void Print( const Source& source ) const;

		size_t fileIndex;
		size_t line;
		bool labelIsDefinition;
		Type type;
		union ValueUnion
		{
			Instruction instruction;
			Directive directive;
			Register reg;
			uint32_t number;
			size_t labelStringIndex;
			String string;
			size_t pos;
			ValueUnion() {new(&string) String();}
		} value;
};

class AsmOptions;

class Source
{
	public:
		enum class State {
			Idle, ReadingEOL, ReadingLabel, ReadingNumber, ReadingNumberWithBase, ReadingComment, ReadingDirective,
			ReadingStringLiteral, ReadingCharLiteral, ReadingLessThan, ReadingGreaterThan, ReadingNot
		};
		std::vector<Token> tokens;
		StringPool stringPool;

		Source( const AsmOptions& options );
		~Source();

		void AppendFile( const char* filename );
		void AppendText( const char* text, size_t fileIndex, size_t length );

		const std::string& GetFilename( size_t index ) const;
		void PrintLine( FILE* listing, std::vector<Token>::const_iterator token ) const;

	private:
		friend void Token::Print( const Source& source ) const;

		FILE* FindFile( const char* filename );
		std::string FilePath( const std::string& filename );

		const AsmOptions& options_m;

		bool IsLetter( char c );
		bool IsDigit( char c, int base=10 );
		bool IsWhiteSpace( char c );
		bool IsEndOfLine( char c );
		bool IsLabelChar( char c );

		int Digit( char c, int base );

		std::string currentFile_m;
		std::vector<char*> sources_m;
		std::vector<std::string> filenames_m;
		int lineNumber_m;
};

#endif
