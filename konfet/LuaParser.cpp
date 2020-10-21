#include "LuaParser.h"
#include "LuaHeader.h"
#include <algorithm>
#include <iostream>

namespace Konfet {

LuaParser::LuaParser(std::vector<uint8_t>& data)
    : m_data(data)
{
}

template <class T>
T readPod(std::vector<uint8_t>::iterator& it)
{
    T ret;
    std::copy(it, it + sizeof(T), reinterpret_cast<uint8_t*>(&ret));
    it += sizeof(T);
    return ret;
}

void readBytes(std::vector<uint8_t>::iterator& it, uint8_t* out, size_t len)
{
    std::copy(it, it + len, out);
    it += len;
}

std::vector<LuaInstruction> LuaParser::Parse()
{
    // TODO: Create LuaChunk

    std::vector<uint8_t>::iterator sigIt = m_data.begin();
    std::vector<uint8_t>::iterator it = m_data.begin() + 4;

    // Read bytecode header into LuaHeader structure
    LuaHeader header = {
        { '\0', '\0', '\0', '\0' }, // signature
        readPod<uint8_t>(it), // version
        readPod<uint8_t>(it), // format
        readPod<uint8_t>(it), // endiannessFlag
        readPod<uint8_t>(it), // intSize
        readPod<uint8_t>(it), // sizeTypeSize
        readPod<uint8_t>(it), // instructionSize
        readPod<uint8_t>(it), // luaNumberSize
        readPod<uint8_t>(it), // integralFlag
    };
    readBytes(sigIt, header.signature, 4);

#ifdef _DEBUG
    std::cout << std::hex;
    (std::cout << "SIG: ").write(reinterpret_cast<const char*>(&header.signature[0]), 4) << '\n';
    std::cout << "VER: " << static_cast<int>(header.version) << '\n';
    std::cout << "FMT: " << static_cast<int>(header.format) << '\n';
    std::cout << "END: " << static_cast<int>(header.endiannessFlag) << '\n';
    std::cout << "INT: " << static_cast<int>(header.intSize) << '\n';
    std::cout << "SZT: " << static_cast<int>(header.sizeTypeSize) << '\n';
    std::cout << "INS: " << static_cast<int>(header.instructionSize) << '\n';
    std::cout << "NUM: " << static_cast<int>(header.luaNumberSize) << '\n';
    std::cout << "INT: " << static_cast<int>(header.integralFlag) << '\n';
    std::cout << std::dec;
#endif

    return std::vector<LuaInstruction>();
}

} // namespace LuaParser