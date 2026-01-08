#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/systems/GameContext.hh"
#include "threads/ThreadsManagement.hh"
#include "src/systems/events/Events.hh"
#include "src/entities/Human.hh"
#include "Keyboard.hh"
#include "Window.hh"

#include <chrono>

namespace Game::Core {

    class Runtime {
        Game::Core::Window window;
        Game::Systems::GameContext gameCtx;
        Game::Systems::Events::EventsHandler eventsHandler;
        Game::Core::Threads::ThreadsManagement threadsManagement;
        // TODO: for each eventHandleFunction implement the insertion into the events pool
    
    public:
        Runtime() = default;

        void RunGame();
        void Wait();

        void HandlePlayerAction(const char input);
        void HandlePlayerMovement(const char dir);
    };

}