#include "Chip8Emulator.h"
#include <fstream>
#include <iostream>

int main(int argc, char**args) {

    std::fstream game("/home/sebastian/c8games/INVADERS", std::ios::in);
    Chip8Emulator chip8Emulator(&game);

    while(true) {
        chip8Emulator.emulationStep();
        std::cin.get();
    }
}