//
// Created by sebastian on 14.05.16.
//

#ifndef BINDING_EXCEPTION
#define BINDING_EXCEPTION

#include "Exception.h"

class ElementNotFound : public Exception  {
public:
    ElementNotFound() : Exception("ElementNotFound", "Required element could not be found. It does not exist.", 123) {}
};

#endif  // BINDING_EXCEPTION

#ifndef CHIP8EMULATOR_BINDING_H
#define CHIP8EMULATOR_BINDING_H

#include <array>

template <typename T, typename V, int S>
class Binding {
    struct Data {
        T _key;
        V _value;
    };

    // Binding array
    std::array<Data, S> _bindings;
    int _bindingsCounter;
public:
    Binding();

    void add(T, V);
    void set(T, V);
    V get(T);
};

template <typename T, typename V, int S>
Binding<T, V, S>::Binding() {
    _bindingsCounter = 0;
}

template <typename T, typename V, int S>
void Binding<T, V, S>::add(T key, V value) {
    // check out if there already exist key
    for(auto i = 0; i < _bindingsCounter; i++) {
        if(_bindings[i]._key == key) // Do nothing
            return;
    }
    // It's a new key so we add it
    if(_bindingsCounter < S)
        _bindings[_bindingsCounter++] = {key, value};
}

template <typename T, typename V, int S>
void Binding<T, V, S>::set(T key, V value) {
    // Look up for
    for(auto i = 0; i < _bindingsCounter; i++) {
        if(_bindings[i]._key == key) {
            _bindings[i]._value = value;
            break;
        }
    }
}

template <typename T, typename V, int S>
V Binding<T, V, S>::get(T key) {
    // Look up for
    for(auto i = 0; i < _bindingsCounter; i++) {
        if(_bindings[i]._key == key) return _bindings[i]._value;
    }
    // Throw not found
    throw ElementNotFound();
}

#endif //CHIP8EMULATOR_BINDING_H
