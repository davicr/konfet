#include "LuaInstruction.h"

namespace Konfet {

const char* OpcodeNames[static_cast<int>(InstructionOpcode::OPCODES_FINISH)] = {
    "MOVE",
    "LOADK",
    "LOADBOOL",
    "LOADNIL",
    "GETUPVAL",
    "GETGLOBAL",
    "GETTABLE",
    "SETGLOBAL",
    "SETUPVAL",
    "SETTABLE",
    "NEWTABLE",
    "SELF",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "POW",
    "UNM",
    "NOT",
    "LEN",
    "CONCAT",
    "JMP",
    "EQ",
    "LT",
    "LE",
    "TEST",
    "TESTSET",
    "CALL",
    "TAILCALL",
    "RETURN",
    "FORLOOP",
    "FORPREP",
    "TFORLOOP",
    "SETLIST",
    "CLOSURE",
    "VARARG"
};

const InstructionType OpcodeTypes[static_cast<int>(InstructionOpcode::OPCODES_FINISH)] = {
    InstructionType::iABC, // OP_MOVE
    InstructionType::iABx, // OP_LOADK
    InstructionType::iABC, // OP_LOADBOOL
    InstructionType::iABC, // OP_LOADNIL
    InstructionType::iABC, // OP_GETUPVAL
    InstructionType::iABx, // OP_GETGLOBAL
    InstructionType::iABC, // OP_GETTABLE
    InstructionType::iABx, // OP_SETGLOBAL
    InstructionType::iABC, // OP_SETUPVAL
    InstructionType::iABC, // OP_SETTABLE
    InstructionType::iABC, // OP_NEWTABLE
    InstructionType::iABC, // OP_SELF
    InstructionType::iABC, // OP_ADD
    InstructionType::iABC, // OP_SUB
    InstructionType::iABC, // OP_MUL
    InstructionType::iABC, // OP_DIV
    InstructionType::iABC, // OP_MOD
    InstructionType::iABC, // OP_POW
    InstructionType::iABC, // OP_UNM
    InstructionType::iABC, // OP_NOT
    InstructionType::iABC, // OP_LEN
    InstructionType::iABC, // OP_CONCAT
    InstructionType::iAsBx, // OP_JMP
    InstructionType::iABC, // OP_EQ
    InstructionType::iABC, // OP_LT
    InstructionType::iABC, // OP_LE
    InstructionType::iABC, // OP_TEST
    InstructionType::iABC, // OP_TESTSET
    InstructionType::iABC, // OP_CALL
    InstructionType::iABC, // OP_TAILCALL
    InstructionType::iABC, // OP_RETURN
    InstructionType::iAsBx, // OP_FORLOOP
    InstructionType::iAsBx, // OP_FORPREP
    InstructionType::iABC, // OP_TFORLOOP
    InstructionType::iABC, // OP_SETLIST
    InstructionType::iABC, // OP_CLOSE
    InstructionType::iABx, // OP_CLOSURE
    InstructionType::iABC, // OP_VARARG
};

LuaInstruction::LuaInstruction(uint32_t op)
{
    m_opcode = InstructionOpcode::OP_MOVE;
    m_type = OpcodeTypes[static_cast<int>(m_opcode)];
}

std::ostream& operator<<(std::ostream& os, LuaInstruction instruction)
{
    os << OpcodeNames[static_cast<int>(instruction.m_opcode)];
    return os;
}

} // namespace LuaInstruction