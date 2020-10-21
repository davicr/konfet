#pragma once

#include <cstdint>
#include <string>

namespace Konfet {

struct LuaLocal {
    std::string name;
    uint32_t startPc;
    uint32_t endPc;
};

} // namespace Konfet