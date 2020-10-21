#include "LuaInstruction.h"
#include "LuaParser.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void readFileToBytes(const char* path, std::vector<uint8_t>& outVector)
{
    std::ifstream file(path, std::ifstream::in | std::ifstream::binary);
    if (!file.is_open())
        throw std::exception("failed to open the given file");
    std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(outVector));
}

int main(int argc, char* argv[])
{
    // Requires one argument: path to Lua 5.1 bytecode
    if (argc < 2) {
        std::cout << "Missing path to Lua 5.1 bytecode" << '\n';
        return 1;
    }

    // Attempt to read bytecode into a vector of bytes
    std::vector<uint8_t> bytecode;
    try {
        readFileToBytes(argv[1], bytecode);
    } catch (std::exception&) {
        std::cerr << "Failed to open the given bytecode" << '\n';
        return 1;
    }

    // Parse the given bytecode
    Konfet::LuaParser parser(bytecode);
    Konfet::LuaChunk chunk;
    try {
        chunk = parser.Parse();
    } catch (std::exception& e) {
        std::cerr << "Failed to parse the given bytecode: " << e.what() << '\n';
    }

    return 0;
}