//
// Created by sebastian on 15.05.16.
//

#ifndef CHIP8EMULATOR_KEYBOARD_H
#define CHIP8EMULATOR_KEYBOARD_H

#include "Chip8Types.h"
#include <array>

class Keyboard {
    std::array<Byte, 16> _keyboard;
public:

    enum {
        NOTPRESED = 0,
        PRESED = 1
    };

    void update(SDL_Event*);

    friend class Chip8Emulator;
};


#endif //CHIP8EMULATOR_KEYBOARD_H
