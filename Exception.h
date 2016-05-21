//
// Created by sebastian on 15.05.16.
//

#ifndef CHIP8EMULATOR_EXCEPTION_H
#define CHIP8EMULATOR_EXCEPTION_H

#include <string>

class Exception {
    std::string _name;
    std::string _message;
    int _number;
public:
    Exception(const char*name = "", const char*message = "", int number  = 0){
        _name = name;
        _message = message;
        _number = number;
    }

    std::string getName() const {
        return _name;
    }

    std::string getMessage() const {
        return _message;
    }

    int getNumber() const {
        return _number;
    }
};


#endif //CHIP8EMULATOR_EXCEPTION_H