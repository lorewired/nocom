#include <iostream>

#include "../src/procedural-generation/proc-gen.hh"

int main(void) {
    std::cout << ": ";
    int n; std::cin >> n;
    auto root = ProceduralGeneration::GenerateRooms(n);
    ProceduralGeneration::DebugMap(root);
    return EXIT_SUCCESS;
}