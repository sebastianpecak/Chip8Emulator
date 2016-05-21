//
// Created by sebastian on 15.05.16.
//

#ifndef CHIP8EMULATOR_DISPLAY_H
#define CHIP8EMULATOR_DISPLAY_H

#include "Chip8Types.h"
#include "Chip8Emulator.h"

class Display {
    static int PIXEL_SCALE;
    SDL_Window *_window;
    SDL_Surface *_windowSurface;
    Chip8Emulator *_chip8Emulator;
    int _localPixelScale;

public:

    explicit Display(CString = DefaultEmultorWindowCaption);

    // Display whole video memory
    void update();

    void connect(Chip8Emulator*);

    static void setPixelScale(int);
    static void init();
    static void finish();
};


#endif //CHIP8EMULATOR_DISPLAY_H
