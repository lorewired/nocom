#include "ProceduralGeneration.hh"
#include "src/utils/CardinalCoords.hh"

using namespace Game::ProceduralGeneration;

void Game::ProceduralGeneration::ConnectRooms(
    std::shared_ptr<MapNode> src,
    std::shared_ptr<MapNode> dst,
    NodeDir dir
)
{
    // bidirectional connection
    switch (dir) {
        case UP:
            src->SetAdjacent(UP, dst);
            dst->SetAdjacent(DOWN, src);
            break;
        case RIGHT:
            src->SetAdjacent(RIGHT, dst);
            dst->SetAdjacent(LEFT, src);
            break;
        case DOWN:
            src->SetAdjacent(DOWN, dst);
            dst->SetAdjacent(UP, src);
            break;
        case LEFT:
            src->SetAdjacent(LEFT, dst);
            dst->SetAdjacent(RIGHT, src);
    }
}

void Game::ProceduralGeneration::PositionEnemies(MapNode& mapNode) {
    Game::Entities::Map& map = mapNode.GetMap();
    std::vector<Game::Utils::Vec2<int, int>> emptyCells;
    for (int y = 0; y < map.Height(); y++) {
        for (int x = 0; x < map.Width(); x++) {
            if (map.At(x, y).Type() == Game::Entities::CellType::EMPTY) {
                emptyCells.emplace_back(x, y);
            }
        }
    }
    int random_index = Game::Utils::r32ir(0, emptyCells.size() - 1);
    Game::Utils::Vec2<int, int> random_coords = emptyCells[random_index];
    auto enemy = std::make_shared<Game::Entities::Enemy>();
    enemy->SetCoords(random_coords);
    mapNode.Enemies().push_back(enemy);
}

void Game::ProceduralGeneration::SetEmptyCells(Entities::Map& map) {
    const int height           = map.Height();
    const int width            = map.Width();
    const int totalBorderCells = (height << 1) + (width << 1);
    const int totalEmptyArea   = height * width - totalBorderCells;

    auto valid = [&height, &width] (int x, int y) { return x > 0 && y > 0 && x < width - 1 && y < height - 1; };
    
    int randomPercent      = Game::Utils::r32ir(60, 90);
    int requiredEmptyCells = totalEmptyArea * randomPercent / 100;
    int emptyCells         = 0;

    std::stack<std::pair<int, int>> stk;
    const int startX = Game::Utils::r32ir(1, width - 2);
    const int startY = Game::Utils::r32ir(1, height - 2);
    stk.emplace(startX, startY);

    int min_x, min_y;
    int max_x, max_y;

    min_x = max_x = startX;
    min_y = max_y = startY;

    while (stk.size()) {
        auto [x, y] = stk.top(); stk.pop();

        if (emptyCells == requiredEmptyCells)
            continue;

        min_x = std::min(min_x, x);
        max_x = std::max(max_x, x);
        min_y = std::min(min_y, y);
        max_y = std::max(max_y, y);

        if (map.At(x, y).Type() != Entities::CellType::EMPTY) {
            map.At(x, y).SetType(Entities::CellType::EMPTY);
            emptyCells ++;
        }

        std::vector<std::pair<int, int>> validCoords;
        for (int i = 0; i < 4; i++) {
            int Y = y + Game::Utils::yCoords[i];
            int X = x + Game::Utils::xCoords[i];
            if (valid(X, Y))
                validCoords.emplace_back(X, Y);
        }
        
        std::shuffle(
            validCoords.begin(),
            validCoords.end(),
            Game::Utils::GetRandomGenerator()
        );
        
        for (const auto& coord : validCoords)
            stk.push(coord);
    }

    max_x ++, max_y ++; // moving to adjacent full cell
    min_x --, min_y --; // "

    const int new_height = max_y - min_y + 1;
    const int new_width  = max_x - min_x + 1;
    Entities::Map new_map(new_width, new_height);

    for (int y = 0; y < new_height; y++)
        for (int x = 0; x < new_width; x++)
            new_map.At(x, y) = map.At(x + min_x, y + min_y);

    map = new_map;
}

std::shared_ptr<MapNode> Game::ProceduralGeneration::GenerateRooms(const int totalRooms) {
    std::vector<std::shared_ptr<MapNode>> rooms;
    int roomsCreated = 0;
    while (roomsCreated < totalRooms) {
        if (!roomsCreated) {
            rooms.push_back(std::make_shared<MapNode>(CreateMapNode()));
            roomsCreated ++;
            continue;
        }

        int randomRoom  = Game::Utils::r32ir(0, int(rooms.size() - 1));
        auto targetRoom = rooms[randomRoom];
        
        NodeDir randomDir = MapNode::RandomNodeDirection();
        
        if (targetRoom->GetAdjacent(randomDir) != nullptr)
            continue;
            
        auto newRoom = std::make_shared<MapNode>(CreateMapNode());
        ConnectRooms(targetRoom, newRoom, randomDir);

        rooms.push_back(newRoom);
        roomsCreated ++;
    }
    // Pick a random room to be the root and prepare the room
    auto root = rooms[Game::Utils::r32ir(0, int(rooms.size() - 1))];
    Game::Entities::Map& rootMap = root->GetMap();

    // removing noise from initial room
    for (int y = 1; y < rootMap.Height() - 1; y++)
        for (int x = 1; x < rootMap.Width() - 1; x++)
            if (rootMap.At(x, y).Type() != Game::Entities::CellType::EMPTY)
                rootMap.At(x, y).SetType(Game::Entities::CellType::EMPTY);
            
    return root;
}

MapNode Game::ProceduralGeneration::CreateMapNode() {
    int height = Game::Utils::r32ir(Entities::Map::MAP_MIN_HEIGHT, Entities::Map::MAP_MAX_HEIGHT);
    int width  = Game::Utils::r32ir(height, Entities::Map::MAP_MAX_WIDTH);
    MapNode mapNode(Entities::Map(width, height));
    SetEmptyCells(mapNode.GetMap());
    PositionEnemies(mapNode);
    return mapNode;
}