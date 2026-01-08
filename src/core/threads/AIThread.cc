#include "ThreadsManagement.hh"
#include "src/utils/CardinalCoords.hh"
#include "src/utils/Rand.hh"

void Game::Core::Threads::ThreadsManagement::StopAIThread() {
    isRunning = false;
    snapshot.Notifier().notify_all();
    
    if (aiThread && aiThread->joinable()) {
        aiThread->join();
    }
}

void Game::Core::Threads::ThreadsManagement::AIThreadListener(Game::Systems::GameContext& gameCtx) {
    while (isRunning) {
        std::unique_lock<std::mutex> snapshot_lock(snapshot.Mutex());

        snapshot.Notifier().wait(snapshot_lock, [this] () { return snapshot.Ready() || !isRunning; });

        if (!isRunning)
            break;

        // 33% of chance to the enemy move
        if (std::rand() % 3 == 0 && gameCtx.CurrentRoom()->Enemies().size()) {
            std::vector<Game::Utils::Vec2<int, int>> validCoords;
            auto enemy = gameCtx.CurrentRoom()->Enemies().front();
            for (int i = 0; i < 4; i++) {
                int x = enemy->X() + Game::Utils::xCoords[i];
                int y = enemy->Y() + Game::Utils::yCoords[i];
                if (Game::Entities::Map::ValidCoords(gameCtx.CurrentRoom()->GetMap(), x, y)) {
                    validCoords.emplace_back(x, y);
                }
            }
            int random_index = Game::Utils::r32ir(0, static_cast<int>(validCoords.size() - 1));
            gameCtx.PushEvent<Game::Systems::Events::EventEnemyMove>(enemy, validCoords[random_index]);
        }
    }
}

void Game::Core::Threads::ThreadsManagement::RunAIThread(Game::Systems::GameContext& gameCtx) {
    aiThread = std::make_unique<std::thread>(
        std::thread(
            &Game::Core::Threads::ThreadsManagement::AIThreadListener,
            this,
            std::ref(gameCtx)
        )
    );
}

#pragma region Events

#pragma endregion