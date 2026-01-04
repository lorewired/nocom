#include "runtime.hh"

void Game::Core::Runtime::RunGame() {
    auto initialRoom = gameContext.InitialRoom();
    auto currentRoom = gameContext.CurrentRoom();
    auto& player      = gameContext.Player();

    initialRoom = currentRoom = Game::ProceduralGeneration::GenerateRooms(Game::Utils::r32ir(5, 10));
    window      = Game::Core::Window(initialRoom);

    player.SetCoords(initialRoom->GetMap().Width() >> 1, initialRoom->GetMap().Height() >> 1);

    Game::Terminal::HideCursor();
    Game::Terminal::CleanScreen();
    
    while (player.Hp() > 0) {
        window.Render(currentRoom);
        window.RenderPlayer(player);
        window.FinishRender(currentRoom);
        HandlePlayerAction(Game::Core::Keyboard::ReadPlayerInput());
        eventsHandler.LoadEvents(gameContext, eventsPoll);
        Wait();
    }
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
    Game::Utils::Vec2<int, int> new_coords = gameContext.Player().Coords();
    switch (dir) {
        case 'w': new_coords.second = gameContext.Player().Y() - 1; break;
        case 'a': new_coords.first = gameContext.Player().X() - 1; break;
        case 's': new_coords.second = gameContext.Player().Y() + 1; break;
        case 'd': new_coords.first = gameContext.Player().X() + 1; break;
    }
    if (! ValidCoords(new_coords)) return;
    gameContext.Player().SetCoords(new_coords);
}

bool Game::Core::Runtime::ValidCoords(const Game::Utils::Vec2<int, int>& new_coords)
{
    return new_coords.first >= 0 &&
           new_coords.second >= 0 &&
           new_coords.first < gameContext.CurrentRoom()->GetMap().Width() &&
           new_coords.second < gameContext.CurrentRoom()->GetMap().Height() &&
           gameContext.CurrentRoom()->GetMap().At(new_coords).Type() != Game::Entities::CellType::WALL;
}

void Game::Core::Runtime::Wait() { std::this_thread::sleep_for(std::chrono::milliseconds(30)); }