//
// Created by sebastian on 15.05.16.
//

#include "Display.h"

int Display::PIXEL_SCALE = DefaultPixelScale;

void Display::setPixelScale(int pixelScale) {
    if(pixelScale > 0 && pixelScale <= 30) Display::PIXEL_SCALE = pixelScale;
}

void Display::init() {
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER);
}

void Display::finish() {
    SDL_Quit();
}

Display::Display(CString windowCaption) {
    _window = SDL_CreateWindow(windowCaption, 0, 0, DefaultDisplayX * PIXEL_SCALE, DefaultDisplayY * PIXEL_SCALE, SDL_WINDOW_SHOWN);
    SDL_SetPaletteColors(nullptr, nullptr, 0, 2);
    _windowSurface = SDL_GetWindowSurface(_window);
}

void Display::connect(Chip8Emulator *chip8Emulator) {
    if(chip8Emulator) _chip8Emulator = chip8Emulator;
}

void Display::update() {
    // If there is emulator connected
    if(_chip8Emulator && _chip8Emulator->_requestUpdate) {
        for(int x=0; x<DefaultDisplayX; x++) {
            for(int y=0; y<DefaultDisplayY; y++) {
                SDL_Rect rect = {x*PIXEL_SCALE, y*PIXEL_SCALE, PIXEL_SCALE, PIXEL_SCALE};
                SDL_FillRect(_windowSurface, &rect, (0xFF)*_chip8Emulator->_videoMemory[x][y]);
            }
        }
        SDL_UpdateWindowSurface(_window);
        _chip8Emulator->_requestUpdate = false;
    }
}