#include "Assembler.h"
#include "Source.h"
#include "Labels.h"
#include "Expression.h"
#include "InstructionInfo.h"
#include "Errors.h"
#include "Options.h"
#include <utility>
#include <ctype.h>
#include <unordered_set>

#if USE_SMALL_ZP
static const int minBranchOffset_g = -0x80;
static const int maxBranchOffset_g = 0x7f;
static const int maxZPAddr_g = 0xff;
#else
static const int minBranchOffset_g = -0x8000;
static const int maxBranchOffset_g = 0x7fff;
static const int maxZPAddr_g = 0xffff;
#endif
static const int maxConstant_g = 3;

Assembler::Modifiers::Modifiers()
{
	sizeByte = false;
	sizeWord = false;
	sizeLong = false;
	sizeFloat = false;
	indirect = false;
	stack = false;
	wait = false;
	link = false;
}

Assembler::ParsedInstruction::ParsedInstruction()
{
	instruction = Token::Instruction::undefined;
	addrMode = SourceAddrMode::undefined;
	destRegister = Token::Register::undefined;
	sourceRegister = Token::Register::undefined;
	Value constant;
	Value address;
}

const char* Assembler::addrModeName_g[] = {
	"indabs", "abs", "abs0", "absX",
	"absY", "acc", "imm", "imp",
	"indzpX", "indzpY", "rel", "zp0",
	"zpX", "zpY", "accExt"
};

const char* Assembler::sourceAddrModeName_g[] = {
	"reg",
	"imm",
	"constant",
	"variable",
	"mem",
	"absX",
	"indabs",
	"indabsX",
	"indabsY",
	"undefined"
};

static std::unordered_map<Token::Instruction, Token::Register> instructionDefaultDest_g({
	{Token::Instruction::ABX, Token::Register::X0},
	{Token::Instruction::ABY, Token::Register::Y0},
	{Token::Instruction::ACX, Token::Register::X0}, {Token::Instruction::ACY, Token::Register::Y0},
	{Token::Instruction::ADC, Token::Register::A0}, {Token::Instruction::ADD, Token::Register::A0},
	{Token::Instruction::ADX, Token::Register::X0}, {Token::Instruction::ADY, Token::Register::Y0},
	{Token::Instruction::AND, Token::Register::A0}, {Token::Instruction::ANX, Token::Register::X0},
	{Token::Instruction::ANY, Token::Register::Y0}, {Token::Instruction::ASL, Token::Register::A0},
	{Token::Instruction::ASR, Token::Register::A0}, {Token::Instruction::BCX, Token::Register::X0},
	{Token::Instruction::BCY, Token::Register::Y0}, {Token::Instruction::BIC, Token::Register::A0},
	{Token::Instruction::BIT, Token::Register::A0}, {Token::Instruction::BRK, Token::Register::A0},
	{Token::Instruction::CBT, Token::Register::A0}, {Token::Instruction::CCX, Token::Register::X0},
	{Token::Instruction::CCY, Token::Register::Y0}, {Token::Instruction::CMP, Token::Register::A0},
	{Token::Instruction::CPC, Token::Register::A0}, {Token::Instruction::CPX, Token::Register::X0},
	{Token::Instruction::CPY, Token::Register::Y0},
	{Token::Instruction::DEX, Token::Register::X0}, {Token::Instruction::DEY, Token::Register::Y0},
	{Token::Instruction::DIV, Token::Register::A0}, {Token::Instruction::DVS, Token::Register::A0},
	{Token::Instruction::EOR, Token::Register::A0}, {Token::Instruction::EOX, Token::Register::X0},
	{Token::Instruction::EOY, Token::Register::Y0}, {Token::Instruction::ESL, Token::Register::A0},
	{Token::Instruction::INX, Token::Register::X0},
	{Token::Instruction::INY, Token::Register::Y0}, {Token::Instruction::LDA, Token::Register::A0},
	{Token::Instruction::LDX, Token::Register::X0}, {Token::Instruction::LDY, Token::Register::Y0},
	{Token::Instruction::LSR, Token::Register::A0}, {Token::Instruction::MDS, Token::Register::A0},
	{Token::Instruction::MLS, Token::Register::A0}, {Token::Instruction::MOD, Token::Register::A0},
	{Token::Instruction::MUL, Token::Register::A0},
	{Token::Instruction::NGX, Token::Register::X0}, {Token::Instruction::NGY, Token::Register::Y0},
	{Token::Instruction::NTX, Token::Register::X0}, {Token::Instruction::NTY, Token::Register::Y0},
	{Token::Instruction::EXX, Token::Register::X0}, {Token::Instruction::EXY, Token::Register::Y0},
	{Token::Instruction::ORA, Token::Register::A0},
	{Token::Instruction::ORX, Token::Register::X0}, {Token::Instruction::ORY, Token::Register::Y0},
	{Token::Instruction::PHA, Token::Register::A0}, {Token::Instruction::PHP, Token::Register::P},
	{Token::Instruction::PHX, Token::Register::X0}, {Token::Instruction::PHY, Token::Register::Y0},
	{Token::Instruction::PLA, Token::Register::A0}, {Token::Instruction::PLP, Token::Register::P},
	{Token::Instruction::PLX, Token::Register::X0}, {Token::Instruction::PLY, Token::Register::Y0},
	{Token::Instruction::RLB, Token::Register::A0},
	{Token::Instruction::ROL, Token::Register::A0}, {Token::Instruction::ROR, Token::Register::A0},
	{Token::Instruction::RRB, Token::Register::A0}, {Token::Instruction::RSQ, Token::Register::A0},
	{Token::Instruction::SBC, Token::Register::A0},
	{Token::Instruction::SBX, Token::Register::X0}, {Token::Instruction::SBY, Token::Register::Y0},
	{Token::Instruction::SCX, Token::Register::X0}, {Token::Instruction::SCY, Token::Register::Y0},
	{Token::Instruction::SQR, Token::Register::A0}, {Token::Instruction::STA, Token::Register::A0},
	{Token::Instruction::STX, Token::Register::X0}, {Token::Instruction::STY, Token::Register::Y0},
	{Token::Instruction::SUB, Token::Register::A0},
	{Token::Instruction::TAX, Token::Register::X0}, {Token::Instruction::TAY, Token::Register::Y0},
	{Token::Instruction::TSX, Token::Register::X0}, {Token::Instruction::TXA, Token::Register::A0},
	{Token::Instruction::TXS, Token::Register::SP}, {Token::Instruction::TYA, Token::Register::A0},
	{Token::Instruction::CLC, Token::Register::P}, {Token::Instruction::CLD, Token::Register::P},
	{Token::Instruction::CLI, Token::Register::P}, {Token::Instruction::CLV, Token::Register::P},
	{Token::Instruction::SEC, Token::Register::P}, {Token::Instruction::SED, Token::Register::P},
	{Token::Instruction::SEI, Token::Register::P}, {Token::Instruction::SEV, Token::Register::P},
	{Token::Instruction::TBT_C, Token::Register::P}, {Token::Instruction::TBT_D, Token::Register::P},
	{Token::Instruction::TBT_I, Token::Register::P}, {Token::Instruction::TBT_V, Token::Register::P},
	{Token::Instruction::XBT_C, Token::Register::P}, {Token::Instruction::XBT_D, Token::Register::P},
	{Token::Instruction::XBT_I, Token::Register::P}, {Token::Instruction::XBT_V, Token::Register::P}
});

static std::unordered_map<Token::Instruction, Token::Register> instructionDefaultSource_g({
	{Token::Instruction::TAX, Token::Register::A0}, {Token::Instruction::TAY, Token::Register::A0},
	{Token::Instruction::TSX, Token::Register::SP}, {Token::Instruction::TXA, Token::Register::X0},
	{Token::Instruction::TXS, Token::Register::X0}, {Token::Instruction::TYA, Token::Register::Y0}
});

static std::unordered_map<Token::Instruction, Token::Register> instructionDefaultIndex_g({
	{Token::Instruction::RTI, Token::Register::SP}, {Token::Instruction::RTS, Token::Register::SP},
	{Token::Instruction::PLA, Token::Register::SP}, {Token::Instruction::PHA, Token::Register::SP},
	{Token::Instruction::PLX, Token::Register::SP}, {Token::Instruction::PHX, Token::Register::SP},
	{Token::Instruction::PLY, Token::Register::SP}, {Token::Instruction::PHY, Token::Register::SP},
	{Token::Instruction::PLP, Token::Register::SP}, {Token::Instruction::PHP, Token::Register::SP}
});

static bool sourceAddrModeHasNumber_g[] = {
	true,		// indabs
	true,		// abs
	true,		// absX
	true,		// indabsX
	true,		// indabsY
	false,		// acc
	true,		// imm
	false		// undefined
};

static std::unordered_set<Token::Instruction> isBitOperation_g({
	Token::Instruction::CLC, Token::Instruction::CLD, Token::Instruction::CLI, Token::Instruction::CLV,
	Token::Instruction::SEC, Token::Instruction::SED, Token::Instruction::SEI, Token::Instruction::SEV,
});

static std::unordered_map<Token::Instruction, int> bitOperationDefault_g({
	{ Token::Instruction::CLC, 0},
	{ Token::Instruction::CLD, 3},
	{ Token::Instruction::CLI, 2},
	{ Token::Instruction::CLV, 6},
	{ Token::Instruction::SEC, 0},
	{ Token::Instruction::SED, 3},
	{ Token::Instruction::SEI, 2},
	{ Token::Instruction::SEV, 6}
});

