#pragma once

#include "LuaInstruction.h"
#include <cstdint>
#include <vector>

namespace Konfet {

class LuaParser {
public:
    LuaParser(std::vector<uint8_t>& data);
    std::vector<LuaInstruction> Parse();

private:
    std::vector<uint8_t> m_data;
};

} // namespace LuaParser