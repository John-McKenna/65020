#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "Source.h"
#include "Expression.h"
#include "Output.h"
#include <vector>
#include <unordered_map>
#include <stdio.h>

class Assembler
{
	public:
		Assembler( Source& source, Output& output );
		void Assemble();
		void AssemblePass( FILE* listing = nullptr );

		enum class AddrMode {
			indabs, abs, abs0, absX, absY,
			acc, imm, imp, indzpX, indzpY,
			rel, zp0, zpX, zpY, accExt,
			undefined
		};
		static const char* addrModeName_g[];
		// What the addressing mode looks like from the format of the source
		enum class SourceAddrMode {
			reg,				// reg or nothing
			imm,				// #value
			constant,			// #value (constant encoded into opcode for inc/dec and shift instructions)
			variable,			// reg (for shift instructions)
			mem,				// any mode involving an address, with index and/or indirection

			// EncodeInstruction resolves mem into these
			absX,
			indabs,
			indabsX,
			indabsY,

			undefined
		};
		static const char* sourceAddrModeName_g[];
		enum class InstructionClass
		{
			MainGroup, Branch, BitOp, Move, Unary, IncDec, Shift, BRK, NOP, Jump, Stack, Return
		};

		struct Modifiers
		{
			bool sizeByte;
			bool sizeWord;
			bool sizeLong;
			bool sizeFloat;
			bool indirect;
			bool stack;
			bool wait;
			bool link;

			Modifiers();
		};

		struct ParsedInstruction
		{
			Token::Instruction instruction;
			Modifiers modifiers;
			SourceAddrMode addrMode;
			Token::Register destRegister;
			Token::Register sourceRegister;
			Value constant;
			Value constant2;
			Value address;

			ParsedInstruction();
		};

	private:
		void HandleStar( const Source& source, std::vector<Token>::iterator& token );
		void HandleLabel( const Source& source, std::vector<Token>::iterator& token, FILE* listing );
		void HandleIfElseEndif( const Source& source, std::vector<Token>::iterator& token, FILE* listing );
		void HandleDirective( const Source& source, std::vector<Token>::iterator& token, FILE* listing );
		void HandleInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );

		ParsedInstruction ParseInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseMainGroupInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseBranchInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseBitOpInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseMoveInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseUnaryInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseIncDecInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseShiftInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseBRKInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseNOPInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseJumpInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseStackInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );
		ParsedInstruction ParseReturnInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing );

		void ParseModifier( InstructionClass instructionClass, std::vector<Token>::iterator& token, Modifiers& modifiers );

		void AssignDefaultRegisters( ParsedInstruction& instruction );

		void TranslateMOV( ParsedInstruction& instruction );
		void TranslateCBT( ParsedInstruction& instruction );
		void TranslateSBT( ParsedInstruction& instruction );
		void TranslateInstruction( ParsedInstruction& instruction, const Source& source, std::vector<Token>::iterator& token );

		uint16_t EncodeInstruction( ParsedInstruction instruction, bool& largeOperand, bool largeConstant, AddrMode& addrModeOut, Value& operandOut );
		void EmitOperand( AddrMode addrMode, Value operand, bool largeOperand, const ParsedInstruction& parsedInstruction, bool shiftInstruction, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token );
		void CheckExtensionField( int value, int mask, const char* failMessage, ... );

		Source& source_m;
		Output& output_m;
		std::unordered_map<int, bool> largeOperand_m;
		std::unordered_map<int, bool> largeConstant_m;
		std::vector<Token>::iterator lineStart_m;
		bool sizeDecisionChanged_m;
		bool haveUnknownValues_m;
		bool labelsChanged_m;
		int pass_m;
		bool assemblyEnabled_m;
		std::vector<bool> assemblyEnabledStack_m;
};

#endif
