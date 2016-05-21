//
// Created by sebastian on 05.05.16.
//

#ifndef CHIP8EMULATOR_CHIP8EMULATOR_H
#define CHIP8EMULATOR_CHIP8EMULATOR_H

#include "Chip8Types.h"
#include "Binding.h"

class Chip8Emulator {
    // Current opcode
    Word _opcode;
    // Index register
    Word _I;
    // Program counter
    Word _pc;
    // Two timers
    Byte _delayTimer;
    Byte _soundTimer;
    // Cpu registers
    std::array<Byte, 16> _V;
    // Stack
    Byte _stackPointer;
    std::array<Word, 16> _stack;
    // VM memory
    std::array<Byte, 4096> _ramMemory;
    // New verion - currently being developed
    std::array<std::array<Pixel, 32>, 64> _videoMemory;
    // Screen update request flag
    bool _requestUpdate;



    // Associated with pixelmap
    // Display object will be able to use internals of Chip8Emulator
    friend class Display;


    // Keyboard
    Keyboard *_keybaordDevice;
    friend class Keybaord;

    static Byte chip8_fontset[];

    // Ophandlers
    void opcode_cls();
    void opcode_ret();
    void opcode_jump_addr();
    void opcode_call_addr();
    void opcode_se_reg_val();
    void opcode_sne_reg_val();
    void opcode_se_reg_reg();
    void opcode_ld_reg_val();
    void opcode_add_reg_val();
    void opcode_ld_reg_reg();
    void opcode_or_reg_reg();
    void opcode_and_reg_reg();
    void opcode_xor_reg_reg();
    void opcode_add_reg_reg();
    void opcode_sub_reg_reg();
    void opcode_shr_reg();
    void opcode_subn_reg_reg();
    void opcode_shl_reg();
    void opcode_sne_reg_reg();
    void opcode_ld_i_addr();
    void opcode_jump_v0_addr();
    void opcode_rand_reg_val();
    void opcode_draw_reg_reg_val();
    void opcode_skp_reg();
    void opcode_sknp_reg();
    void opcode_ld_reg_dt();
    void opcode_ld_reg_key();
    void opcode_ld_dt_reg();
    void opcode_ld_st_reg();
    void opcode_add_i_reg();
    void opcode_ld_f_reg();
    void opcode_ld_b_reg();
    void opcode_ld_array_i_reg();
    void opcode_ld_reg_array_i();

    Binding<Word, OpcodeDelegate, 40> _opcodeBindings;
    // Mask depends on first 4BIT number of opcode
    // mask could be 0xF00F, 0xF000, 0xF0FF
    // Than opcode anded with mask gives us binding number
    static std::array<Word, 16> _bindingsMask;

    void initBindings();

public:
    Chip8Emulator(std::istream* = nullptr);

    void emulationStep();
    void loadGame(std::istream*);
    void loadState(std::istream*);
    void saveEmulatorState(std::ostream*);
    void connectKeyboard(Keyboard*);
};

#endif //CHIP8EMULATOR_CHIP8EMULATOR_H