static std::unordered_map<Token::Instruction, Assembler::InstructionClass> instructionClass_g({
	{Token::Instruction::ABS, Assembler::InstructionClass::Unary},
	{Token::Instruction::ABX, Assembler::InstructionClass::Unary},
	{Token::Instruction::ABY, Assembler::InstructionClass::Unary},
	{Token::Instruction::ACX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ACY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ADC, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ADD, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ADX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ADY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::AND, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ANX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ANY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ASL, Assembler::InstructionClass::Shift},
	{Token::Instruction::ASR, Assembler::InstructionClass::Shift},
	{Token::Instruction::BCC, Assembler::InstructionClass::Branch},
	{Token::Instruction::BCS, Assembler::InstructionClass::Branch},
	{Token::Instruction::BCX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::BCY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::BEQ, Assembler::InstructionClass::Branch},
	{Token::Instruction::BGE, Assembler::InstructionClass::Branch},
	{Token::Instruction::BGT, Assembler::InstructionClass::Branch},
	{Token::Instruction::BHI, Assembler::InstructionClass::Branch},
	{Token::Instruction::BHS, Assembler::InstructionClass::Branch},
	{Token::Instruction::BIC, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::BIT, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::BLE, Assembler::InstructionClass::Branch},
	{Token::Instruction::BLS, Assembler::InstructionClass::Branch},
	{Token::Instruction::BLT, Assembler::InstructionClass::Branch},
	{Token::Instruction::BMI, Assembler::InstructionClass::Branch},
	{Token::Instruction::BNE, Assembler::InstructionClass::Branch},
	{Token::Instruction::BNV, Assembler::InstructionClass::Branch},
	{Token::Instruction::BPL, Assembler::InstructionClass::Branch},
	{Token::Instruction::BRA, Assembler::InstructionClass::Branch},
	{Token::Instruction::BRK, Assembler::InstructionClass::BRK},
	{Token::Instruction::BVC, Assembler::InstructionClass::Branch},
	{Token::Instruction::BVS, Assembler::InstructionClass::Branch},
	{Token::Instruction::CBT, Assembler::InstructionClass::BitOp},
	{Token::Instruction::CCX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::CCY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::CLC, Assembler::InstructionClass::BitOp},
	{Token::Instruction::CLD, Assembler::InstructionClass::BitOp},
	{Token::Instruction::CLI, Assembler::InstructionClass::BitOp},
	{Token::Instruction::CLV, Assembler::InstructionClass::BitOp},
	{Token::Instruction::CMP, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::CPC, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::CPX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::CPY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::DEC, Assembler::InstructionClass::IncDec},
	{Token::Instruction::DEX, Assembler::InstructionClass::IncDec},
	{Token::Instruction::DEY, Assembler::InstructionClass::IncDec},
	{Token::Instruction::DIV, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::DVS, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::EOR, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::EOX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::EOY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ESL, Assembler::InstructionClass::Shift},
	{Token::Instruction::INC, Assembler::InstructionClass::IncDec},
	{Token::Instruction::INX, Assembler::InstructionClass::IncDec},
	{Token::Instruction::INY, Assembler::InstructionClass::IncDec},
	{Token::Instruction::JMP, Assembler::InstructionClass::Jump},
	{Token::Instruction::JSR, Assembler::InstructionClass::Jump},
	{Token::Instruction::LDA, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::LDX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::LDY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::LSR, Assembler::InstructionClass::Shift},
	{Token::Instruction::MDS, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::MLS, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::MOD, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::MOV, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::MUL, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::NEG, Assembler::InstructionClass::Unary},
	{Token::Instruction::NGX, Assembler::InstructionClass::Unary},
	{Token::Instruction::NGY, Assembler::InstructionClass::Unary},
	{Token::Instruction::NOP, Assembler::InstructionClass::NOP},
	{Token::Instruction::NOT, Assembler::InstructionClass::Unary},
	{Token::Instruction::NTX, Assembler::InstructionClass::Unary},
	{Token::Instruction::NTY, Assembler::InstructionClass::Unary},
	{Token::Instruction::EXT, Assembler::InstructionClass::Unary},
	{Token::Instruction::EXX, Assembler::InstructionClass::Unary},
	{Token::Instruction::EXY, Assembler::InstructionClass::Unary},
	{Token::Instruction::ORA, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ORX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::ORY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::PHA, Assembler::InstructionClass::Stack},
	{Token::Instruction::PHP, Assembler::InstructionClass::Stack},
	{Token::Instruction::PHX, Assembler::InstructionClass::Stack},
	{Token::Instruction::PHY, Assembler::InstructionClass::Stack},
	{Token::Instruction::PLA, Assembler::InstructionClass::Stack},
	{Token::Instruction::PLP, Assembler::InstructionClass::Stack},
	{Token::Instruction::PLX, Assembler::InstructionClass::Stack},
	{Token::Instruction::PLY, Assembler::InstructionClass::Stack},
	{Token::Instruction::RLB, Assembler::InstructionClass::Shift},
	{Token::Instruction::ROL, Assembler::InstructionClass::Shift},
	{Token::Instruction::ROR, Assembler::InstructionClass::Shift},
	{Token::Instruction::RRB, Assembler::InstructionClass::Shift},
	{Token::Instruction::RSQ, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::RTI, Assembler::InstructionClass::Return},
	{Token::Instruction::RTS, Assembler::InstructionClass::Return},
	{Token::Instruction::SBC, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SBT, Assembler::InstructionClass::BitOp},
	{Token::Instruction::SBX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SBY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SCX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SCY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SEC, Assembler::InstructionClass::BitOp},
	{Token::Instruction::SED, Assembler::InstructionClass::BitOp},
	{Token::Instruction::SEI, Assembler::InstructionClass::BitOp},
	{Token::Instruction::SEV, Assembler::InstructionClass::BitOp},
	{Token::Instruction::SQR, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::STA, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::STX, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::STY, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::SUB, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::TAX, Assembler::InstructionClass::Move},
	{Token::Instruction::TAY, Assembler::InstructionClass::Move},
	{Token::Instruction::TBT, Assembler::InstructionClass::BitOp},
	{Token::Instruction::TSX, Assembler::InstructionClass::Move},
	{Token::Instruction::TXA, Assembler::InstructionClass::Move},
	{Token::Instruction::TXS, Assembler::InstructionClass::Move},
	{Token::Instruction::TYA, Assembler::InstructionClass::Move},
	{Token::Instruction::XBT, Assembler::InstructionClass::BitOp},
	{Token::Instruction::LDR, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::STR, Assembler::InstructionClass::MainGroup},
	{Token::Instruction::PSH, Assembler::InstructionClass::Stack},
	{Token::Instruction::PUL, Assembler::InstructionClass::Stack},
});

Assembler::Assembler( Source& source, Output& output ) : source_m(source), output_m(output)
{
	sizeDecisionChanged_m = false;
	haveUnknownValues_m = false;
	labelsChanged_m = false;
	pass_m = 0;
	assemblyEnabled_m = true;
}

// These handlers should leave token pointing to token after their input
void Assembler::HandleStar( const Source& source, std::vector<Token>::iterator& token )
{
	token++;
	if ( token->type != Token::Type::equals )
	{
		Error( &source_m, &token, "Expected =" );
	}
	token++;
	ExpressionEvaluator eval( source, token );
	Value addr = eval.Evaluate( output_m.CurrentLocation() );
	if ( addr.known && (addr.type != Value::Type::number) )
	{
		Error( &source_m, &token, ".org value must be a number" );
	}
	output_m.NewBlock( addr.value.number );
}

void Assembler::HandleLabel( const Source& source, std::vector<Token>::iterator& token, FILE* listing )
{
	std::vector<Token>::const_iterator label = token;
	token++;
	Value value;
	if ( token->type == Token::Type::equals )
	{
		// If followed by = <expression>, assign the value of the expression to the label
		token++;
		ExpressionEvaluator eval( source, token );
		value = eval.Evaluate( output_m.CurrentLocation() );
		output_m.PrintLabel( listing, value.value.number );
	}
	else
	{
		// otherwise assign the current location to the label, and continue with the same line
		value = output_m.CurrentLocation();
		output_m.PrintAddress( listing );
	}
	Value oldValue = GetLabel( source, *label );
	if ( oldValue != value )
	{
		labelsChanged_m = true;
#if ENABLE_ASSEMBLER_PASS_CONTROL_DEBUG
		const String& string = source.stringPool.GetString(label->value.labelStringIndex);
		std::string cstr( string.ptr, string.length );
		printf( "Label changed: %s was ", cstr.c_str() );
		oldValue.Print();
		printf( " now " );
		value.Print();
		printf( "\n" );
#endif
	}
	SetLabel( source, label, value );
}

void Assembler::HandleIfElseEndif( const Source& source, std::vector<Token>::iterator& token, FILE* listing )
{
	switch ( token->value.directive )
	{
		case Token::Directive::ifDir:
		{
			token++;
			assemblyEnabledStack_m.push_back( assemblyEnabled_m );
			ExpressionEvaluator eval(source, token);
			Value value = eval.Evaluate(output_m.CurrentLocation(), false);
			bool enable = true;
			if ( value.known )
			{
				if ( value.type != Value::Type::number )
				{
					Error( &source_m, &token, "Expression isn't a number" );
				}
				enable = value.value.number != 0;
			}
			assemblyEnabled_m = enable && assemblyEnabled_m;
			break;
		}
		case Token::Directive::elseDir:
		{
			token++;
			if ( assemblyEnabledStack_m.size() == 0 )
			{
				Error( &source_m, &token, ".else without .if" );
			}
			assemblyEnabled_m = !assemblyEnabled_m && assemblyEnabledStack_m.back();
			break;
		}
		case Token::Directive::endifDir:
		{
			token++;
			if ( assemblyEnabledStack_m.size() == 0 )
			{
				Error( &source_m, &token, ".endif without .if" );
			}
			assemblyEnabled_m = assemblyEnabledStack_m.back();
			assemblyEnabledStack_m.pop_back();
		}
	}
}

