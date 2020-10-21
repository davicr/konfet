#include "LuaInstruction.h"

namespace Konfet {

const char* OpcodeNames[static_cast<int>(InstructionOpcode::OPCODES_FINISH)] = {
    "move",
    "loadk",
    "loadbool",
    "loadnil",
    "getupval",
    "getglobal",
    "gettable",
    "setglobal",
    "setupval",
    "settable",
    "newtable",
    "self",
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "pow",
    "unm",
    "not",
    "len",
    "concat",
    "jmp",
    "eq",
    "lt",
    "le",
    "test",
    "testset",
    "call",
    "tailcall",
    "return",
    "forloop",
    "forprep",
    "tforloop",
    "setlist",
    "close",
    "closure",
    "vararg",
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

InstructionOpcode LuaInstruction::getOpcode()
{
    // Opcodes are the right-most 6 bits
    return static_cast<InstructionOpcode>(m_encodedInstruction & 0b111111);
}

uint32_t LuaInstruction::getArgA()
{
    // Argument A is between bits 7 and 15
    return (m_encodedInstruction & 0b11111111000000) >> 6;
}

uint32_t LuaInstruction::getArgB()
{
    // Argument B is between bits 24 and 31
    if (m_type != InstructionType::iABC)
        throw std::exception("can't get argument B for non-iABC instruction");

    return m_encodedInstruction >> 23;
}

uint32_t LuaInstruction::getArgC()
{
    // Argument C is between bits 16 and 23
    if (m_type != InstructionType::iABC)
        throw std::exception("can't get argument C for non-iABC instruction");

    return (m_encodedInstruction & 0b11111111100000000000000) >> 14;
}

uint32_t LuaInstruction::getArgBx()
{
    // Argument Bx is between bits 31 and 14
    if (m_type == InstructionType::iABC)
        throw std::exception("can't get argument Bx for non-iABx/iAsBx instruction");

    return m_encodedInstruction >> 14;
}

int32_t LuaInstruction::getArgSignedBx()
{
    // Argument sBx is between bits 31 and 14
    if (m_type != InstructionType::iAsBx)
        throw std::exception("can't get argument sBx for non-iAsBx instruction");

    return getArgBx() - 131071;
}

LuaInstruction::LuaInstruction(uint32_t op)
{
    m_encodedInstruction = op;
    m_opcode = getOpcode();
    m_type = OpcodeTypes[static_cast<int>(m_opcode)];
}

std::ostream& operator<<(std::ostream& os, LuaInstruction instruction)
{
    os << OpcodeNames[static_cast<int>(instruction.m_opcode)] << ' ' << instruction.getArgA();
    if (instruction.m_type == InstructionType::iABC)
        os << ' ' << instruction.getArgB() << ' ' << instruction.getArgC();
    if (instruction.m_type == InstructionType::iABx)
        os << ' ' << instruction.getArgBx();
    if (instruction.m_type == InstructionType::iAsBx)
        os << ' ' << instruction.getArgSignedBx();
    return os;
}

} // namespace LuaInstruction