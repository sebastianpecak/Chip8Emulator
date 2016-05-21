//
// Created by sebastian on 14.05.16.
//

#include "Chip8Emulator.h"
#include "Keyboard.h"

// Binding mask
std::array<Word, 16> Chip8Emulator::_bindingsMask = {
        // 0x0xxx
        0x00FF,
        // 0x1xxx
        0xF000,
        // 0x2xxx
        0xF000,
        // 0x3xxx
        0xF000,
        // 0x4xxx
        0xF000,
        // 0x5xxx
        0xF000,
        // 0x6xxx
        0xF000,
        // 0x7xxx
        0xF000,
        // 0x8xxx
        0xF00F,
        // 0x9xxx
        0xF000,
        // 0xAxxx
        0xF000,
        // 0xBxxx
        0xF000,
        // 0xCxxx
        0xF000,
        // 0xDxxx
        0xF000,
        // 0xExxx
        0xF0FF,
        // 0xFxxx
        0xF0FF
};

void Chip8Emulator::initBindings() {
    // Clear screen
    _opcodeBindings.add(0x00E0, &Chip8Emulator::opcode_cls);
    // Return from subroutine
    _opcodeBindings.add(0x00EE, &Chip8Emulator::opcode_ret);
    // Jump to address
    _opcodeBindings.add(0x1000, &Chip8Emulator::opcode_jump_addr);
    // Call subroutine at address
    _opcodeBindings.add(0x2000, &Chip8Emulator::opcode_call_addr);
    // Skip next if vx == nn
    _opcodeBindings.add(0x3000, &Chip8Emulator::opcode_se_reg_val);
    // Skip next if vx != nn
    _opcodeBindings.add(0x4000, &Chip8Emulator::opcode_sne_reg_val);
    // Skip next if xv == vy
    _opcodeBindings.add(0x5000, &Chip8Emulator::opcode_se_reg_reg);
    // Set vx to nn
    _opcodeBindings.add(0x6000, &Chip8Emulator::opcode_ld_reg_val);
    // Set vx += nn
    _opcodeBindings.add(0x7000, &Chip8Emulator::opcode_add_reg_val);
    // Set vx to vy
    _opcodeBindings.add(0x8000, &Chip8Emulator::opcode_ld_reg_reg);
    // Set vx to vx or vy
    _opcodeBindings.add(0x8001, &Chip8Emulator::opcode_or_reg_reg);
    // Set vx to vx and vy
    _opcodeBindings.add(0x8002, &Chip8Emulator::opcode_and_reg_reg);
    // Set vx to vx xor vy
    _opcodeBindings.add(0x8003, &Chip8Emulator::opcode_xor_reg_reg);
    // Set vx += vy
    _opcodeBindings.add(0x8004, &Chip8Emulator::opcode_add_reg_reg);
    // Set vx -= vy
    _opcodeBindings.add(0x8005, &Chip8Emulator::opcode_sub_reg_reg);
    // Set vx >>= 1
    _opcodeBindings.add(0x8006, &Chip8Emulator::opcode_shr_reg);
    // Set vx -= vy
    _opcodeBindings.add(0x8007, &Chip8Emulator::opcode_subn_reg_reg);
    // Set vx <<= 1
    _opcodeBindings.add(0x800E, &Chip8Emulator::opcode_shl_reg);
    // Skip next if vx != vy
    _opcodeBindings.add(0x9000, &Chip8Emulator::opcode_sne_reg_reg);
    // Set i to nnn
    _opcodeBindings.add(0xA000, &Chip8Emulator::opcode_ld_i_addr);
    // Jump to v0 + address
    _opcodeBindings.add(0xB000, &Chip8Emulator::opcode_jump_v0_addr);
    // Set vx to rand and nn
    _opcodeBindings.add(0xC000, &Chip8Emulator::opcode_rand_reg_val);
    // Draw sprite
    _opcodeBindings.add(0xD000, &Chip8Emulator::opcode_draw_reg_reg_val);
    // Skip next if key in vx is pressed
    _opcodeBindings.add(0xE09E, &Chip8Emulator::opcode_skp_reg);
    // Skip next if key in vx is not pressed
    _opcodeBindings.add(0xE0A1, &Chip8Emulator::opcode_sknp_reg);
    // Set vx to dt
    _opcodeBindings.add(0xF007, &Chip8Emulator::opcode_ld_reg_dt);
    // Wait for a key press and set vx
    _opcodeBindings.add(0xF00A, &Chip8Emulator::opcode_ld_reg_key);
    // Set dt to vx
    _opcodeBindings.add(0xF015, &Chip8Emulator::opcode_ld_dt_reg);
    // Set st to vx
    _opcodeBindings.add(0xF018, &Chip8Emulator::opcode_ld_st_reg);
    // Add vx to i
    _opcodeBindings.add(0xF01E, &Chip8Emulator::opcode_add_i_reg);
    // Set i to location of character in vx
    _opcodeBindings.add(0xF029, &Chip8Emulator::opcode_ld_f_reg);
    // Store binary-coded numbers
    _opcodeBindings.add(0xF033, &Chip8Emulator::opcode_ld_b_reg);
    // Store v0-vx in memory i-i+x
    _opcodeBindings.add(0xF055, &Chip8Emulator::opcode_ld_array_i_reg);
    // Store i-i+x in v0-vx
    _opcodeBindings.add(0xF065, &Chip8Emulator::opcode_ld_reg_array_i);
}