void Assembler::HandleDirective( const Source& source, std::vector<Token>::iterator& token, FILE* listing )
{
	switch ( token->value.directive )
	{
		case Token::Directive::orgDir:
		{
			token++;
			ExpressionEvaluator eval( source, token );
			Value addr = eval.Evaluate( output_m.CurrentLocation() );
			if ( addr.known && (addr.type != Value::Type::number) )
			{
				Error( &source_m, &token, ".org value must be a number" );
			}
			output_m.NewBlock( addr.value.number );
			break;
		}
		case Token::Directive::byteDir:
		case Token::Directive::wordDir:
		case Token::Directive::longDir:
		{
			Token::Directive directive = token->value.directive;
			token++;
			while ( token->type != Token::Type::lineEnd )
			{
				ExpressionEvaluator eval( source, token );
				Value value = eval.Evaluate( output_m.CurrentLocation() );
				// emit value
				switch( directive )
				{
					case Token::Directive::byteDir:
						if ( value.type == Value::Type::string )
						{
							output_m.Emit( value.value.string, listing, source, token );
						}
						else
						{
							output_m.Emit( uint16_t(value.value.number), listing, source, token );
						}
						break;
					case Token::Directive::wordDir:
						output_m.Emit( uint8_t(value.value.number%256), listing, source, token );
						output_m.Emit( uint8_t(value.value.number/256), listing, source, token );
						break;
					case Token::Directive::longDir:
						output_m.Emit( uint32_t(value.value.number), listing, source, token );
						break;
				}
				if ( token->type == Token::Type::lineEnd )
				{
					break;
				}
				if ( token->type == Token::Type::comma )
				{
					token++;
				}
				else
				{
					Error( &source_m, &token, "syntax error" );
				}
			}
			break;
		}
		case Token::Directive::spaceDir:
		{
			token++;
			ExpressionEvaluator eval( source, token );
			Value value = eval.Evaluate( output_m.CurrentLocation() );
			uint32_t n = 0;
			if ( value.known )
			{
				if ( value.type != Value::Type::number )
				{
					Error( &source_m, &token, "Expression isn't a number" );
				}
				n = value.value.number;
			}
			output_m.Skip( n );
			break;
		}
		case Token::Directive::sectionDir:
		{
			token++;
			if ( token->type != Token::Type::label )
			{
				Error( &source_m, &token, "Bad section name" );
			}
			const String& name = source.stringPool.GetString(token->value.labelStringIndex);
			output_m.SwitchToSection( name );
			token++;
			break;
		}
	}
}

typedef std::unordered_map<Token::RegisterType, Token::Instruction> RegisterToInstructionMap;
static std::unordered_map<Token::Instruction, RegisterToInstructionMap> instructionTranslateMap_g({
	{Token::Instruction::ABS,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::ABX},
			{Token::RegisterType::X, Token::Instruction::ABX},
			{Token::RegisterType::Y, Token::Instruction::ABY},
			{Token::RegisterType::P, Token::Instruction::ABY}
		})
	},
	{Token::Instruction::ADC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::ADC},
			{Token::RegisterType::X, Token::Instruction::ACX},
			{Token::RegisterType::Y, Token::Instruction::ACY}
		})
	},
	{Token::Instruction::ADD,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::ADD},
			{Token::RegisterType::X, Token::Instruction::ADX},
			{Token::RegisterType::Y, Token::Instruction::ADY}
		})
	},
	{Token::Instruction::AND,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::AND},
			{Token::RegisterType::X, Token::Instruction::ANX},
			{Token::RegisterType::Y, Token::Instruction::ANY}
		})
	},
	{Token::Instruction::BIC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::BIC},
			{Token::RegisterType::X, Token::Instruction::BCX},
			{Token::RegisterType::Y, Token::Instruction::BCY}
		})
	},
	{Token::Instruction::CMP,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::CMP},
			{Token::RegisterType::X, Token::Instruction::CPX},
			{Token::RegisterType::Y, Token::Instruction::CPY}
		})
	},
	{Token::Instruction::CPC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::CPC},
			{Token::RegisterType::X, Token::Instruction::CCX},
			{Token::RegisterType::Y, Token::Instruction::CCY}
		})
	},
	{Token::Instruction::DEC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::DEX},
			{Token::RegisterType::X, Token::Instruction::DEX},
			{Token::RegisterType::Y, Token::Instruction::DEY},
			{Token::RegisterType::P, Token::Instruction::DEY}
		})
	},
	{Token::Instruction::EOR,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::EOR},
			{Token::RegisterType::X, Token::Instruction::EOX},
			{Token::RegisterType::Y, Token::Instruction::EOY}
		})
	},
	{Token::Instruction::INC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::INX},
			{Token::RegisterType::X, Token::Instruction::INX},
			{Token::RegisterType::Y, Token::Instruction::INY},
			{Token::RegisterType::P, Token::Instruction::INY}
		})
	},
	{Token::Instruction::LDR,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::LDA},
			{Token::RegisterType::X, Token::Instruction::LDX},
			{Token::RegisterType::Y, Token::Instruction::LDY}
		})
	},
	{Token::Instruction::NEG,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::NGX},
			{Token::RegisterType::X, Token::Instruction::NGX},
			{Token::RegisterType::Y, Token::Instruction::NGY},
			{Token::RegisterType::P, Token::Instruction::NGY}
		})
	},
	{Token::Instruction::NOT,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::NTX},
			{Token::RegisterType::X, Token::Instruction::NTX},
			{Token::RegisterType::Y, Token::Instruction::NTY},
			{Token::RegisterType::P, Token::Instruction::NTY}
		})
	},
	{Token::Instruction::EXT,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::EXX},
			{Token::RegisterType::X, Token::Instruction::EXX},
			{Token::RegisterType::Y, Token::Instruction::EXY},
			{Token::RegisterType::P, Token::Instruction::EXY}
		})
	},
	{Token::Instruction::ORA,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::ORA},
			{Token::RegisterType::X, Token::Instruction::ORX},
			{Token::RegisterType::Y, Token::Instruction::ORY}
		})
	},
	{Token::Instruction::PSH,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::PHA},
			{Token::RegisterType::X, Token::Instruction::PHX},
			{Token::RegisterType::Y, Token::Instruction::PHY},
			{Token::RegisterType::P, Token::Instruction::PHP}
		})
	},
	{Token::Instruction::PUL,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::PLA},
			{Token::RegisterType::X, Token::Instruction::PLX},
			{Token::RegisterType::Y, Token::Instruction::PLY},
			{Token::RegisterType::P, Token::Instruction::PLP}
		})
	},
	{Token::Instruction::SBC,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::SBC},
			{Token::RegisterType::X, Token::Instruction::SCX},
			{Token::RegisterType::Y, Token::Instruction::SCY}
		})
	},
	{Token::Instruction::STR,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::STA},
			{Token::RegisterType::X, Token::Instruction::STX},
			{Token::RegisterType::Y, Token::Instruction::STY}
		})
	},
	{Token::Instruction::SUB,
		RegisterToInstructionMap({
			{Token::RegisterType::A, Token::Instruction::SUB},
			{Token::RegisterType::X, Token::Instruction::SBX},
			{Token::RegisterType::Y, Token::Instruction::SBY}
		})
	}
});

static const Token::Instruction CBTInstructions_g[] = {
	Token::Instruction::CLC, Token::Instruction::CLV, Token::Instruction::CLI, Token::Instruction::CLD, 
	Token::Instruction::CLD, Token::Instruction::CLI, Token::Instruction::CLV, Token::Instruction::CLC, 
	Token::Instruction::CLC, Token::Instruction::CLV, Token::Instruction::CLI, Token::Instruction::CLD, 
	Token::Instruction::CLD, Token::Instruction::CLI, Token::Instruction::CLV, Token::Instruction::CLC, 
	Token::Instruction::CLC, Token::Instruction::CLV, Token::Instruction::CLI, Token::Instruction::CLD, 
	Token::Instruction::CLD, Token::Instruction::CLI, Token::Instruction::CLV, Token::Instruction::CLC, 
	Token::Instruction::CLC, Token::Instruction::CLV, Token::Instruction::CLI, Token::Instruction::CLD, 
	Token::Instruction::CLD, Token::Instruction::CLI, Token::Instruction::CLV, Token::Instruction::CLC, 
};

static const Token::Instruction TBTInstructions_g[] = {
	Token::Instruction::TBT_C, Token::Instruction::TBT_V, Token::Instruction::TBT_I, Token::Instruction::TBT_D, 
	Token::Instruction::TBT_D, Token::Instruction::TBT_I, Token::Instruction::TBT_V, Token::Instruction::TBT_C, 
	Token::Instruction::TBT_C, Token::Instruction::TBT_V, Token::Instruction::TBT_I, Token::Instruction::TBT_D, 
	Token::Instruction::TBT_D, Token::Instruction::TBT_I, Token::Instruction::TBT_V, Token::Instruction::TBT_C, 
	Token::Instruction::TBT_C, Token::Instruction::TBT_V, Token::Instruction::TBT_I, Token::Instruction::TBT_D, 
	Token::Instruction::TBT_D, Token::Instruction::TBT_I, Token::Instruction::TBT_V, Token::Instruction::TBT_C, 
	Token::Instruction::TBT_C, Token::Instruction::TBT_V, Token::Instruction::TBT_I, Token::Instruction::TBT_D, 
	Token::Instruction::TBT_D, Token::Instruction::TBT_I, Token::Instruction::TBT_V, Token::Instruction::TBT_C, 
};

