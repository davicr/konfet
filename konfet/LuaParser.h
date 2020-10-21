#pragma once

#include "LuaChunk.h"
#include "LuaHeader.h"
#include "LuaInstruction.h"
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace Konfet {

class LuaParser {
public:
    LuaParser(std::vector<uint8_t>& data);
    LuaChunk Parse();

private:
    template <typename T>
    T readPod();

    template <typename T>
    std::vector<T> readPodList();

    template <typename T, typename I>
    std::vector<T> readList(std::function<T(I)> func);

    void readBytes(uint8_t* out, size_t len);
    std::string readLuaString();

    LuaHeader parseHeader();
    LuaChunk parseChunk();

    std::vector<uint8_t> m_data;
    std::vector<uint8_t>::iterator m_dataIterator;
};

} // namespace LuaParser