void Chip8Emulator::opcode_cls() {
    for(int i=0; i<64;i++) _videoMemory[i].fill(BlackPixel);
}

void Chip8Emulator::opcode_ret() {
    _pc = _stack[--_stackPointer];
}

void Chip8Emulator::opcode_jump_addr() {
    _pc = (_opcode & 0x0FFF) - 2;
}

void Chip8Emulator::opcode_call_addr() {
    _stack[_stackPointer++] = _pc;
    _pc = (_opcode & 0x0FFF) - 2;
}

void Chip8Emulator::opcode_se_reg_val() {
    if(_V[(0x0F00 & _opcode) >> 8] == (_opcode & 0x00FF)) _pc+=2;
}

void Chip8Emulator::opcode_sne_reg_val() {
    if(_V[(0x0F00 & _opcode) >> 8] != (_opcode & 0x00FF)) _pc+=2;
}

void Chip8Emulator::opcode_se_reg_reg() {
    if(_V[(_opcode & 0x0F00) >> 8] == _V[(_opcode & 0x00F0) >> 4]) _pc+=2;
}

void Chip8Emulator::opcode_ld_reg_val() {
    _V[(_opcode & 0x0F00) >> 8] = (_opcode & 0x00FF);
}

void Chip8Emulator::opcode_add_reg_val() {
    _V[(_opcode & 0x0F00) >> 8] += (_opcode & 0x00FF);
}