static const Token::Instruction SBTInstructions_g[] = {
	Token::Instruction::SEC, Token::Instruction::SEV, Token::Instruction::SEI, Token::Instruction::SED, 
	Token::Instruction::SED, Token::Instruction::SEI, Token::Instruction::SEV, Token::Instruction::SEC, 
	Token::Instruction::SEC, Token::Instruction::SEV, Token::Instruction::SEI, Token::Instruction::SED, 
	Token::Instruction::SED, Token::Instruction::SEI, Token::Instruction::SEV, Token::Instruction::SEC, 
	Token::Instruction::SEC, Token::Instruction::SEV, Token::Instruction::SEI, Token::Instruction::SED, 
	Token::Instruction::SED, Token::Instruction::SEI, Token::Instruction::SEV, Token::Instruction::SEC, 
	Token::Instruction::SEC, Token::Instruction::SEV, Token::Instruction::SEI, Token::Instruction::SED, 
	Token::Instruction::SED, Token::Instruction::SEI, Token::Instruction::SEV, Token::Instruction::SEC, 
};

static const Token::Instruction XBTInstructions_g[] = {
	Token::Instruction::XBT_C, Token::Instruction::XBT_V, Token::Instruction::XBT_I, Token::Instruction::XBT_D, 
	Token::Instruction::XBT_D, Token::Instruction::XBT_I, Token::Instruction::XBT_V, Token::Instruction::XBT_C, 
	Token::Instruction::XBT_C, Token::Instruction::XBT_V, Token::Instruction::XBT_I, Token::Instruction::XBT_D, 
	Token::Instruction::XBT_D, Token::Instruction::XBT_I, Token::Instruction::XBT_V, Token::Instruction::XBT_C, 
	Token::Instruction::XBT_C, Token::Instruction::XBT_V, Token::Instruction::XBT_I, Token::Instruction::XBT_D, 
	Token::Instruction::XBT_D, Token::Instruction::XBT_I, Token::Instruction::XBT_V, Token::Instruction::XBT_C, 
	Token::Instruction::XBT_C, Token::Instruction::XBT_V, Token::Instruction::XBT_I, Token::Instruction::XBT_D, 
	Token::Instruction::XBT_D, Token::Instruction::XBT_I, Token::Instruction::XBT_V, Token::Instruction::XBT_C, 
};

void Assembler::TranslateMOV( ParsedInstruction& instruction )
{
	if ( instruction.instruction != Token::Instruction::MOV ) return;
	Token::RegisterType sourceType = Token::registerType_g[int(instruction.sourceRegister)];
	Token::RegisterType destType = Token::registerType_g[int(instruction.destRegister)];
	if ( (sourceType == Token::RegisterType::A) || (sourceType == Token::RegisterType::Y) )
	{
		if ( (destType == Token::RegisterType::A) || (destType == Token::RegisterType::Y) )
		{
			instruction.instruction = Token::Instruction::TAY;
		}
		else
		{
			instruction.instruction = Token::Instruction::TAX;
		}
	}
	else
	{
		if ( (destType == Token::RegisterType::A) || (destType == Token::RegisterType::Y) )
		{
			instruction.instruction = Token::Instruction::TXA;
		}
		else
		{
			instruction.instruction = Token::Instruction::TXS;
		}
	}
}

void Assembler::TranslateCBT( ParsedInstruction& instruction )
{
	switch ( instruction.instruction )
	{
		case Token::Instruction::CBT:
			instruction.instruction = CBTInstructions_g[instruction.constant.value.number];
			break;
		case Token::Instruction::TBT:
			instruction.instruction = TBTInstructions_g[instruction.constant.value.number];
			break;
		default:
			;
	}
}

void Assembler::TranslateSBT( ParsedInstruction& instruction )
{
	switch ( instruction.instruction )
	{
		case Token::Instruction::SBT:
			instruction.instruction = SBTInstructions_g[instruction.constant.value.number];
			break;
		case Token::Instruction::XBT:
			instruction.instruction = XBTInstructions_g[instruction.constant.value.number];
			break;
		default:
			;
	}
}

void Assembler::TranslateInstruction( ParsedInstruction& instruction, const Source& source, std::vector<Token>::iterator& token )
{
	TranslateMOV( instruction );
	TranslateCBT( instruction );
	TranslateSBT( instruction );
	Token::RegisterType registerType = Token::registerType_g[int(instruction.destRegister)];
	auto instructionInfo = instructionTranslateMap_g.find(instruction.instruction);
	if ( instructionInfo != instructionTranslateMap_g.end() )
	{
		auto registerInfo = instructionInfo->second.find(registerType);
		if ( registerInfo == instructionInfo->second.end() )
		{
			if ( instructionInfo_g[int(instruction.instruction)].size() == 0 )
			{
				// No translation, and the base instruction isn't real
				// (ABS gets translated to ABX if the register is X, but if there is no register there is still
				// a registerless ABS to handle it.  But this doesn't apply to LDR - that must always translate)
				Error( &source_m, &token, "No translation for instruction %s with register %s", Token::InstructionName_g[int(instruction.instruction)], Token::registerName_g[int(instruction.destRegister)] );
			}
		}
		else
		{
			instruction.instruction = registerInfo->second;
		}
	}
}

static bool IsShiftInstruction( Token::Instruction instruction )
{
	switch ( instruction )
	{
		case Token::Instruction::ASL:
		case Token::Instruction::ASR:
		case Token::Instruction::ESL:
		case Token::Instruction::LSR:
		case Token::Instruction::RLB:
		case Token::Instruction::ROL:
		case Token::Instruction::ROR:
		case Token::Instruction::RRB:
			return true;
		default:
			return false;
	}
}

static bool IsBranchInstruction( Token::Instruction instruction )
{
	switch ( instruction )
	{
		case Token::Instruction::BCC:
		case Token::Instruction::BCS:
		case Token::Instruction::BEQ:
		case Token::Instruction::BGE:
		case Token::Instruction::BGT:
		case Token::Instruction::BHI:
		case Token::Instruction::BHS:
		case Token::Instruction::BIC:
		case Token::Instruction::BLE:
		case Token::Instruction::BLS:
		case Token::Instruction::BLT:
		case Token::Instruction::BMI:
		case Token::Instruction::BNE:
		case Token::Instruction::BNV:
		case Token::Instruction::BPL:
		case Token::Instruction::BRA:
		case Token::Instruction::BVC:
		case Token::Instruction::BVS:
			return true;
		default:
			return false;
	}
}

void Assembler::ParseModifier( InstructionClass instructionClass, std::vector<Token>::iterator& token, Modifiers& modifiers )
{
	if ( token->type == Token::Type::dot )
	{
		token++;
		if ( token->type != Token::Type::stringLit )
		{
			Error( &source_m, &token, "expect instruction modifier after ." );
		}
		for ( size_t i = 0; i < token->value.string.length; i++ )
		{
			char modifier = tolower(token->value.string.ptr[i]);
			switch ( modifier )
			{
				case 'b':
					modifiers.sizeByte = true;
					break;
				case 'w':
					modifiers.sizeWord = true;
					break;
				case 'l':
					if ( instructionClass == InstructionClass::Branch )
					{
						modifiers.link = true;
					}
					else
					{
						modifiers.sizeLong = true;
					}
					break;
				case 'f':
					modifiers.sizeFloat = true;
					break;
				case 'i':
					modifiers.wait = true;
					break;
				default:
					Error( &source_m, &token, "unknown modifier %c", token->value.string.ptr[i] );
			}
		}
		token++;
	}
}

static int RegisterNumberOrZero( Token::Register reg )
{
	if ( reg == Token::Register::undefined )
	{
		return 0;
	}
	return int(reg);
}

static void ResolveAddrMode( Assembler::SourceAddrMode& addrMode, Assembler::ParsedInstruction& instruction, const InstructionInfo& instructionInfo, bool largeConstant )
{
	if ( addrMode == Assembler::SourceAddrMode::mem )
	{
		if ( instruction.address.enclosedInParentheses )
		{
			if ( instruction.address.index == Token::Register::undefined )
			{
				// (addr)
				// Used by JMP.  Indirect branches should have P as the index
				// and the I modifier set
				addrMode = Assembler::SourceAddrMode::indabs;
			}
			else
			{
				// (addr,X)
				addrMode = Assembler::SourceAddrMode::indabsX;
			}
		}
		else
		{
			// What happens with (zp),Y?
			addrMode = Assembler::SourceAddrMode::absX;
		}
	}
	bool isShift = IsShiftInstruction(instruction.instruction);
	if ( isShift && (addrMode == Assembler::SourceAddrMode::imm) )
	{
		if ( instruction.constant.known && (instruction.constant.type == Value::Type::number) )
		{
			if ( instruction.constant.value.number == 1 )
			{
				addrMode = Assembler::SourceAddrMode::constant;
			}
			else
			{
				addrMode = Assembler::SourceAddrMode::imm;
			}
		}
		else
		{
			// don't know how to deal with this
			addrMode = Assembler::SourceAddrMode::reg;
		}
	}
	if ( instructionInfo.count(addrMode) == 0 )
	{
		// This instruction doesn't support this addressing mode.  Find an
		// alternative
		switch ( addrMode )
		{
			case Assembler::SourceAddrMode::indabsX:
				if ( IsBranchInstruction(instruction.instruction) )
				{
					addrMode = Assembler::SourceAddrMode::absX;
					instruction.modifiers.indirect = true;
				}
				break;
			case Assembler::SourceAddrMode::indabs:
				addrMode = Assembler::SourceAddrMode::indabsY;
				instruction.address.index = Token::Register::P;
				break;
			default:
				;
		}
	}
}

