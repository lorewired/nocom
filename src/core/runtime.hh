#pragma once

#include "src/procedural-generation/proc-gen.hh"
#include "src/entities/human.hh"
#include "keyboard.hh"
#include "window.hh"

#include <thread>
#include <chrono>
#include <memory>

namespace Game::Core {

    class Runtime {
        Game::Core::Window window;

        Game::Entities::Human player;

        std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom;
        std::shared_ptr<Game::ProceduralGeneration::MapNode> currentRoom;
        
    public:
        Runtime() = default;

        void RunGame();

        void HandlePlayerAction(const char input);
        void HandlePlayerMovement(const char dir);

        void HandleEvents();

        bool ValidCoords(const Game::Utils::Vec2& coords);
        void Wait();
    };

}