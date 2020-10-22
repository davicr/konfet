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

void printChunk(const Konfet::LuaChunk& chunk)
{
    std::cout << "source name: " << chunk.sourceName << '\n';
    std::cout << "line defined: " << chunk.lineDefined << '\n';
    std::cout << "last line defined: " << chunk.lastLineDefined << '\n';
    std::cout << "number of upvalues: " << (int)chunk.numUpvalues << '\n';
    std::cout << "number of parameters: " << (int)chunk.numParameters << '\n';
    std::cout << "vararg flag: " << (int)chunk.varargFlags << '\n';
    std::cout << "maximum stack: " << (int)chunk.maxStackSize << '\n';

    for (auto ins : chunk.instructions)
        std::cout << "ins: " << ins << '\n';
    for (auto cons : chunk.constants)
        std::cout << "cons: " << cons << '\n';
    for (auto pos : chunk.sourceLines)
        std::cout << "pos: " << pos << '\n';
    for (auto local : chunk.locals)
        std::cout << "loc: " << local.name << " startPc: " << local.startPc << " endPc: " << local.endPc << '\n';
    for (auto upvalue : chunk.upvalues)
        std::cout << "upval: " << upvalue << '\n';
    std::cout << '\n';
    for (auto proto : chunk.protos)
        printChunk(proto);
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

    // Parse the given bytecode into the top-level chunk
    Konfet::LuaParser parser(bytecode);
    Konfet::LuaChunk chunk;
    try {
        chunk = parser.Parse();
    } catch (std::exception& e) {
        std::cerr << "Failed to parse the given bytecode: " << e.what() << '\n';
        return 1;
    }
    printChunk(chunk);

    // TODO: Generate graph for given top-level chunk

    return 0;
}