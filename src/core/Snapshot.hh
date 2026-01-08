#pragma once

#include "src/utils/Vec2.hh"

#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace Game::Systems { class GameContext; }
namespace Game::ProceduralGeneration { class MapNode; }

namespace Game::Core {

    struct AIData {
        std::shared_ptr<Game::ProceduralGeneration::MapNode> currentRoom;
        std::vector<Game::Utils::Vec2<int, int>> enemiesCoords;
        Game::Utils::Vec2<int, int> playerCoords;
    };
    
    class Snapshot {
        AIData aiData;
        std::condition_variable notifier;
        std::mutex mutex;
        bool ready = false;
    public:
        Snapshot() = default;

        std::mutex& Mutex();
        std::condition_variable& Notifier();

        const AIData& Data() const { return aiData; }

        bool Ready() const;
        void Update(Game::Systems::GameContext& gameCtx);
    };

}