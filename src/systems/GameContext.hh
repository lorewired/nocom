    #pragma once

    #include "src/procedural_generation/ProceduralGeneration.hh"
    #include "src/systems/events/Events.hh"
    #include "src/entities/Human.hh"
    #include "src/entities/Enemy.hh"

    #include <queue>
    #include <mutex>
    #include <condition_variable>

    namespace Game::Systems {

        class GameContext {
        protected:
            // using unique_ptr to avoid Object Slicing
            std::queue<std::unique_ptr<Game::Systems::Events::IEvent>> eventsPool;
            std::mutex eventsPoolMutex;

            std::shared_ptr<Game::ProceduralGeneration::MapNode> initialRoom = nullptr;
            std::shared_ptr<Game::ProceduralGeneration::MapNode> currentRoom = nullptr;

            Game::Entities::Human player;
        public:
            GameContext() = default;
            std::mutex& EventsPoolMutex() { return eventsPoolMutex; }
            std::queue<std::unique_ptr<Game::Systems::Events::IEvent>>& EventsPool() { return eventsPool; }
            std::shared_ptr<Game::ProceduralGeneration::MapNode> InitialRoom() { return initialRoom; }
            std::shared_ptr<Game::ProceduralGeneration::MapNode> CurrentRoom() { return currentRoom; }
            Game::Entities::Human& Player() { return player; }

            template<typename T, typename... Args> void PushEvent(Args&&... args) {
                if constexpr (! std::is_base_of<Game::Systems::Events::IEvent, T>::value) return;
                // locking events pool
                std::unique_lock<std::mutex> eventsPoolLock(eventsPoolMutex);
                eventsPool.push(std::make_unique<T>(std::forward<Args>(args)...));
            }

            void SetCurrentRoom(std::shared_ptr<Game::ProceduralGeneration::MapNode> room) {
                if (!initialRoom) initialRoom = room;
                currentRoom = room;
            }
        };

    }
