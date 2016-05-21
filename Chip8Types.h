//
// Created by sebastian on 15.05.16.
//

#ifndef CHIP8EMULATOR_CHIP8TYPES_H
#define CHIP8EMULATOR_CHIP8TYPES_H

#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <array>
#include <string>
#include <istream>
#include <ostream>

#define DefaultDisplayX 64
#define DefaultDisplayY 32

#define BlackPixel 0
#define WhitePixel 1

#define DefaultPixelScale 20
#define DefaultEmultorWindowCaption "Chip8Emulator"

const int Version =  0x05152016;

#define Degug(text) printf("@@Debug: %s\n", text);
#define PrintLn(text) printf("\n%s", text);

// Class prototypes
template <typename, typename, int>
class Binding;
class Chip8AsmCompiler;
class Chip8Emulator;
class Display;
class Exception;
class Keyboard;

// Data types
typedef unsigned char Byte;
typedef unsigned char Pixel;
typedef unsigned short Word;
typedef void (Chip8Emulator::*OpcodeDelegate)(void);
typedef const char* CString;
typedef std::string String;


#endif //CHIP8EMULATOR_CHIP8TYPES_H
