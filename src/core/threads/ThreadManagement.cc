#include "ThreadsManagement.hh"

Game::Core::Threads::ThreadsManagement::ThreadsManagement(Game::Systems::GameContext& gameCtx) {}

void Game::Core::Threads::ThreadsManagement::UpdateSnapshot(Game::Systems::GameContext& gameCtx) {
    std::unique_lock<std::mutex> snapshot_lock(snapshot.Mutex());

    snapshot.Update(gameCtx);

    snapshot_lock.unlock();
    
    snapshot.Notifier().notify_one();
}