uint16_t Assembler::EncodeInstruction( ParsedInstruction instruction, bool& largeOperand, bool largeConstant, AddrMode& addrModeOut, Value& operandOut )
{
	Token::Register indexRegister = instruction.address.index;
	Token::Register destRegister = instruction.destRegister;
	Token::Register sourceRegister = instruction.sourceRegister;
	// Instructions that don't use an index need something for the lookup.  If none
	// given, use P (constant 0)
	indexRegister = (indexRegister==Token::Register::undefined) ? Token::Register::P : indexRegister;

	Token::RegisterType destType = Token::registerType_g[int(destRegister)];
	Token::RegisterType indexType = Token::registerType_g[int(indexRegister)];
	int destRegNumber = RegisterNumberOrZero( destRegister );
	int indexRegNumber = RegisterNumberOrZero( indexRegister );
	int sourceRegNumber = RegisterNumberOrZero( sourceRegister );
	if ( instructionDefaultDest_g.count(instruction.instruction) > 0 )
	{
		destRegNumber ^= int(instructionDefaultDest_g[instruction.instruction]);
#if ENABLE_ASSEMBLER_INSTRUCTION_ENCODE_DEBUG
		printf( "\tdest -> %s\n", Token::registerName_g[int(destRegister)] );
#endif
	}
	if ( instructionDefaultSource_g.count(instruction.instruction) > 0 )
	{
#if ENABLE_ASSEMBLER_INSTRUCTION_ENCODE_DEBUG
		printf( "\tdest -> %s\n", Token::registerName_g[int(sourceRegister)] );
#endif
		sourceRegNumber ^= int(instructionDefaultSource_g[instruction.instruction]);
	}
	if ( instructionDefaultIndex_g.count(instruction.instruction) > 0 )
	{
#if ENABLE_ASSEMBLER_INSTRUCTION_ENCODE_DEBUG
		printf( "\tdest -> %s\n", Token::registerName_g[int(indexRegister)] );
#endif
		indexRegNumber ^= int(instructionDefaultIndex_g[instruction.instruction]);
	}
	const InstructionInfo& instructionInfo = instructionInfo_g[int(instruction.instruction)];
	SourceAddrMode sourceAddrMode = instruction.addrMode;
	ResolveAddrMode( sourceAddrMode, instruction, instructionInfo, largeConstant );
	auto info = instructionInfo.find( sourceAddrMode );
	if ( info == instructionInfo.end() )
	{
		Error( &source_m, &lineStart_m, "illegal addressing mode %s for instruction %s", sourceAddrModeName_g[int(sourceAddrMode)], Token::InstructionName_g[int(instruction.instruction)] );
	}
	const OpcodeInfoBySize& opcodeInfoBySize = instructionInfo.find(sourceAddrMode)->second;
	const OpcodeInfo& opcodeInfo = opcodeInfoBySize.size[largeOperand].type[int(indexType)];
	addrModeOut = opcodeInfo.addrMode;
	switch ( addrModeOut )
	{
		case AddrMode::abs0:
		case AddrMode::zp0:
			indexRegNumber ^= int(Token::Register::P);
			break;
		case AddrMode::absX:
		case AddrMode::zpX:
		case AddrMode::indzpX:
			indexRegNumber ^= int(Token::Register::X0);
			break;
		case AddrMode::absY:
		case AddrMode::zpY:
		case AddrMode::indzpY:
			indexRegNumber ^= int(Token::Register::Y0);
			break;
		case AddrMode::acc:
			indexRegNumber = sourceRegNumber;
			break;
		case AddrMode::rel:
			if ( indexRegister != Token::Register::PC )
			{
				// If the index register isn't PC, use the offset given directly
				if ( largeOperand )
				{
					addrModeOut = AddrMode::abs;
				}
				else
				{
					addrModeOut = AddrMode::zp0;
				}
			}
			indexRegNumber ^= int(Token::Register::PC);
	}
	ExtensionFormat extensionFormat = opcodeInfo.extensionFormat;
	uint16_t opcode = opcodeInfo.opcode;
	int dataSize = 0;
	if ( (instruction.addrMode == SourceAddrMode::imm) && !instruction.modifiers.sizeByte && !instruction.modifiers.sizeWord && !instruction.modifiers.sizeLong && !instruction.modifiers.sizeFloat )
	{
		// No explicit size given, and an immediate operand
		if ( instruction.address.value.number > 0xff ) dataSize = 1;
		if ( instruction.address.value.number > 0xffff ) dataSize = 2;
	}
	if ( instruction.modifiers.sizeWord ) dataSize = 1;
	if ( instruction.modifiers.sizeLong ) dataSize = 2;
	if ( instruction.modifiers.sizeFloat ) dataSize = 3;
	int nn = 1;
	if ( instruction.constant.known )
	{
		nn = instruction.constant.value.number;
	}
	int vv = 0;
	if ( instruction.constant2.known )
	{
		vv = instruction.constant2.value.number;
	}
	switch ( extensionFormat )
	{
		case ExtensionFormat::PRRXXXDD:
		{
			CheckExtensionField( destRegNumber, 3, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( indexRegNumber, 7, "Illegal index register %s", Token::registerName_g[int(indexRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= ((destRegNumber&3)<<13) | ((indexRegNumber&7)<<10) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::PRR___DD:
		{
			CheckExtensionField( destRegNumber, 3, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= ((destRegNumber&3)<<13) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::PRRRR_DD:
		{
			CheckExtensionField( destRegNumber, 15, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= ((destRegNumber&15)<<11) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::PNNXXXDD:
		{
			int encodedNum = nn-1;
			CheckExtensionField( encodedNum, 3, "Illegal constant" );
			CheckExtensionField( indexRegNumber, 7, "Illegal index register %s", Token::registerName_g[int(indexRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= (encodedNum<<13) | ((indexRegNumber&7)<<10) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::P_RRRRDD:
		{
			CheckExtensionField( destRegNumber, 15, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= ((destRegNumber&15)<<10) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::PSRRRRDD:
		{
			CheckExtensionField( destRegNumber, 15, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			if ( sourceRegister == Token::Register::undefined )
			{
				// no shift amount register: following byte is shift amount
				opcode |= (0 << 14) | ((destRegNumber&15)<<10) | (dataSize<<8);
			}
			else
			{
				// have shift amount register: following byte is shift amount register
				opcode |= (1 << 14) | ((destRegNumber&15)<<10) | (dataSize<<8);
			}
			break;
		}
		case ExtensionFormat::PNNRRRDD:
		{
			int encodedNum = nn-1;
			CheckExtensionField( encodedNum, 3, "Illegal constant" );
			CheckExtensionField( destRegNumber, 7, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( dataSize, 3, "Illegal data size" );
			opcode |= (encodedNum<<13) | ((destRegNumber&7)<<10) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::PAAARRRR:
		{
			indexRegNumber = destRegNumber;
			// fallthrough
		}
		case ExtensionFormat::PAAAXXXX:
		{
			int instructionBitNumber = 0;
			switch ( instruction.instruction )
			{
				case Token::Instruction::CLC: case Token::Instruction::TBT_C:
				case Token::Instruction::SEC: case Token::Instruction::XBT_C:
					instructionBitNumber = 0;
					break;
				case Token::Instruction::CLD: case Token::Instruction::TBT_D:
				case Token::Instruction::SED: case Token::Instruction::XBT_D:
					instructionBitNumber = 3;
					break;
				case Token::Instruction::CLI: case Token::Instruction::TBT_I:
				case Token::Instruction::SEI: case Token::Instruction::XBT_I:
					instructionBitNumber = 2;
					break;
				case Token::Instruction::CLV: case Token::Instruction::TBT_V:
				case Token::Instruction::SEV: case Token::Instruction::XBT_V:
					instructionBitNumber = 6;
					break;
			}
			int aaa = (nn ^ instructionBitNumber) >> 2;
			CheckExtensionField( aaa, 15, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( indexRegNumber, 15, "Illegal source or index register %s", Token::registerName_g[int(indexRegister)] );
			opcode |= (aaa<<12) | ((indexRegNumber&15)<<8);
			break;
		}
		case ExtensionFormat::WNNNVVVV:
		{
			if ( instruction.modifiers.wait )
			{
				opcode |= 0x80000000;
			}
			CheckExtensionField( nn, 7, "Illegal interrupt number" );
			opcode |= nn << 12;
			CheckExtensionField( vv, 15, "Illegal vector number" );
			opcode |= vv;
			break;
		}
		case ExtensionFormat::NNNNNNNN:
		{
			int encodedNumber = nn-1;
			CheckExtensionField( encodedNumber, 255, "Illegal constant" );
			opcode |= encodedNumber << 8;
			break;
		}
		case ExtensionFormat::RRRSSSDD:
		{
			destRegNumber = (destRegNumber&3) | ((destRegNumber&8)>>1);
			sourceRegNumber = (sourceRegNumber&3) | ((sourceRegNumber&8)>>1);
			CheckExtensionField( destRegNumber, 7, "Illegal dest register %s", Token::registerName_g[int(destRegister)] );
			CheckExtensionField( sourceRegNumber, 7, "Illegal source register %s", Token::registerName_g[int(sourceRegister)] );
			opcode |= ((destRegNumber&7) << 13) | ((sourceRegNumber&7) << 10) | (dataSize<<8);
			break;
		}
		case ExtensionFormat::P_______:
		{
			break;
		}
		case ExtensionFormat::branch:
		{
			CheckExtensionField( destRegNumber, 15, "Illegal base register %s", Token::registerName_g[int(destRegister)] );
			opcode |= (dataSize<<14) | (instruction.modifiers.indirect<<13) | (instruction.modifiers.link<<12) | ((indexRegNumber&15)<<8);
			break;
		}
		case ExtensionFormat::none:
		{
			Error( &source_m, &lineStart_m, "instruction %s can't use addressing mode %s with index %s", Token::InstructionName_g[int(instruction.instruction)], sourceAddrModeName_g[int(sourceAddrMode)], Token::registerName_g[int(indexRegister)] );
		}
		default:
		{
			Error( &source_m, &lineStart_m, "unknown extension format %d", extensionFormat );
		}
	}

	operandOut = instruction.address;
	// ASL[.size] reg [, #n]	-- reg, source undefined
	// ASL[.size] reg, reg		-- variable
	// ASL[.size] expr [, #n]	-- mem
	bool isShift = IsShiftInstruction(instruction.instruction);
	if ( isShift )
	{
		switch ( instruction.addrMode )
		{
			case SourceAddrMode::imm:
				operandOut = instruction.constant;
				largeOperand = false;
				break;
			case SourceAddrMode::reg:
				operandOut.type = Value::Type::number;
				operandOut.value.number = (int)instruction.sourceRegister;
				operandOut.known = true;
				largeOperand = false;
				break;
			case SourceAddrMode::mem:
				break;
			default:
			Error( &source_m, &lineStart_m, "Somehow got an unrecognised addressing mode %s in a shift instruction", sourceAddrModeName_g[int(sourceAddrMode)] );
		}
	}
	return opcode;
}

void Assembler::CheckExtensionField( int value, int mask, const char* failMessage, ... )
{
	if ( value != (value & mask) )
	{
		va_list args;
		va_start( args, failMessage );
		Error( &source_m, &lineStart_m, failMessage, args );
		va_end( args );
	}
}

void Assembler::EmitOperand( AddrMode addrMode, Value operand, bool largeOperand, const ParsedInstruction& parsedInstruction, bool shiftInstruction, FILE* listing, const Source& source, std::vector<Token>::const_iterator& token )
{
	int emitSize = 0;
	uint32_t outAddr = 0;
	if ( operand.known )
	{
		outAddr = operand.value.number;
	}
	switch ( addrMode )
	{
		// emit operand
		// if any involve an unknown value, set haveUnknownValues_m
		case AddrMode::indabs:
		case AddrMode::abs:
		case AddrMode::abs0:
		case AddrMode::absX:
		case AddrMode::absY:
			emitSize = 2;
			break;
		case AddrMode::indzpX:
		case AddrMode::indzpY:
		case AddrMode::zp0:
		case AddrMode::zpX:
		case AddrMode::zpY:
			emitSize = 1;
			break;
		case AddrMode::imm:
			emitSize = largeOperand ? 2 : 1;
			break;
		case AddrMode::rel:
		{
			emitSize = largeOperand ? 2 : 1;
			outAddr -= emitSize + 1;
			int bit7 = (outAddr >> 7) & 1;
			if ( !largeOperand && (bit7 == 1) )
			{
				outAddr ^= 0xff00;
			}
			break;
		}
		case AddrMode::accExt:
			emitSize = 1;
			break;
	}
	if ( emitSize == 0 )
	{
		return;
	}
	if ( (pass_m > 1) && (!operand.known) )
	{
		Error( &source_m, &lineStart_m, "Undefined label" );
	}
	haveUnknownValues_m = haveUnknownValues_m || !operand.known;
	if ( operand.known && (parsedInstruction.addrMode == SourceAddrMode::imm) )
	{
		if ( parsedInstruction.modifiers.sizeByte )
		{
			if ( (outAddr > 0xff ) && ((outAddr >> 8) != 0xffffff) )
			{
				Error( &source_m, &lineStart_m, "Immediate operand too large for .b" );
			}
			outAddr = outAddr & 0xff;
			emitSize = 1;
		}
		if ( parsedInstruction.modifiers.sizeWord )
		{
			if ( (outAddr > 0xffff ) && ((outAddr >> 16) != 0xffff) )
			{
				Error( &source_m, &lineStart_m, "Immediate operand too large for .w" );
			}
			outAddr = outAddr & 0xffff;
			emitSize = 1;
		}
	}
#if ENABLE_ASSEMBLER_PASS_CONTROL_DEBUG
	if ( !operand.known )
	{
		printf( "unknown address: file %d line %d", (int)token->fileIndex, (int)token->line );
		source_m.PrintLine( stdout, token );
		printf( "\n" );
	}
#endif
	if ( emitSize == 1 )
	{
		output_m.Emit( uint16_t(outAddr), listing, source, token );
	}
	else
	{
		output_m.Emit( uint32_t(outAddr), listing, source, token );
	}
}

// AND[.size] [rd,] rs
//                  #imm
//                  expr
Assembler::ParsedInstruction Assembler::ParseMainGroupInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::MainGroup, token, request.modifiers );

	Token::Register firstReg = Token::Register::undefined;

	if ( token->type == Token::Type::reg )
	{
		firstReg = token->value.reg;
		token++;
		if ( token->type == Token::Type::comma )
		{
			token++;
		}
		else if ( token->type != Token::Type::lineEnd )
		{
			Error( &source, &token, "Expected a comma after register" );
		}
	}

	switch ( token->type )
	{
		case Token::Type::reg:
		{
			// ADD rd, rs
			// We know there are two explicit registers, because if there was only one,
			// ParseOptionalReg() would have taken it. 
			request.destRegister = firstReg;
			request.sourceRegister = token->value.reg;
			request.addrMode = SourceAddrMode::reg;
			token++;
			break;
		}
		case Token::Type::hash:
		{
			// ADD [rd,] #expr
			token++;
			ExpressionEvaluator expressionEvaluator(source, token);
			request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
			request.destRegister = firstReg;
			request.addrMode = SourceAddrMode::imm;
			break;
		}
		case Token::Type::lineEnd:
		{
			// ADD rs
			request.destRegister = Token::Register::undefined;
			request.sourceRegister = firstReg;
			request.addrMode = SourceAddrMode::reg;
			break;
		}
		default:
		{
			// ADD [rd,] <expr>
			ExpressionEvaluator expressionEvaluator(source, token);
			request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
			request.destRegister = firstReg;
			request.addrMode = SourceAddrMode::mem;
			if ( (request.address.index == Token::Register::undefined) && (token->type == Token::Type::comma) )
			{
				token++;
				if ( token->type == Token::Type::reg )
				{
					request.address.index = token->value.reg;
					token++;
					// Is it (expr),Y?
					if ( request.address.enclosedInParentheses )
					{
						request.addrMode = SourceAddrMode::indabsY;
					}
				}
				else
				{
					Error( &source, &token, "Expected an index register" );
				}
			}
		}
	}
	return request;
}

// BEQ[.l] addr
// BEQ[.l] offset, rs
// BEQ[.l] (addr)
// BEQ[.l] (offset, rs)
Assembler::ParsedInstruction Assembler::ParseBranchInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::Branch, token, request.modifiers );

	ExpressionEvaluator expressionEvaluator(source, token);
	request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
	request.addrMode = SourceAddrMode::mem;

	if ( (request.address.index == Token::Register::undefined) && (token->type == Token::Type::comma) )
	{
		token++;
		if ( token->type == Token::Type::reg )
		{
			request.address.index = token->value.reg;
			token++;
		}
		else
		{
			Error( &source, &token, "Expected an index register" );
		}
	}

	return request;
}

// CLC
// CBT[.s] rd, #n
// CBT[.s] addr, #n
// CBT[.s] addr, ri, #n
Assembler::ParsedInstruction Assembler::ParseBitOpInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::Move, token, request.modifiers );

	switch ( token->type )
	{
		case Token::Type::lineEnd:
		{
			// CLC
			auto bitnum = bitOperationDefault_g.find( request.instruction );
			if ( bitnum == bitOperationDefault_g.end() )
			{
				Error( &source, &token, "Must specify a destination and bit number" );
			}
			request.destRegister = Token::Register::P;
			request.constant.known = true;
			request.constant.index = Token::Register::undefined;
			request.constant.type = Value::Type::number;
			request.constant.value.number = bitnum->second;
			request.addrMode = SourceAddrMode::reg;
			break;
		}
		case Token::Type::reg:
		{
			// CBT reg, #n
			request.destRegister = token->value.reg;
			token++;
			if ( token->type != Token::Type::comma )
			{
				Error( &source, &token, "Expected bit number" );
			}
			token++;
			if ( token->type == Token::Type::hash )
			{
				token++;
				ExpressionEvaluator expressionEvaluator(source, token);
				request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
			}
			else
			{
				Error( &source, &token, "Expected bit number" );
			}
			request.addrMode = SourceAddrMode::reg;
			break;
		}
		default:
		{
			// CBT addr [, ri], #n
			ExpressionEvaluator expressionEvaluator(source, token);
			request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
			if ( token->type != Token::Type::comma )
			{
				Error( &source, &token, "Expected bit number" );
			}
			token++;
			if ( token->type == Token::Type::reg )
			{
				request.address.index = token->value.reg;
				token++;
				if ( token->type != Token::Type::comma )
				{
					Error( &source, &token, "Expected bit number" );
				}
				token++;
			}
			if ( token->type == Token::Type::hash )
			{
				token++;
				ExpressionEvaluator expressionEvaluator(source, token);
				request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
			}
			else
			{
				Error( &source, &token, "Expected bit number" );
			}
			request.addrMode = SourceAddrMode::mem;
		}
	}
	if ( request.modifiers.sizeByte && (request.constant.type == Value::Type::number) && (request.constant.value.number > 7) )
	{
		Error( &source, &token, "Bit number too high for byte operation" );
	}
	if ( request.modifiers.sizeWord && (request.constant.type == Value::Type::number) )
	{
		if ( request.constant.value.number > 15 )
		{
			Error( &source, &token, "Bit number too high for word operation" );
		}
		if ( request.constant.value.number > 7 )
		{
			// Bit 8-15 for words is 16-23 for longs
			request.constant.value.number += 8;
		}
	}
	return request;
}

// TAX[.size]
// MOV[.size] rd, rs
Assembler::ParsedInstruction Assembler::ParseMoveInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::Move, token, request.modifiers );

	if ( request.instruction == Token::Instruction::MOV )
	{
		if ( token->type != Token::Type::reg )
		{
			Error( &source, &token, "Expected destination register" );
		}
		request.destRegister = token->value.reg;
		token++;
		if ( token->type != Token::Type::comma )
		{
			Error( &source, &token, "Expected comma" );
		}
		token++;
		if ( token->type != Token::Type::reg )
		{
			Error( &source, &token, "Expected source register" );
		}
		request.sourceRegister = token->value.reg;
		token++;
		request.addrMode = SourceAddrMode::reg;
	}
	else
	{
		request.addrMode = SourceAddrMode::reg;
	}
	return request;
}

// ABS[.size] reg				// reg
// ABS[.size] expr				// mem
Assembler::ParsedInstruction Assembler::ParseUnaryInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::Unary, token, request.modifiers );

	if ( token->type == Token::Type::reg )
	{
		request.destRegister = token->value.reg;
		request.addrMode = SourceAddrMode::reg;
		token++;
	}
	else
	{
		ExpressionEvaluator expressionEvaluator(source, token);
		request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
		request.addrMode = SourceAddrMode::mem;
		if ( (request.address.index == Token::Register::undefined) && (token->type == Token::Type::comma) && ((token+1)->type == Token::Type::reg) )
		{
			token++;
			request.address.index = token->value.reg;
			token++;
		}
	}
	return request;
}

// DEC[.size] reg [, #n]		// imm
// DEC[.size] expr [, #n]		// mem
Assembler::ParsedInstruction Assembler::ParseIncDecInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.constant.value.number = 1;
	request.constant.type = Value::Type::number;
	request.constant.known = true;
	token++;
	ParseModifier( InstructionClass::IncDec, token, request.modifiers );

	switch ( request.instruction )
	{
		case Token::Instruction::INX:
		case Token::Instruction::DEX:
			request.destRegister = Token::Register::X0;
			break;
		case Token::Instruction::INY:
		case Token::Instruction::DEY:
			request.destRegister = Token::Register::Y0;
			break;
		default:
			;
	}

	if ( token->type == Token::Type::lineEnd )
	{
		request.addrMode = SourceAddrMode::reg;
	}
	else if ( token->type == Token::Type::reg )
	{
		request.destRegister = token->value.reg;
		request.addrMode = SourceAddrMode::reg;
		token++;
	}
	else
	{
		ExpressionEvaluator expressionEvaluator(source, token);
		request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
		request.addrMode = SourceAddrMode::mem;
		if ( (request.address.index == Token::Register::undefined) && (token->type == Token::Type::comma) && ((token+1)->type == Token::Type::reg) )
		{
			token++;
			request.address.index = token->value.reg;
			token++;
		}
	}
	if ( token->type == Token::Type::comma )
	{
		token++;
		if ( token->type == Token::Type::hash )
		{
			token++;
			ExpressionEvaluator expressionEvaluator(source, token);
			request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
			// Keep the previously-assigned constant or mem mode.
		}
		else
		{
			Error( &source, &token, "Expected a constant" );
		}
	}
	return request;
}

// ASL[.size] reg			-- imm
// ASL[.size] reg [, #n]	-- imm
// ASL[.size] reg, reg		-- reg
// ASL[.size] expr [, #n]	-- mem
Assembler::ParsedInstruction Assembler::ParseShiftInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	token++;
	ParseModifier( InstructionClass::Shift, token, request.modifiers );
	// If we don't get an explicit constant, assume 1
	request.constant.value.number = 1;
	request.constant.type = Value::Type::number;
	request.constant.known = true;

	if ( token->type == Token::Type::reg )
	{
		request.destRegister = token->value.reg;
		request.addrMode = SourceAddrMode::imm;
		token++;
	}
	else if ( token->type == Token::Type::lineEnd )
	{
		auto reg = instructionDefaultDest_g.find( request.instruction );
		if ( reg != instructionDefaultDest_g.end() )
		{
			request.destRegister = reg->second;
			request.addrMode = SourceAddrMode::imm;
		}
	}
	else
	{
		ExpressionEvaluator expressionEvaluator(source, token);
		request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), true);
		request.addrMode = SourceAddrMode::mem;
		if ( (request.address.index == Token::Register::undefined) && (token->type == Token::Type::comma) && ((token+1)->type == Token::Type::reg) )
		{
			token++;
			request.address.index = token->value.reg;
			token++;
		}
	}
	if ( token->type == Token::Type::comma )
	{
		token++;
		if ( token->type == Token::Type::reg )
		{
			request.sourceRegister = token->value.reg;
			// This is messy, because addrMode is used to communicate both the thing being
			// shifted and the amount it is shifted by
			// imm means "shifting a register by a constant amount"
			// reg means "shifting a register by a variable amount"
			// mem means "shifting memory by a constant amount"
			if ( request.addrMode == SourceAddrMode::imm ) request.addrMode = SourceAddrMode::reg;
			token++;
		}
		else if ( token->type == Token::Type::hash )
		{
			token++;
			ExpressionEvaluator expressionEvaluator(source, token);
			request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
		}
		else
		{
			Error( &source, &token, "Expected a constant or register" );
		}
	}
	return request;
}

// BRK
// BRK #n
// BRK #n, #n
Assembler::ParsedInstruction Assembler::ParseBRKInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.addrMode = SourceAddrMode::reg;
	request.constant.value.number = 0;
	request.constant.type = Value::Type::number;
	request.constant.known = true;
	token++;

	if ( token->type == Token::Type::hash )
	{
		// vector number
		token++;
		ExpressionEvaluator expressionEvaluator(source, token);
		request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
	}
	if ( token->type == Token::Type::comma )
	{
		token++;
		if ( token->type != Token::Type::hash )
		{
			Error( &source, &token, "expected an interrupt number" );
		}
		token++;
		// interrupt number
		ExpressionEvaluator expressionEvaluator(source, token);
		request.constant2 = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
	}

	return request;
}

// NOP
// NOP #n
Assembler::ParsedInstruction Assembler::ParseNOPInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.addrMode = SourceAddrMode::reg;
	token++;

	if ( token->type == Token::Type::hash )
	{
		token++;
		ExpressionEvaluator expressionEvaluator(source, token);
		request.constant = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);
	}

	return request;
}

// JMP addr
// JMP (addr)
// JSR addr
// JSR (rs), addr
Assembler::ParsedInstruction Assembler::ParseJumpInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.addrMode = SourceAddrMode::mem;
	token++;

	if ( (token->type == Token::Type::openParen) && ((token+1)->type == Token::Type::reg) )
	{
		token++;
		request.sourceRegister = token->value.reg;
		token++;
		if ( token->type != Token::Type::closeParen)
		{
			Error( &source, &token, "Expected (sp)" );
		}
		token++;
		if ( token->type != Token::Type::comma )
		{
			Error( &source, &token, "Expected a comma after stack pointer" );
		}
		token++;
	}

	ExpressionEvaluator expressionEvaluator(source, token);
	request.address = expressionEvaluator.Evaluate(output_m.CurrentLocation(), false);

	return request;
}

// PSH[.size] reg
Assembler::ParsedInstruction Assembler::ParseStackInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.addrMode = SourceAddrMode::reg;
	token++;
	ParseModifier( InstructionClass::Stack, token, request.modifiers );

	request.address.index = Token::Register::SP;
	switch ( request.instruction )
	{
		case Token::Instruction::PHA:
		case Token::Instruction::PLA:
			request.destRegister = Token::Register::A0;
			break;
		case Token::Instruction::PHX:
		case Token::Instruction::PLX:
			request.destRegister = Token::Register::X0;
			break;
		case Token::Instruction::PHY:
		case Token::Instruction::PLY:
			request.destRegister = Token::Register::Y0;
			break;
		case Token::Instruction::PHP:
		case Token::Instruction::PLP:
			request.destRegister = Token::Register::P;
			break;
		default:
			;
	}

	if ( token->type == Token::Type::openParen )
	{
		token++;
		if ( token->type != Token::Type::reg ) Error( &source, &token, "Expected a stack pointer register" );
		request.address.index = token->value.reg;
		token++;
		if ( token->type != Token::Type::closeParen ) Error( &source, &token, "Expected a )" );
		token++;
		if ( token->type != Token::Type::comma ) Error( &source, &token, "Expected a ," );
		token++;
	}

	if ( token->type == Token::Type::reg )
	{
		request.destRegister = token->value.reg;
		token++;
	}
	else if ( token->type != Token::Type::lineEnd )
	{
		Error( &source, &token, "Expected a register" );
	}

	return request;
}

