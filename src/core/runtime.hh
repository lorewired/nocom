#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/systems/events/Events.hh"
#include "src/systems/GameContext.hh"
#include "src/entities/Human.hh"
#include "Keyboard.hh"
#include "Window.hh"

#include <thread>
#include <chrono>
#include <memory>

#include <queue>

namespace Game::Core {

    class Runtime {
        Game::Core::Window window;

        Game::Systems::GameContext gameContext;

        Game::Systems::Events::EventsHandler eventsHandler;
        std::queue<Game::Systems::Events::EventContext> eventsPoll;
        // TODO: for each eventHandleFunction implement the insertion into the events poll
        
    public:
        Runtime() = default;

        void RunGame();

        void HandlePlayerAction(const char input);
        void HandlePlayerMovement(const char dir);

        bool ValidCoords(const Game::Utils::Vec2<int, int>& coords);
        void Wait();
    };

}