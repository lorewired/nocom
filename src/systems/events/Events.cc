#include "Events.hh"

void Game::Systems::Events::EventsHandler::LoadEvents
(
    GameContextType& gameContext,
    std::queue<Game::Systems::Events::EventContext>& eventsPoll
)
{
    // check all events
    using namespace Game::Systems::Events;
    
    if (eventsPoll.empty()) return;
    
    EventContext eventContext = eventsPoll.front();
    eventsPoll.pop();
    
    switch (eventContext.Type()) {
        case EventType::PlayerMove:
            RunEventPlayerMove(eventContext, gameContext, eventsPoll);
            break;
        case EventType::RoomChange:
            RunEventRoomChange(eventContext, gameContext);
            break;
    }
}

void Game::Systems::Events::RunEventRoomChange
(
    EventContext& eventContext,
    GameContextType& gameContext
)
{
    auto& player = gameContext.Player();
    auto currentRoom = gameContext.CurrentRoom();
    auto [nextRoom, doorCoords] = currentRoom->GetNextRoom(player.Coords());
    player.SetCoords(doorCoords);
}

void Game::Systems::Events::RunEventPlayerMove
(
    EventContext& eventContext,
    GameContextType& gameContext,
    std::queue<Game::Systems::Events::EventContext>& eventsPoll
)
{
    auto& player = gameContext.Player();
    auto& map    = gameContext.CurrentRoom()->GetMap();

    if (map.At(player.Coords()).Type() == Game::Entities::CellType::DOOR)
        eventsPoll.push(EventContext(EventType::RoomChange));
}