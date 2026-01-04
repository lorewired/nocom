#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/entities/Human.hh"
#include "Terminal.hh"

#include <memory>

namespace Game::Core {

    class Window {
        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        
    public:
        Window() = default;
        Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom);

        void Render(std::shared_ptr<Game::ProceduralGeneration::MapNode> room);
        void RenderPlayer(Game::Entities::Human& player);
        void FinishRender(std::shared_ptr<Game::ProceduralGeneration::MapNode>& room);
        // void RenderEnemy(const Game::Entities::Enemy& enemy);
    };

}