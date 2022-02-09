#include "InstructionInfo.h"

std::vector<InstructionInfo> instructionInfo_g;

static void InitInstructionInfoA()
{
	instructionInfo_g[(int)(int)Token::Instruction::ABS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xa0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xa0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xa0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xa0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xa0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xa0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ABX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xa0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ABY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xa088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ACX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x006f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x006b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x006b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x006f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x006b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x006b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ACY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x007f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x007b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x007b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x007f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x007b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x007b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ADC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x007c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0075, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0075, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0065, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0065, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x007d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0079, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x006d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0061, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0061, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0071, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0071, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ADD] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x807c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8069, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8075, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8075, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8065, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8065, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x807d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8079, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x806d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8061, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8061, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x8071, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8071, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ADX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8063, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8067, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x806f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x806f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x806b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x806b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x806f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x806f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x806b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x806b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ADY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8073, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8077, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x807f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x807b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x807b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x807f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x807b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x807b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::AND] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x003c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0035, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0035, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0025, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0025, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0029, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x002d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0021, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0021, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0031, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0031, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ANX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x002f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x002f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x002b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x002b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x002f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x002f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x002b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x002b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ANY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x003b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x003b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x003b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x003b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ASL] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x000a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0016, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x0016, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x0006, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x0006, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x001e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x000e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x000e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ASR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x804a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8056, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x8056, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x8046, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x8046, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x805e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x805e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x804e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x804e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoB()
{
	instructionInfo_g[(int)Token::Instruction::BCC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BCS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BCX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8023, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8027, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x802f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x802f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x802b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x802b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x802f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x802f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x802b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x802b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BCY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8033, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x8037, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x803f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x803b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x803b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x803f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x803b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x803b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BEQ] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BGE] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BGT] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BHI] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80b0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BHS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BIC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x803c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8029, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8035, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8035, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8025, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8025, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x803d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8029, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x802d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8021, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8021, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x8031, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8031, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BIT] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0034, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003a, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003a, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0024, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0024, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003a, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x003a, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x002c, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x002c, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BLE] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BLS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8090, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BLT] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x8030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BMI] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0030, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BNE] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x00d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BNV] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80d0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BPL] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0010, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BRA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x80f0, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BRK] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::acc, ExtensionFormat::WNNNVVVV }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BVC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0050, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::BVS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// A
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// X
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// Y
					OpcodeInfo({ 0x0070, Assembler::AddrMode::rel, ExtensionFormat::branch }),			// P
				})
			})
		}
	});
}

static void InitInstructionInfoC()
{
	instructionInfo_g[(int)Token::Instruction::CBT] = InstructionInfo(),
	instructionInfo_g[(int)Token::Instruction::CCX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80e4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80e4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80ec, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80ec, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::CCY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80c4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80c4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80cc, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80cc, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::CLC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::CLD] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::CLI] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::CLV] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::CMP] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00d5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00c5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00c5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00dd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00dd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00d9, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00cd, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00c1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00d1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00d1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::CPC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80dc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80c9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80d5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80c5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80c5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80dd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80dd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80d9, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80cd, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80c1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80c1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80d1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80d1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::CPX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00c3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00e0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00e4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00e4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00cf, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00ec, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ec, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::CPY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00d3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00c0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00c4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00c4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00df, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00cc, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00cc, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoD()
{
	instructionInfo_g[(int)Token::Instruction::DEC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x00d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x00c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x00c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x00de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x00ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x00ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::DEX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::DEY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x0088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::DIV] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x009b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x009b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x009b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x009b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::DVS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x8093, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x8097, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x8000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x809b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x809b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x8000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x809b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x809b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoE()
{
	instructionInfo_g[(int)Token::Instruction::EOR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x005c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0049, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0055, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0055, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0045, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0045, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x005d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0059, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x004d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0041, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0041, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0051, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0051, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::EOX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0043, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0047, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x004f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x004b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x004b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x004f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x004b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x004b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::EOY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0053, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0057, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x005f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x005b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x005b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x005f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x005b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x005b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ESL] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x800a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8002, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc002, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8016, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x8016, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x8006, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x8006, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x801e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x801e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x800e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x800e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoI()
{
	instructionInfo_g[(int)Token::Instruction::INC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x00f6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x00e6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x00e6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00fe, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x00fe, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x00ee, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x00ee, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::INX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00e8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::INY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x00c8, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoJ()
{
	instructionInfo_g[(int)Token::Instruction::JMP] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x004c, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabs,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x006c, Assembler::AddrMode::indabs, ExtensionFormat::P_______ }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::JSR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// A
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// X
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// Y
					OpcodeInfo({ 0x0020, Assembler::AddrMode::abs, ExtensionFormat::P_______ }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoL()
{
	instructionInfo_g[(int)Token::Instruction::LDA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a9, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00b5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00a5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00a5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00bd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00bd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00b9, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ad, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00a1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00b1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00b1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::LDX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a2, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00af, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00af, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00b6, Assembler::AddrMode::zpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00a6, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00af, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00af, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00be, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ae, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::LDY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00a0, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b4, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00b4, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00a4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00a4, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00bc, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00bc, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00ac, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ac, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::LSR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x004a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0042, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4042, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0056, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x0056, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x0046, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x0046, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x005e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x005e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x004e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x004e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoM()
{
	instructionInfo_g[(int)Token::Instruction::MDS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::MLS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::MOD] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00a3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00a7, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ab, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::MOV] = InstructionInfo(),
	instructionInfo_g[(int)Token::Instruction::MUL] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0083, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0087, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoN()
{
	instructionInfo_g[(int)Token::Instruction::NEG] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x80d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x80c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x80c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x80de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x80ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x80ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::NGX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x80ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::NGY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0x8088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::NOP] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// A
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// X
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// Y
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// A
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// X
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// Y
					OpcodeInfo({ 0x00ea, Assembler::AddrMode::imp, ExtensionFormat::NNNNNNNN }),		// P
				})
			})
		},
	});
}