void Chip8Emulator::opcode_ld_reg_reg() {
    _V[(_opcode & 0x0F00) >> 8] = _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_or_reg_reg() {
    _V[(_opcode & 0x0F00) >> 8] |= _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_and_reg_reg() {
    _V[(_opcode & 0x0F00) >> 8] &= _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_xor_reg_reg() {
    _V[(_opcode & 0x0F00) >> 8] ^= _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_add_reg_reg() {
    if(_V[(_opcode & 0x00F0) >> 4] > (0xFF - _V[(_opcode & 0x0F00) >> 8]))
        _V[0xF] = 1; //carry
    else
        _V[0xF] = 0;
    _V[(_opcode & 0x0F00) >> 8] += _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_sub_reg_reg() {
    if(_V[(_opcode & 0x00F0) >> 4] > _V[(_opcode & 0x0F00) >> 8]) _V[0xF] = 0; // there is a borrow
    else _V[0xF] = 1;
    _V[(_opcode & 0x0F00) >> 8] -= _V[(_opcode & 0x00F0) >> 4];
}

void Chip8Emulator::opcode_shr_reg() {
    _V[0xF] = _V[(_opcode & 0x0F00) >> 8] & 0b00000001;
    _V[(_opcode & 0x0F00) >> 8] >>= 1;
}

void Chip8Emulator::opcode_subn_reg_reg() {
    if(_V[(_opcode & 0x00F0) >> 4] > _V[(_opcode & 0x0F00) >> 8]) _V[0xF] = 1;
    else _V[0xF] = 0;
    _V[(_opcode & 0x0F00) >> 8] = _V[(_opcode & 0x00F0) >> 4] - _V[(_opcode & 0x0F00) >> 8];
}

void Chip8Emulator::opcode_shl_reg() {
    _V[0xF] = _V[(_opcode & 0x0F00) >> 8] >> 7;
    _V[(_opcode & 0x0F00) >> 8] <<= 1;
}

void Chip8Emulator::opcode_sne_reg_reg() {
    if(_V[(_opcode & 0x0F00) >> 8] != _V[(_opcode & 0x00F0) >> 4]) _pc += 2;
}

void Chip8Emulator::opcode_ld_i_addr() {
    _I = (_opcode & 0x0FFF);
}

void Chip8Emulator::opcode_jump_v0_addr() {
    _pc = (_opcode & 0x0FFF) + _V[0] - 2;
}

void Chip8Emulator::opcode_rand_reg_val() {
    srand(time(nullptr));
    Byte randomNumber = (Byte)rand()%256, nn = (Byte)(_opcode & 0x00FF);
    _V[(_opcode & 0x0F00) >> 8] = randomNumber & nn;
}

void Chip8Emulator::opcode_draw_reg_reg_val() {
    int spriteSize = (_opcode & 0x000F), x = _V[(_opcode & 0x0F00) >> 8], y = _V[(_opcode & 0x00F0) >> 4];
    for(int i=0; i<spriteSize; i++) {
        Byte line = _ramMemory[_I + i];
        for(int j=0; j<8;j++) {
            Byte pixel = (line & (0b10000000 >>j)) >> (7-j);
            // Alternate version
            // Validate coordinates
            if((x+j)>=0 && (x+j)<DefaultDisplayX && (y+i)>=0 && (y+i)<DefaultDisplayY) {
                _V[0xF] = _videoMemory[x + j][y + i] & pixel;
                _videoMemory[x + j][y + i] ^= pixel;
            }
        }
    }
    _requestUpdate = true;
}

void Chip8Emulator::opcode_skp_reg() {
    if(_keybaordDevice->_keyboard[_V[(_opcode & 0x0F00) >> 8]] != 0) _pc += 2;
}

void Chip8Emulator::opcode_sknp_reg() {
    if(_keybaordDevice->_keyboard[_V[(_opcode & 0x0F00) >> 8]] == 0) _pc += 2;
}

void Chip8Emulator::opcode_ld_reg_dt() {
    _V[(_opcode & 0x0F00) >> 8] = _delayTimer;
}

void Chip8Emulator::opcode_ld_reg_key() {
    bool pressed = false;
    for(int i=0; i<16;i++) {
        if(_keybaordDevice->_keyboard[i] != 0) {
            _V[(_opcode & 0x0F00) >> 8] = i;
            pressed = true;
            break;
        }
    }
    // Loop until key is pressed
    if(!pressed) _pc -= 2;
}

void Chip8Emulator::opcode_ld_dt_reg() {
    _delayTimer = _V[(_opcode & 0x0F00) >> 8];
}

void Chip8Emulator::opcode_ld_st_reg() {
    _soundTimer = _V[(_opcode & 0x0F00) >> 8];
}

void Chip8Emulator::opcode_add_i_reg() {
    _I += _V[(_opcode & 0x0F00) >> 8];
}

void Chip8Emulator::opcode_ld_f_reg() {
    _I = _V[(_opcode & 0x0F00) >> 8] * 5;
}

void Chip8Emulator::opcode_ld_b_reg() {
    _ramMemory[_I] = _V[(_opcode & 0x0F00) >> 8] / 100;
    _ramMemory[_I + 1] = (_V[(_opcode & 0x0F00) >> 8] / 10) % 10;
    _ramMemory[_I + 2] = (_V[(_opcode & 0x0F00) >> 8] % 100) % 10;
}

void Chip8Emulator::opcode_ld_array_i_reg() {
    int x = (_opcode & 0x0F00) >> 8;
    for(int i=0; i <= x; i++) _ramMemory[_I + x] = _V[x];
    _I += ((_opcode & 0x0F00) >> 8) + 1;
}

void Chip8Emulator::opcode_ld_reg_array_i() {
    int x = (_opcode & 0x0F00) >> 8;
    for(int i=0; i <= x; i++) _V[x] = _ramMemory[_I + x];
    _I += ((_opcode & 0x0F00) >> 8) + 1;
}