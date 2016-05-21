//
// Created by sebastian on 15.05.16.
//

#include "Display.h"
#include "Keyboard.h"
#include <fstream>

int main() {

    // Load game files
    std::fstream game1("/home/sebastian/c8games/PONG", std::ios::in), game2("/home/sebastian/c8games/INVADERS", std::ios::in);

    if(game1.is_open() && game2.is_open()) {
        Chip8Emulator chip8Emulator(&game1);
        Chip8Emulator chip8Emulator1(&game2);
        // Close files
        game1.close();
        game2.close();

        Display::init();

        Keyboard mainKeyboard;

        Display display("Display Test");
        Display display1("Display1 Test");

        display.connect(&chip8Emulator);
        display1.connect(&chip8Emulator1);

        chip8Emulator.connectKeyboard(&mainKeyboard);
        chip8Emulator1.connectKeyboard(&mainKeyboard);

        // SDL Event
        SDL_Event event;

        bool quitFlag = false;
        while(!quitFlag) {
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_WINDOWEVENT_CLOSE:
                        !quitFlag;
                        break;
                    case SDL_KEYUP:
                        mainKeyboard.update(&event);
                        break;
                    case SDL_KEYDOWN:
                        mainKeyboard.update(&event);
                        break;
                }
            }

            chip8Emulator.emulationStep();
            chip8Emulator1.emulationStep();
            display.update();
            display1.update();
        }

        Display::finish();
    }
}