// RTS
// RTS (rs)
Assembler::ParsedInstruction Assembler::ParseReturnInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	ParsedInstruction request;
	request.instruction = token->value.instruction;
	request.addrMode = SourceAddrMode::reg;
	token++;

	if ( (token->type == Token::Type::openParen) && ((token+1)->type == Token::Type::reg) )
	{
		token++;
		request.sourceRegister = token->value.reg;
		token++;
		if ( token->type != Token::Type::closeParen )
		{
			Error( &source, &token, "Expected (sp)" );
		}
		token++;
	}

	return request;
}

Assembler::ParsedInstruction Assembler::ParseInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	InstructionClass instructionClass = instructionClass_g[token->value.instruction];
	switch ( instructionClass )
	{
		case InstructionClass::MainGroup:
			return ParseMainGroupInstruction( source, token, lineNumber, listing );
		case InstructionClass::Branch:
			return ParseBranchInstruction( source, token, lineNumber, listing );
		case InstructionClass::BitOp:
			return ParseBitOpInstruction( source, token, lineNumber, listing );
		case InstructionClass::Move:
			return ParseMoveInstruction( source, token, lineNumber, listing );
		case InstructionClass::Unary:
			return ParseUnaryInstruction( source, token, lineNumber, listing );
		case InstructionClass::IncDec:
			return ParseIncDecInstruction( source, token, lineNumber, listing );
		case InstructionClass::Shift:
			return ParseShiftInstruction( source, token, lineNumber, listing );
		case InstructionClass::BRK:
			return ParseBRKInstruction( source, token, lineNumber, listing );
		case InstructionClass::NOP:
			return ParseNOPInstruction( source, token, lineNumber, listing );
		case InstructionClass::Jump:
			return ParseJumpInstruction( source, token, lineNumber, listing );
		case InstructionClass::Stack:
			return ParseStackInstruction( source, token, lineNumber, listing );
		case InstructionClass::Return:
			return ParseReturnInstruction( source, token, lineNumber, listing );
		default:
			ParsedInstruction result;
			result.instruction = Token::Instruction::undefined;
			return result;
	}
}

