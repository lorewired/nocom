#pragma once

#include "src/systems/events/Events.hh"
#include "src/systems/GameContext.hh"
#include "src/core/Keyboard.hh"
#include "src/core/Snapshot.hh"

#include <thread>
#include <atomic>

// namespace Game::Systems { class GameContext; }

namespace Game::Core::Threads {

    class ThreadsManagement {
        std::unique_ptr<std::thread> aiThread;
        std::atomic<bool> isRunning = true;
        Game::Core::Snapshot snapshot;

    public:
        ThreadsManagement() = default;
        ThreadsManagement(Game::Systems::GameContext&eventsPool);
        
        // AI Thread
        void AIThreadListener(Game::Systems::GameContext& gameCtx);
        void UpdateSnapshot(Game::Systems::GameContext& gameCtx);
        
        void RunAIThread(Game::Systems::GameContext& gameCtx);
        void StopAIThread();
        // AI Thread end

        // helper functions
        bool ValidCoords(Game::Systems::GameContext& gameCtx, const Game::Utils::Vec2<int, int>& targetCoords) {
            return targetCoords.first >= 0 &&
            targetCoords.second >= 0 &&
            targetCoords.first < gameCtx.CurrentRoom()->GetMap().Width() &&
            targetCoords.second < gameCtx.CurrentRoom()->GetMap().Height() &&
            gameCtx.CurrentRoom()->GetMap().At(targetCoords).Type() != Game::Entities::CellType::WALL;
        }
        // helper functions end
    };
    
}