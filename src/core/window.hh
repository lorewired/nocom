#pragma once

#include "src/procedural-generation/proc-gen.hh"

#include <memory>

namespace Game::Core {

    class Window {
        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        
    public:
        Window() = default;
        Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom);

        void Display(std::shared_ptr<Game::ProceduralGeneration::MapNode> node);
    };

}