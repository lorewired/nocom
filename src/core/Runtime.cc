#include "runtime.hh"

void Game::Core::Runtime::RunGame() {
    auto generatedMap = Game::ProceduralGeneration::GenerateRooms(Game::Utils::r32ir(5, 10));
    gameCtx.SetCurrentRoom(generatedMap);

    auto& player     = gameCtx.Player();
    auto currentRoom = gameCtx.CurrentRoom();
    
    player.SetCoords(currentRoom->GetMap().Width() >> 1, currentRoom->GetMap().Height() >> 1);
    
    window = Game::Core::Window(currentRoom);
    
    auto lastRenderedRoom = gameCtx.CurrentRoom();

    Game::Terminal::HideCursor();
    Game::Terminal::CleanScreen();

    // threadsManagement.RunAIThread(gameCtx);
    
    while (player.Hp() > 0) {
        if (lastRenderedRoom != gameCtx.CurrentRoom()) {
            Game::Terminal::CleanScreen();
            lastRenderedRoom = gameCtx.CurrentRoom();
        }
        window.Render(gameCtx.CurrentRoom(), gameCtx.Player(), gameCtx.CurrentRoom()->Enemies());
        // as duas funcoes abaixo estao protegidas por um mutex da pool
        HandlePlayerAction(Game::Core::Keyboard::ReadPlayerInput());
        eventsHandler.LoadEvents(gameCtx);
        // essa de baixo por outro mutex q ntem nd haver com o de cima, q seria o mutex da snapshot
        threadsManagement.UpdateSnapshot(gameCtx);
        Wait();
    }

    // threadsManagement.StopAIThread();
}

void Game::Core::Runtime::HandlePlayerAction(const char input) {
    if (! Game::Core::Keyboard::IsKeyValid(input)) return;
    
    if (std::isdigit(input)) {
        //
        return;
    }
    
    HandlePlayerMovement(input);
}

void Game::Core::Runtime::HandlePlayerMovement(const char dir) {
    Game::Utils::Vec2<int, int> targetCoords = gameCtx.Player().Coords();
    switch (dir) {
        case 'w': targetCoords.second = gameCtx.Player().Y() - 1; break;
        case 'a': targetCoords.first = gameCtx.Player().X() - 1; break;
        case 's': targetCoords.second = gameCtx.Player().Y() + 1; break;
        case 'd': targetCoords.first = gameCtx.Player().X() + 1; break;
    }
    if (! Game::Entities::Map::ValidCoords(gameCtx.CurrentRoom()->GetMap(), targetCoords)) return;
    gameCtx.PushEvent<Game::Systems::Events::EventPlayerMove>(targetCoords);
}

void Game::Core::Runtime::Wait() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); }