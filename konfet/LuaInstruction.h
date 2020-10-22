#pragma once

#include <cstdint>
#include <iostream>

namespace Konfet {

enum class InstructionType {
    iABC,
    iABx,
    iAsBx
};

enum class InstructionOpcode {
    OP_MOVE,
    OP_LOADK,
    OP_LOADBOOL,
    OP_LOADNIL,
    OP_GETUPVAL,
    OP_GETGLOBAL,
    OP_GETTABLE,
    OP_SETGLOBAL,
    OP_SETUPVAL,
    OP_SETTABLE,
    OP_NEWTABLE,
    OP_SELF,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_POW,
    OP_UNM,
    OP_NOT,
    OP_LEN,
    OP_CONCAT,
    OP_JMP,
    OP_EQ,
    OP_LT,
    OP_LE,
    OP_TEST,
    OP_TESTSET,
    OP_CALL,
    OP_TAILCALL,
    OP_RETURN,
    OP_FORLOOP,
    OP_FORPREP,
    OP_TFORLOOP,
    OP_SETLIST,
    OP_CLOSE,
    OP_CLOSURE,
    OP_VARARG,
    OPCODES_FINISH
};

class LuaInstruction {
public:
    LuaInstruction(uint32_t op);
    InstructionOpcode getOpcode();
    uint32_t getArgA();
    uint32_t getArgB();
    uint32_t getArgC();
    uint32_t getArgBx();
    int32_t getArgSignedBx();
    friend std::ostream& operator<<(std::ostream& os, LuaInstruction instruction);

private:
    uint32_t m_encodedInstruction;
    InstructionOpcode m_opcode;
    InstructionType m_type;
};

} // namespace Konfet