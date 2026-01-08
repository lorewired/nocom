#include "Events.hh"

#include "src/systems/GameContext.hh"

void Game::Systems::Events::EventRoomChange::Execute(GameContextType& gameCtx) {
    auto& player = gameCtx.Player();
    auto currentRoom = gameCtx.CurrentRoom();
    auto [nextRoom, doorCoords] = currentRoom->GetNextRoom(player.Coords());
    player.SetCoords(doorCoords);
    gameCtx.SetCurrentRoom(nextRoom);
}

void Game::Systems::Events::EventPlayerDeath::Execute(GameContextType& gameCtx) {
    gameCtx.Player().SetHp(0);
}

void Game::Systems::Events::EventPlayerMove::Execute(GameContextType& gameCtx) {
    if (! Game::Entities::Map::ValidCoords(gameCtx.CurrentRoom()->GetMap(), targetX, targetY))
        return;
    
    auto& player = gameCtx.Player();
    auto& map    = gameCtx.CurrentRoom()->GetMap();

    player.SetCoords(targetX, targetY);

    if (map.At(player.Coords()).Type() == Game::Entities::CellType::DOOR)
        gameCtx.PushEvent<EventRoomChange>();
}

void Game::Systems::Events::EventEnemyMove::Execute(GameContextType& gameCtx) {
    if (!enemy) return;
    
    if (! Game::Entities::Map::ValidCoords(gameCtx.CurrentRoom()->GetMap(), targetX, targetY))
        return;
    
    enemy->SetCoords(targetX, targetY);

    if (gameCtx.Player().Coords() == enemy->Coords())
        gameCtx.PushEvent<EventPlayerDeath>();
}