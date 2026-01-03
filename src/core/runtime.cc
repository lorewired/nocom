#include "runtime.hh"

void Game::Core::Runtime::RunGame() {
    initialRoom = currentRoom = Game::ProceduralGeneration::GenerateRooms(Game::Utils::r32ir(5, 10));
    window = Game::Core::Window(initialRoom);
    player.SetCoords(initialRoom->GetMap().Width() >> 1, initialRoom->GetMap().Height() >> 1);

    Game::Terminal::HideCursor();
    Game::Terminal::CleanScreen();
    
    while (player.Hp() > 0) {
        window.Render(currentRoom);
        window.RenderPlayer(player);
        window.FinishRender(currentRoom);
        HandlePlayerAction(Game::Core::Keyboard::ReadPlayerInput());
        HandleEvents();
        Wait();
    }
}

void Game::Core::Runtime::HandleEvents() {
    
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
    Game::Utils::Vec2 new_coords = player.Coords();
    switch (dir) {
        case 'w': new_coords.y = player.Y() - 1; break;
        case 'a': new_coords.x = player.X() - 1; break;
        case 's': new_coords.y = player.Y() + 1; break;
        case 'd': new_coords.x = player.X() + 1; break;
    }
    if (! ValidCoords(new_coords)) return;
    player.SetCoords(new_coords);
}

bool Game::Core::Runtime::ValidCoords(const Game::Utils::Vec2& new_coords)
{
    return new_coords.x >= 0 &&
           new_coords.y >= 0 &&
           new_coords.x < currentRoom->GetMap().Width() &&
           new_coords.y < currentRoom->GetMap().Height() &&
           currentRoom->GetMap().At(new_coords).Type() != Game::Entities::CellType::WALL;
}

void Game::Core::Runtime::Wait() { std::this_thread::sleep_for(std::chrono::milliseconds(30)); }