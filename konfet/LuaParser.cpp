#include "LuaParser.h"
#include "LuaChunk.h"
#include "LuaHeader.h"
#include "LuaInstruction.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace Konfet {

LuaParser::LuaParser(std::vector<uint8_t>& data)
    : m_data(data)
{
    m_dataIterator = m_data.begin();
}

template <typename T>
T LuaParser::readPod()
{
    T ret;
    std::copy(m_dataIterator, m_dataIterator + sizeof(T), reinterpret_cast<uint8_t*>(&ret));
    m_dataIterator += sizeof(T);
    return ret;
}

void LuaParser::readBytes(uint8_t* out, size_t len)
{
    std::copy(m_dataIterator, m_dataIterator + len, out);
    m_dataIterator += len;
}

std::string LuaParser::readLuaString()
{
    // Assumes 32-bit size_t
    std::string ret = "";
    uint32_t len = readPod<uint32_t>();
    for (size_t i = 0; i < len; i++) {
        ret.push_back(*m_dataIterator);
        m_dataIterator++;
    }
    return ret;
}

template <typename T>
std::vector<T> LuaParser::readPodList()
{
    std::vector<T> ret;
    int size = readPod<int>();
    for (int i = 0; i < size; i++) {
        T data = readPod<T>();
        ret.push_back(data);
    }
    return ret;
}

template <typename T, typename I>
std::vector<T> LuaParser::readList(std::function<T(I)> func)
{
    std::vector<T> ret;
    int size = readPod<int>();
    for (int i = 0; i < size; i++) {
        I data = readPod<I>();
        ret.push_back(func(data));
    }
    return ret;
}

LuaHeader LuaParser::parseHeader()
{
    LuaHeader header;

    readBytes(header.signature, 4);
    header.version = readPod<uint8_t>();
    header.format = readPod<uint8_t>();
    header.endiannessFlag = readPod<uint8_t>();
    header.intSize = readPod<uint8_t>();
    header.sizeTypeSize = readPod<uint8_t>();
    header.instructionSize = readPod<uint8_t>();
    header.luaNumberSize = readPod<uint8_t>();
    header.integralFlag = readPod<uint8_t>();

    return header;
}

LuaChunk LuaParser::parseChunk()
{
    LuaChunk chunk = {};

    chunk.sourceName = readLuaString();
    chunk.lineDefined = readPod<int>();
    chunk.lastLineDefined = readPod<int>();
    chunk.numUpvalues = readPod<uint8_t>();
    chunk.numParameters = readPod<uint8_t>();
    chunk.varargFlags = readPod<uint8_t>();
    chunk.maxStackSize = readPod<uint8_t>();

    // Parse instructions!
    auto parseInstruction = [](uint32_t ins) { return LuaInstruction(ins); };
    chunk.instructions = readList<LuaInstruction, uint32_t>(parseInstruction);
    for (auto ins : chunk.instructions)
        std::cout << ins << '\n';

    return chunk;
}

LuaChunk LuaParser::Parse()
{
    // Read bytecode header into LuaHeader structure
    LuaHeader header = parseHeader();

    // Verify if Lua header matches our supported header
    LuaHeader supportedHeader = {
        { 0x1B, 0x4C, 0x75, 0x61 },
        0x51,
        0,
        1,
        4,
        4,
        4,
        8,
        0
    };
    if (memcmp(&header, &supportedHeader, sizeof(LuaHeader)))
        throw std::exception("unsupported Lua header");

    // Read top-level Lua chunk
    LuaChunk topChunk = parseChunk();

    return topChunk;
}

} // namespace LuaParser