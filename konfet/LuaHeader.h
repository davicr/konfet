#pragma once

#include <cstdint>

namespace Konfet {

struct LuaHeader {
    uint8_t signature[4];
    uint8_t version;
    uint8_t format;
    uint8_t endiannessFlag;
    uint8_t intSize;
    uint8_t sizeTypeSize;
    uint8_t instructionSize;
    uint8_t luaNumberSize;
    uint8_t integralFlag;
};

}