//
// Created by sebastian on 05.05.16.
//

#include <iostream>
#include "Chip8Emulator.h"

Byte Chip8Emulator::chip8_fontset[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8Emulator::Chip8Emulator(std::istream *content) {
    // Initialize everything, regs, memory etc
    this->_pc = 0x200;
    this->_opcode = 0;
    this->_I = 0;
    this->_stackPointer = 0;
    this->_requestUpdate = false;

    // Clear stack
    for(int i=0; i<_stack.size(); i++) _stack[i] = 0;

    // Clear registers
    for(int i=0; i<_V.size(); i++) _V[i] = 0;

    // Clear memory
    for(int i=0; i<_ramMemory.size(); i++) _ramMemory[i] = 0;

    // Load font set
    memcpy(_ramMemory.data(), &chip8_fontset, 80);

    _delayTimer = 0;
    _soundTimer = 0;

    // Init opcode handler bindings
    initBindings();

    // If required load code from istream
    if(content) loadGame(content);
}

void Chip8Emulator::loadGame(std::istream *inStream) {
    if(inStream && inStream->good()) {
        // Load game from stream
        inStream->seekg(0);
        int i = 0;
        while(!inStream->eof()) this->_ramMemory[0x200 + i++] = (Byte)inStream->get();
        printf("\n%d loaded\n", i);
    }
    else Degug("Invalid stream pointer")
}

void Chip8Emulator::saveEmulatorState(std::ostream *outStream) {
    if(outStream && outStream->good()) {
        outStream->seekp(0);
        /*
         * Output file structure
         *      CHIP8 VERSION [4B]
         *      OPCODE [2B]
         *      I [2B]
         *      PC [2B]
         *      DELAY_TIMER [1B]
         *      SOUND_TIMER [1B]
         *      V [16B]
         *      STACK_POINTER [1B]
         *      STACK [32B]
         *      RAM_MEMORY [4096B]
         *      VIDEO_MEMORY [2048B]
         *
         *      TOTAL_LENGTH: 6205B
         *
         */

        outStream->write((const char*)&Version, sizeof(int));
        outStream->write((const char*)&_opcode, sizeof(Word));
        outStream->write((const char*)&_I, sizeof(Word));
        outStream->write((const char*)&_pc, sizeof(Word));
        outStream->write((const char*)&_delayTimer, sizeof(Byte));
        outStream->write((const char*)&_soundTimer, sizeof(Byte));
        outStream->write((const char*)_V.data(), sizeof(Byte)*16);
        outStream->write((const char*)&_stackPointer, sizeof(Byte));
        outStream->write((const char*)_stack.data(), sizeof(Byte)*32);
        outStream->write((const char*)_ramMemory.data(), sizeof(Byte)*4096);
        // Save video memory
    }
    else Degug("Invalid stream pointer");
}

void Chip8Emulator::connectKeyboard(Keyboard *keyboardDevice) {
    if(keyboardDevice) _keybaordDevice = keyboardDevice;
}

void Chip8Emulator::emulationStep() {
    // Fetch one instruction from memory
    // Emulator runs on BigEndian bitset
    _opcode = (_ramMemory[_pc] << 8) | _ramMemory[_pc + 1];

    // Call opcode handler delegate
    // And check if there were errors
    try {
        (this->*_opcodeBindings.get(_opcode & (_bindingsMask[(_opcode & 0xF000) >> 12])))();
    } catch(ElementNotFound &e) {
        std::cout <<"Unknown opcode!\n";
    } catch(...) {
        std::cout <<"Unknown error!\n";
    }

    // Count down
    if(_delayTimer > 0) _delayTimer--;
    if(_soundTimer > 0) {
        PrintLn("BUZZER BEEP")
        --_soundTimer;
    }

    _pc+=2;
}

