cmake_minimum_required(VERSION 3.5)
project(Chip8Emulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Chip8Emulator.h Chip8Emulator.cpp MyGame.h Binding.cpp Binding.h OpcodeHandlers.cpp Exception.cpp Exception.h Display.cpp Display.h displayTest.cpp Chip8AsmCompiler.cpp Chip8AsmCompiler.h Chip8Types.h Keyboard.cpp Keyboard.h chip8inline.cpp SimpleEmulator/simpleEmulator.cpp)
add_executable(Chip8Emulator ${SOURCE_FILES})