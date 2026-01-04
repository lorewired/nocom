#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/entities/Human.hh"

#include <queue>
#include <memory>

namespace Game::Systems {

    class GameContext {
    protected:
        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        std::shared_ptr<Game::ProceduralGeneration::MapNode> currentRoom;
        Game::Entities::Human player;
    public:
        GameContext() = default;
        std::shared_ptr<Game::ProceduralGeneration::MapNode> InitialRoom() { return initialRoom; }
        std::shared_ptr<Game::ProceduralGeneration::MapNode> CurrentRoom() { return currentRoom; }
        Game::Entities::Human& Player() { return player; }
    };
    
}