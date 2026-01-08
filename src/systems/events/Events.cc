#include "Events.hh"

#include "src/systems/GameContext.hh"

void Game::Systems::Events::EventsHandler::LoadEvents(GameContextType& gameCtx)
{
    std::unique_lock<std::mutex> eventsPoolLock(gameCtx.EventsPoolMutex());
    
    // check all events
    auto& eventsPool = gameCtx.EventsPool();

    if (eventsPool.empty())
        return;
    
    auto event = std::move(eventsPool.front()); // transform to an rvalue
    eventsPool.pop();

    eventsPoolLock.unlock();

    if (event)
        event->Execute(gameCtx);
}