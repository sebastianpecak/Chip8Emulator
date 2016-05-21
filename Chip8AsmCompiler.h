//
// Created by sebastian on 15.05.16.
//

#ifndef CHIP8EMULATOR_CHIP8ASMCOMPILER_H
#define CHIP8EMULATOR_CHIP8ASMCOMPILER_H

#include "Chip8Types.h"
#include <istream>
#include <string>

// Binary structure
struct BinaryFormat {
    Byte *_data;
    unsigned int _size;
};

class Chip8AsmCompiler {
public:
    static BinaryFormat compile(std::istream*);
    static BinaryFormat compile(const std::string&);
    static std::string decompile(std::istream*);
    static std::string decompile(BinaryFormat&);
};


#endif //CHIP8EMULATOR_CHIP8ASMCOMPILER_H