void Assembler::AssignDefaultRegisters( ParsedInstruction& instruction )
{
	if ( instruction.destRegister == Token::Register::undefined )
	{
		auto reg = instructionDefaultDest_g.find( instruction.instruction );
		if ( reg != instructionDefaultDest_g.end() )
		{
			instruction.destRegister = reg->second;
		}
	}
	if ( instruction.sourceRegister == Token::Register::undefined )
	{
		auto reg = instructionDefaultSource_g.find( instruction.instruction );
		if ( reg != instructionDefaultSource_g.end() )
		{
			instruction.sourceRegister = reg->second;
		}
	}
	if ( instruction.address.index == Token::Register::undefined )
	{
		auto reg = instructionDefaultIndex_g.find( instruction.instruction );
		if ( reg != instructionDefaultIndex_g.end() )
		{
			instruction.address.index = reg->second;
		}
	}
}

void Assembler::HandleInstruction( const Source& source, std::vector<Token>::iterator& token, int lineNumber, FILE* listing )
{
	InstructionClass instructionClass = instructionClass_g[token->value.instruction];
	ParsedInstruction parsedInstruction = ParseInstruction( source, token, lineNumber, listing );

	AssignDefaultRegisters( parsedInstruction );

	bool largeOperand = false;
	bool largeConstant = false;
	if ( parsedInstruction.modifiers.sizeLong && (parsedInstruction.addrMode == SourceAddrMode::imm) )
	{
		largeOperand = true;
	}

	if ( (instructionClass == InstructionClass::Branch) && (parsedInstruction.address.index == Token::Register::undefined) && parsedInstruction.address.known )
	{
		uint32_t destAddr = parsedInstruction.address.value.number;
		// Make it relative to PC
		parsedInstruction.address.index = Token::Register::PC;
		parsedInstruction.address.value.number = parsedInstruction.address.value.number - output_m.CurrentLocation().value.number;
		int offset = int(parsedInstruction.address.value.number);
		if ( parsedInstruction.address.known && ((offset-2 < minBranchOffset_g) || (offset-2 > maxBranchOffset_g)) )
		{
			largeOperand = true;
		}
	}

	if ( !parsedInstruction.address.known )
	{
		// * if address is unknown, keep previous decision
		largeOperand = largeOperand || largeOperand_m[lineNumber];
	}
	else if ( instructionClass != InstructionClass::Branch )
	{
		if ( parsedInstruction.address.value.number > maxZPAddr_g )
		{
			largeOperand = true;
			if ( !largeOperand_m[lineNumber] )
			{
				// * if it is known and > 8 bit, it is 32 bit.  Mark this instruction large
				largeOperand_m[lineNumber] = true;
				sizeDecisionChanged_m = true;
#if ENABLE_ASSEMBLER_PASS_CONTROL_DEBUG
				printf( "Size decision changed: file %d line %d\n", (int)token->fileIndex, (int)lineNumber );
				source_m.PrintLine( stdout, token );
				printf( "\n" );
#endif
			}
		}
		else
		{
			// * if it is known and < 8 bit, and this instruction is marked large, it is 32 bit
			// * if it is known and < 8 bit, and this instruction is not marked large, it is 8 bit
			largeOperand = largeOperand || largeOperand_m[lineNumber];
		}
	}

	bool isShift = instructionClass == InstructionClass::Shift;
	if ( isShift )
	{
		if ( parsedInstruction.constant.known && (parsedInstruction.constant.value.number > maxConstant_g) )
		{
			largeConstant = true;
			if ( !largeConstant_m[lineNumber] )
			{
				// * if it is known and > 8 bit, it is 32 bit.  Mark this instruction large
				largeConstant_m[lineNumber] = true;
				sizeDecisionChanged_m = true;
#if ENABLE_ASSEMBLER_PASS_CONTROL_DEBUG
				printf( "Constant size decision changed: file %d line %d\n", (int)token->fileIndex, (int)lineNumber );
				source_m.PrintLine( stdout, token );
				printf( "\n" );
#endif
			}
		}
		else
		{
			largeConstant = largeConstant || largeConstant_m[lineNumber];
		}
	}

#if ENABLE_ASSEMBLER_INSTRUCTION_ENCODE_DEBUG
	printf( "%s addrMode %s large %d dest %s source %s number %08x (%s)\n",
		Token::InstructionName_g[int(parsedInstruction.instruction)], sourceAddrModeName_g[int(parsedInstruction.addrMode)], largeOperand,
		Token::registerName_g[int(parsedInstruction.destRegister)], Token::registerName_g[int(parsedInstruction.sourceRegister)],
		parsedInstruction.address.value.number, parsedInstruction.address.known?"known":"unknown" );
#endif

	// Map general instructions to register-specific
	TranslateInstruction( parsedInstruction, source, token );

	Value operand;
	AddrMode addrMode;
	uint16_t opcode = EncodeInstruction( parsedInstruction, largeOperand, largeConstant, addrMode, operand );
	output_m.Emit( opcode, listing, source, token );
	EmitOperand( addrMode, operand, largeOperand, parsedInstruction, isShift, listing, source, token );
}

