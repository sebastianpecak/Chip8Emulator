//
// Created by sebastian on 15.05.16.
//

#include "Keyboard.h"

void Keyboard::update(SDL_Event *event) {
    // We determine weather keyboard event occured in main loop
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    _keyboard[0] = state[SDL_SCANCODE_X];
    _keyboard[1] = state[SDL_SCANCODE_1];
    _keyboard[2] = state[SDL_SCANCODE_2];
    _keyboard[3] = state[SDL_SCANCODE_3];
    _keyboard[4] = state[SDL_SCANCODE_Q];
    _keyboard[5] = state[SDL_SCANCODE_W];
    _keyboard[6] = state[SDL_SCANCODE_E];
    _keyboard[7] = state[SDL_SCANCODE_A];
    _keyboard[8] = state[SDL_SCANCODE_S];
    _keyboard[9] = state[SDL_SCANCODE_D];
    _keyboard[0xa] = state[SDL_SCANCODE_Z];
    _keyboard[0xb] = state[SDL_SCANCODE_C];
    _keyboard[0xc] = state[SDL_SCANCODE_4];
    _keyboard[0xd] = state[SDL_SCANCODE_R];
    _keyboard[0xe] = state[SDL_SCANCODE_F];
    _keyboard[0xf] = state[SDL_SCANCODE_V];
}