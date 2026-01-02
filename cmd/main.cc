#include <iostream>

#include "src/core/runtime.hh"

int main(void) {
    Game::Core::Runtime runtime;
    runtime.RunGame();
    return EXIT_SUCCESS;
}