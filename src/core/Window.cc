#include "Window.hh"

Game::Core::Window::Window(std::shared_ptr<Game::ProceduralGeneration::MapNode> _initialRoom)
    : initialRoom(_initialRoom) {}

void Game::Core::Window::Render(
    std::shared_ptr<Game::ProceduralGeneration::MapNode> room,
    Game::Entities::Human& player,
    std::vector<std::shared_ptr<Game::Entities::Enemy>>& enemies
)
{
    Game::Entities::Map& map = room->GetMap();
    int height = map.Height();
    int width = map.Width();

    std::vector<std::string> screenBuffer(height);

    for (int y = 0; y < height; y++) {
        screenBuffer[y].reserve(width);
        for (int x = 0; x < width; x++) {
            screenBuffer[y] += map.At(x, y).Rep();
        }
    }

    if (player.Y() >= 0 && player.Y() < height && player.X() >= 0 && player.X() < width) {
        screenBuffer[player.Y()][player.X()] = 'O';
    }

    for (auto& enemy : enemies) {
        if (enemy->Y() >= 0 && enemy->Y() < height && enemy->X() >= 0 && enemy->X() < width) {
            screenBuffer[enemy->Y()][enemy->X()] = 'U';
        }
    }

    std::stringstream ss;
    for (int y = 0; y < height; y++) {
        ss << screenBuffer[y] << '\n';
    }

    Game::Terminal::PositionCursor(0, 0);
    std::cout << ss.str();

    Game::Terminal::PositionCursor(0, height + 1);
    
    std::cout.flush();
}