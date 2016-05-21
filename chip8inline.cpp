//
// Created by sebastian on 17.05.16.
//

#include "Chip8Emulator.h"
#include "Display.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <SDL2/SDL_thread.h>
#include <queue>

#define CMD_CREATE "create"
#define CMD_DISPLAY "display"
#define CMD_EMULATOR "emulator"
// connect 0 1
// connect display 0 with emulator 1
#define CMD_CONNECT "connect"
#define CMD_DESTROY "destroy"
#define CMD_LIST "list"
#define CMD_QUIT "quit"
#define CMD_START "start"
#define CMD_PAUSE "pause"
#define CMD_RESET "reset"
#define CMD_DUMP "dump"

#define EXESTATUS_NORMAL 1
#define EXESTATUS_ERROR 2
#define EXESTATUS_QUITAPP 0

using namespace std;

inline void getCommand(string&);
bool validateCommand(string&);
int executeCommand(string&);

template <typename T>
struct Component {
    T *_component;
    string _name;
};

// List of emulators
vector<Component<Chip8Emulator>> _chip8Emulators;
// List of available displays
vector<Component<Display>> _displays;


// MainThread queue
queue<int> mainThreadJobs;

int main() {

    _chip8Emulators.clear();
    _displays.clear();

    // Start thread
    SDL_CreateThread([](void *data)->int {
        while(true) {

        }
    }, "mainFunction", nullptr);

    string cmdLine = "";
    for(;;) {
        getCommand(cmdLine);
        if(validateCommand(cmdLine)) {
            int status = executeCommand(cmdLine);
            if(status == EXESTATUS_ERROR) {
                Degug("\n@@ Command execution error @@\n")
            } else if(status == EXESTATUS_QUITAPP) {
                // break main loop
                break;
            }
        }
        else Degug("Invalid command @@")
    }

    Display::finish();
    return 0;
}

void getCommand(string &output) {
    do {
        cout <<"##: ";
        output = "";
        getline(cin, output);
    } while(output.length() == 0);
}

bool validateCommand(string &command) {
}

int executeCommand(string &command) {
    boost::char_separator<char> separator(" ");
    boost::tokenizer<boost::char_separator<char>> tokens(command, separator);
    boost::tokenizer<boost::char_separator<char>>::iterator begin= tokens.begin();

    if(begin.current_token() == CMD_QUIT) {
        return EXESTATUS_QUITAPP;
    } else if(begin.current_token() == CMD_CREATE) {
        begin++;
        if(begin.current_token() == CMD_EMULATOR) {
            Component<Chip8Emulator> temp;
            temp._component = new Chip8Emulator;
            if(!(++begin).at_end()) temp._name = begin.current_token();
            if(!(++begin).at_end()) {
                fstream gameFile(begin.current_token().c_str(), ios::in);
                temp._component->loadGame(&gameFile);
                gameFile.close();
            }
            _chip8Emulators.push_back(temp);
        } else if(begin.current_token() == CMD_DISPLAY) {
            Component<Display> temp;
            temp._component = new Display;
            if(!(++begin).at_end()) temp._name = begin.current_token();
            _displays.push_back(temp);
        }
    } else if(begin.current_token() == CMD_LIST) {
        begin++;
        if(begin.current_token() == CMD_EMULATOR) {
            // Display emulators list
            cout <<"Emulators:\n";
            for(int i=0; i<_chip8Emulators.size(); i++) cout <<"["<<i<<"] of_name <"<<_chip8Emulators[i]._name<<">\n";
        } else if(begin.current_token() == CMD_DISPLAY) {
            cout <<"Displays:\n";
            for(int i=0; i<_displays.size(); i++) cout <<"["<<i<<"] of_name <"<<_displays[i]._name<<">\n";
        }
    } else if(begin.current_token() == CMD_CONNECT) {
        begin++;
        // Test of lambda expresions
            [](string name)->Display* {
                for(int i=0; i<_displays.size(); i++) {
                    if(name == _displays[i]._name) return _displays[i]._component;
                }
               // throw logic_error("Element not found");

            }(begin.current_token())->connect([](string name)->Chip8Emulator* {
                for(int i=0; i<_chip8Emulators.size(); i++) {
                    if(name == _chip8Emulators[i]._name) return _chip8Emulators[i]._component;
                }
               // throw logic_error("Element not found");
            }((++begin).current_token()));
    }
}