static void InitInstructionInfoO()
{
	instructionInfo_g[(int)Token::Instruction::ORA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x001c, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x0009, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0015, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0015, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0005, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0005, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x001d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0019, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x000d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0001, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0001, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0011, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0011, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ORX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0003, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0007, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x000f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x000f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x000b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x000b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x000f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x000f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x000b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x000b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ORY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0013, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x0017, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x001f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x001b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x001b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x001f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x001f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x001b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x001b, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoP()
{
	instructionInfo_g[(int)Token::Instruction::PHA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0048, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PHP] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0008, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PHX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0044, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PHY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0054, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PLA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0068, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PLP] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0028, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PLX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0064, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::PLY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0074, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
}

static void InitInstructionInfoR()
{
	instructionInfo_g[(int)Token::Instruction::RLB] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x802a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8036, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x8036, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x8026, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x8026, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x803e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x803e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x802e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x802e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ROL] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x002a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0022, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4022, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0036, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x0036, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x0026, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x0026, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x003e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x003e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x002e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x002e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::ROR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x006a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x0062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0x4062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0076, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x0076, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x0066, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x0066, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x007e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x007e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x006e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x006e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::RRB] = InstructionInfo({
		{
			Assembler::SourceAddrMode::constant,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// A
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// X
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// Y
					OpcodeInfo({ 0x806a, Assembler::AddrMode::acc, ExtensionFormat::P_RRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// A
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// X
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// Y
					OpcodeInfo({ 0x8062, Assembler::AddrMode::imm, ExtensionFormat::PSRRRRDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// A
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// X
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// Y
					OpcodeInfo({ 0xc062, Assembler::AddrMode::accExt, ExtensionFormat::PSRRRRDD}),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8076, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x8076, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x8066, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x8066, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x807e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0x807e, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0x806e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0x806e, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::RSQ] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::RTI] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0040, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::RTS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0060, Assembler::AddrMode::imp, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
	});
}

static void InitInstructionInfoS()
{
	instructionInfo_g[(int)Token::Instruction::SBC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x00e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00f5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00e5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00e5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00fd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00fd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00f9, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00ed, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00e1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00f1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00f1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SBT] = InstructionInfo(),
	instructionInfo_g[(int)Token::Instruction::SBX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SBY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x80f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SCX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00e3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00e7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00ef, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00eb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SCY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00f3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// A
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// X
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// Y
					OpcodeInfo({ 0x00f7, Assembler::AddrMode::imm, ExtensionFormat::PRR___DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00ff, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00fb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SEC] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::SED] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x00f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::SEI] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x0072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::SEV] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x0098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x00b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::SQR] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00b3, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x00bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x00bb, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::STA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0095, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0095, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0085, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0085, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x009d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x009d, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0099, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008d, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0081, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0081, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0091, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0091, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::STX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x008f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x008f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0096, Assembler::AddrMode::zpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0086, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x008f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x008f, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x009e, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008e, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::STY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0094, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x0094, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0084, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x0084, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x009c, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x009c, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x008c, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x008c, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::SUB] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80fc, Assembler::AddrMode::acc, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::imm,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// A
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// X
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// Y
					OpcodeInfo({ 0x80e9, Assembler::AddrMode::imm, ExtensionFormat::PRRRR_DD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80f5, Assembler::AddrMode::zpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80e5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80e5, Assembler::AddrMode::zp0, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80fd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80fd, Assembler::AddrMode::absX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x80f9, Assembler::AddrMode::absY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80ed, Assembler::AddrMode::abs0, ExtensionFormat::PRRXXXDD }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80e1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// A
					OpcodeInfo({ 0x80e1, Assembler::AddrMode::indzpX, ExtensionFormat::PRRXXXDD }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::indabsY,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x80f1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// Y
					OpcodeInfo({ 0x80f1, Assembler::AddrMode::indzpY, ExtensionFormat::PRRXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// A
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// X
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// Y
					OpcodeInfo({ 0x0000, Assembler::AddrMode::undefined, ExtensionFormat::none }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoT()
{
	instructionInfo_g[(int)Token::Instruction::TAX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00aa, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TAY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00a8, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TBT] = InstructionInfo(),
	instructionInfo_g[(int)Token::Instruction::TSX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x00ba, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TXA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x008a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TXS] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x009a, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TYA] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// A
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// X
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// Y
					OpcodeInfo({ 0x0098, Assembler::AddrMode::acc, ExtensionFormat::RRRSSSDD }),		// P
				})
			})
		}
	});
}

