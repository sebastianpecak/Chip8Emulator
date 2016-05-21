//
// Created by sebastian on 12.05.16.
//

#ifndef CHIP8EMULATOR_MYGAME_H
#define CHIP8EMULATOR_MYGAME_H

typedef unsigned char Byte;

Byte MyGameRom[] = {
        // Clear screen
        0x00, 0xE0,             // 0-1B
        // Main object size 8x5
        // Put object position into registres v0-x v1-y
        0x60, 0x00,             // 2-3B
        0x61, 0x00,             // 4-5B

        // Jump to main code
        0x12, 0x15,              // 6-7B

        // Lets make some image   8-12B
        // Main object
        0b00011000,
        0b00100100,
        0b01000010,
        0b10000001,
        0b01111110,

        // Draw image
        // Set I
        0xA2, 0x08,             // 13-14B
        // clear screen
        0x00, 0xE0,             // 15-16B
        // Draw image at position v0 v1
        0xD0, 0x15,              // 17-18B
        // Return from subroutine
        0x00, 0xEE,                  // 19-20B

        // Main code
        // Set step
        0x62, 0x01,             // 21-22B
        // Draw main object
        // Call draw imgae
        0x22, 0x0D,         // 23-24B
        // Set direction x
        0x63, 0x01,             // 25-26
        // Set dir y
        0x64, 0x01,             // 27-28

        // Skip if vx =0
        0x30, 0x00,             // 29-30
        // Jump to next
        0x12, 0x23,              // 31-32
        // Change dir if x==0
        0x63, 0x01,             // 33-34

        // Skip if y==0
        0x31, 0x00,             // 35-36
        // Jump to next
        0x12, 0x29,             // 37-38
        // Change dir if y==0
        0x64, 0x01,             // 39-40

        // Skip if x==56
        0x30, 0x38,             // 41-42
        // Jump to next
        0x12, 0x2F,             // 43-44
        // Change dir if y==0
        0x63, 0x00,             // 45-46

        // Skip if y==27
        0x31, 0x1B,             // 47-48
        // Jump to next
        0x12, 0x35,             // 49-50
        // Change dir if y==0
        0x64, 0x00,             // 51-52

        // Accordingly to drirection move target x
        0x33, 0x00,              // 53-54
        // Jump to next instruction
        0x12, 0x3B,              // 55-56
        // if equal - call move left
        0x22, 0x57,              // 57-58

        // Accordingly to drirection move target x
        0x33, 0x01,              // 59-60
        // Jump to next instruction
        0x12, 0x41,              // 61-62
        // if equal - call move right
        0x22, 0x5B,              // 63-64

        // Accordingly to drirection move target y
        0x34, 0x00,              // 65-66
        // Jump to next instruction
        0x12, 0x47,              // 67-68
        // if equal - call move up
        0x22, 0x4F,              // 69-70

        // Accordingly to drirection move target y
        0x34, 0x01,              // 71-72
        // Jump to next instruction
        0x12, 0x4D,              // 73-74
        // if equal - call move down
        0x22, 0x53,              // 75-76

        // Jump to beginning of main loop
        0x12, 0x17,             // 77-78

        // Move up
        0x81, 0x25,             // 79-80
        // Return
        0x00, 0xEE,             // 81-82

        // Move down
        0x81, 0x24,              // 83-84
        // Return
        0x00, 0xEE,             // 85-86

        // Move left
        0x80, 0x25,             // 87-88
        // Return
        0x00, 0xEE,              // 89-90

        // Move right
        0x80, 0x24,             // 91-92
        // Return
        0x00, 0xEE            // 93-94
};

#endif //CHIP8EMULATOR_MYGAME_H
