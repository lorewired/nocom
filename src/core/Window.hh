#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/entities/Human.hh"
#include "Terminal.hh"

#include <memory>
#include <sstream>
#include <vector>
#include <string>

namespace Game::Core {

    class Window {
        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        
    public:
        Window() = default;
        Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom);

        void Render(
            std::shared_ptr<Game::ProceduralGeneration::MapNode> room,
            Game::Entities::Human& player,
            std::vector<std::shared_ptr<Game::Entities::Enemy>>& enemies
        );
    };

}