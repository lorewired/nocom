#pragma once

#include <conio.h>

namespace Game::Core::Keyboard {

    inline bool* CreateValidKeys() {
        static bool map[256] {};
        map[27] = true;
        map['w'] = true;
        map['a'] = true;
        map['s'] = true;
        map['d'] = true;
        map[' '] = true;
        return map;
    }
    
    inline bool* validKeys = CreateValidKeys();
    
    bool IsKeyValid(const char key);
    char ReadPlayerInput();
    
}