static void InitInstructionInfoX()
{
	instructionInfo_g[(int)Token::Instruction::XBT] = InstructionInfo(),
	instructionInfo_g[(int)Token::Instruction::NOT] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xe0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xe0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xe0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xe0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xe0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xe0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::NTX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xe0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::NTY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xe088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::EXT] = InstructionInfo({
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xc0d6, Assembler::AddrMode::zpX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xc0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xc0c6, Assembler::AddrMode::zp0, ExtensionFormat::PNNXXXDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// A
					OpcodeInfo({ 0xc0de, Assembler::AddrMode::absX, ExtensionFormat::PNNXXXDD }),		// X
					OpcodeInfo({ 0xc0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// Y
					OpcodeInfo({ 0xc0ce, Assembler::AddrMode::abs0, ExtensionFormat::PNNXXXDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::EXX] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xc0ca, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::EXY] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// A
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// X
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// Y
					OpcodeInfo({ 0xc088, Assembler::AddrMode::acc, ExtensionFormat::PNNRRRDD }),		// P
				})
			})
		}
	});
	instructionInfo_g[(int)Token::Instruction::TBT_C] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8018, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8012, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::TBT_D] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80d8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80d2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::TBT_I] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8058, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8052, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::TBT_V] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80b8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8092, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::XBT_C] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8038, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8032, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::XBT_D] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x80f8, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80f2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::XBT_I] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8078, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x8072, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
	instructionInfo_g[(int)Token::Instruction::XBT_V] = InstructionInfo({
		{
			Assembler::SourceAddrMode::reg,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// A
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// X
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// Y
					OpcodeInfo({ 0x8098, Assembler::AddrMode::imp, ExtensionFormat::PAAARRRR }),		// P
				})
			})
		},
		{
			Assembler::SourceAddrMode::absX,
			OpcodeInfoBySize({
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				}),
				OpcodeInfoByIndexType({
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// A
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// X
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// Y
					OpcodeInfo({ 0x80b2, Assembler::AddrMode::abs, ExtensionFormat::PAAAXXXX }),		// P
				})
			})
		},
	});
}

void InitInstructionInfo()
{
	instructionInfo_g.resize((int)Token::Instruction::undefined);
	// Putting all of the initialisation into one function (or making it a
	// global initialiser) crashes some versions of Visual Studio
	InitInstructionInfoA();
	InitInstructionInfoB();
	InitInstructionInfoC();
	InitInstructionInfoD();
	InitInstructionInfoE();
	InitInstructionInfoI();
	InitInstructionInfoJ();
	InitInstructionInfoL();
	InitInstructionInfoM();
	InitInstructionInfoN();
	InitInstructionInfoO();
	InitInstructionInfoP();
	InitInstructionInfoR();
	InitInstructionInfoS();
	InitInstructionInfoT();
	InitInstructionInfoX();
}

