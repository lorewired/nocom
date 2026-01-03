#include "window.hh"

Game::Core::Window::Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom)
: initialRoom(_initialRoom) {}

void Game::Core::Window::Render(std::shared_ptr<Game::ProceduralGeneration::MapNode> room) {
    Game::Terminal::PositionCursor(0, 0);

    Game::Entities::Map& map = room->GetMap();

    for (int y = 0; y < map.Height(); y++) {
        for (int x = 0; x < map.Width(); x++) {
            std::cout << map.At(x, y).Rep();
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    std::cout.flush();
}

void Game::Core::Window::RenderPlayer(const Game::Entities::Human& player) {
    // TODO: move cursor and print player.
    Game::Terminal::PositionCursor(player.X(), player.Y());
    std::cout << "O";
    std::cout.flush();
}

void Game::Core::Window::FinishRender(const std::shared_ptr<Game::ProceduralGeneration::MapNode>& room) {
    Game::Terminal::PositionCursor(0, room->GetMap().Height() + 1);
}