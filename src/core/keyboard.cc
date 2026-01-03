#include "keyboard.hh"

bool Game::Core::Keyboard::IsKeyValid(const char key) { return key != '\0' && Game::Core::Keyboard::validKeys[key]; }

char Game::Core::Keyboard::ReadPlayerInput() {
    if (_kbhit()) {
        int keyCode = _getch();

        char key = static_cast<char>(keyCode);
        
        if (key >= 'A' && key <= 'Z')
            key ^= 0x20;
        
        // TODO:
        // lock_guard<mutex> lock(mtx);

        return key;
    }
    return '\0';
}