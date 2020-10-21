#pragma once

#include "LuaConstant.h"
#include "LuaInstruction.h"
#include "LuaLocal.h"
#include <cstdint>
#include <string>
#include <vector>

namespace Konfet {

struct LuaChunk {
    std::string sourceName;
    int lineDefined;
    int lastLineDefined;
    uint8_t numUpvalues;
    uint8_t numParameters;
    uint8_t varargFlags;
    uint8_t maxStackSize;
    std::vector<LuaInstruction> instructions;
    std::vector<LuaConstant> constants;
    std::vector<LuaChunk> protos;
    std::vector<int> sourceLines;
    std::vector<LuaLocal> locals;
    std::vector<std::string> upvalues;
};

} // namespace Konfet