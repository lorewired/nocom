#include "Snapshot.hh"

// Headers necessários
#include "src/systems/GameContext.hh"
#include "src/procedural_generation/ProceduralGeneration.hh" 
#include "src/entities/Enemy.hh" 

std::mutex& Game::Core::Snapshot::Mutex() { return mutex; }

std::condition_variable& Game::Core::Snapshot::Notifier() { return notifier; }

bool Game::Core::Snapshot::Ready() const { return ready; }

void Game::Core::Snapshot::Update(Game::Systems::GameContext& gameCtx) {
    auto currentRoomPtr = gameCtx.CurrentRoom();
    
    if (!currentRoomPtr) {
        return; 
    }

    aiData.playerCoords = gameCtx.Player().Coords();
    aiData.currentRoom  = currentRoomPtr; 

    aiData.enemiesCoords.clear();
    
    const auto& enemiesList = currentRoomPtr->Enemies();
    aiData.enemiesCoords.reserve(enemiesList.size());

    for (const auto& enemy : enemiesList) {
        if (enemy) { 
            aiData.enemiesCoords.push_back(enemy->Coords());
        }
    }

    ready = true;
}