#pragma once

#include "src/procedural-generation/proc-gen.hh"
#include "src/entities/human.hh"
#include "terminal.hh"

#include <memory>

namespace Game::Core {

    class Window {
        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        
    public:
        Window() = default;
        Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom);

        void Render(std::shared_ptr<Game::ProceduralGeneration::MapNode> room);
        void RenderPlayer(const Game::Entities::Human& player);
        void FinishRender(const std::shared_ptr<Game::ProceduralGeneration::MapNode>& room);
        // void RenderEnemy(const Game::Entities::Enemy& enemy);
};

}