void Assembler::AssemblePass( FILE* listing )
{
	output_m.NewBlock( 0 );
	LabelResetPass();
	std::vector<Token>::iterator token = source_m.tokens.begin();
	int lineNumber = 1;
	int globalLineNumber = 1;
	size_t prevFileIndex = (size_t)-1;
	while ( token->type != Token::Type::sourceEnd )
	{
		lineStart_m = token;
		if ( token->type == Token::Type::lineStart )
		{
			if ( token->fileIndex != prevFileIndex )
			{
				if ( !assemblyEnabled_m )
				{
					// skip included files excluded by .if
					while ( (token->type != Token::Type::sourceEnd) && (token->fileIndex != prevFileIndex) )
					{
						token++;
					}
				}
				else
				{
					if ( listing != nullptr )
					{
						fprintf( listing, "Input file %s:\n", source_m.GetFilename(token->fileIndex).c_str() );
					}
					lineNumber = 1;
				}
				prevFileIndex = token->fileIndex;
			}
			token++;
		}
		output_m.BeginLine( listing, token->line );
		if ( (token->type == Token::Type::directive) && (
			(token->value.directive == Token::Directive::ifDir) ||
			(token->value.directive == Token::Directive::elseDir) ||
			(token->value.directive == Token::Directive::endifDir) ) )
		{
			HandleIfElseEndif( source_m, token, listing );
		}
		if ( !assemblyEnabled_m )
		{
			// skip to next line
			while ( (token->type != Token::Type::sourceEnd) && (token->type != Token::Type::lineEnd) )
			{
				token++;
			}
		}
		else
		{
			if ( token->type == Token::Type::label )
			{
				HandleLabel( source_m, token, listing );
			}
			switch ( token->type )
			{
				case Token::Type::star:
					HandleStar( source_m, token );
					break;
				case Token::Type::directive:
					HandleDirective( source_m, token, listing );
					break;
				case Token::Type::instruction:
					HandleInstruction( source_m, token, globalLineNumber, listing );
					break;
				case Token::Type::lineEnd:
					break;
				default:
					Error( &source_m, &token, "syntax error" );
			}
		}
		output_m.EndLine( listing, source_m, token );
		if ( token->type != Token::Type::lineEnd )
		{
			Error( &source_m, &token, "expected end of line" );
		}
		token++;
		lineNumber++;
		globalLineNumber++;
	}
	if ( assemblyEnabledStack_m.size() > 0 )
	{
		Error( &source_m, &token, ".if without .else" );
	}
}

void Assembler::Assemble()
{
	// Make sure source ends with sourceEnd
	source_m.tokens.push_back( Token(0, 0, Token::Type::sourceEnd) );
	sizeDecisionChanged_m = true;
	haveUnknownValues_m = true;
	labelsChanged_m = true;
	pass_m = 1;
	while ( sizeDecisionChanged_m || haveUnknownValues_m || labelsChanged_m )
	{
		output_m.Clear();
		sizeDecisionChanged_m = false;
		haveUnknownValues_m = false;
		labelsChanged_m = false;
		assemblyEnabled_m = true;
		assemblyEnabledStack_m.clear();
		AssemblePass();
#if ENABLE_ASSEMBLER_PASS_CONTROL_DEBUG
		printf( "sizeDecisionChanged: %d  haveUnknownValues: %d  labelsChanged: %d\n", sizeDecisionChanged_m, haveUnknownValues_m, labelsChanged_m );
#endif
		pass_m++;
	}
}
