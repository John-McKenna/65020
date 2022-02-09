#ifndef INSTRUCTIONINFO_H
#define INSTRUCTIONINFO_H

#include "Source.h"
#include "Assembler.h"

void InitInstructionInfo();

enum class ExtensionFormat {
	PRRXXXDD, PRR___DD, PRRRR_DD, PNNXXXDD, P_RRRRDD, PSRRRRDD,
	PNNRRRDD, PAAARRRR, PAAAXXXX, WNNNVVVV, NNNNNNNN, RRRSSSDD,
	P_______, branch, none
};

struct OpcodeInfo
{
	uint16_t opcode;
	Assembler::AddrMode addrMode;
	ExtensionFormat extensionFormat;
};

struct OpcodeInfoByIndexType
{
	OpcodeInfo type[4];
};

struct OpcodeInfoBySize
{
	OpcodeInfoByIndexType size[2];
};

typedef std::unordered_map<Assembler::SourceAddrMode, OpcodeInfoBySize> InstructionInfo;

extern std::vector<InstructionInfo> instructionInfo_g;
#endif
