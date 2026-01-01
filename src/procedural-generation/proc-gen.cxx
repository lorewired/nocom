#include "proc-gen.hxx"

using namespace ProceduralGeneration;

void ProceduralGeneration::ConnectRooms(
    std::shared_ptr<MapNode> src,
    std::shared_ptr<MapNode> dst,
    NodeDir dir
)
{
    // bidirectional connection
    switch (dir) {
        case TOP:
            src->SetAdjacent(TOP, dst);
            dst->SetAdjacent(DOWN, src);
            break;
        case RIGHT:
            src->SetAdjacent(RIGHT, dst);
            dst->SetAdjacent(LEFT, src);
            break;
        case DOWN:
            src->SetAdjacent(DOWN, dst);
            dst->SetAdjacent(TOP, src);
            break;
        case LEFT:
            src->SetAdjacent(LEFT, dst);
            dst->SetAdjacent(RIGHT, src);
    }
}

void ProceduralGeneration::SetEmptyCells(Map& map) {
    const int height = map.Height();
    const int width = map.Width();
    const int totalBorderCells = (height << 1) + (width << 1);
    const int totalEmptyArea   = height * width - totalBorderCells;
    const int xCoords[]        = { -1, 0, 1, 0 };
    const int yCoords[]        = { 0, 1, 0, -1 };

    auto valid = [&height, &width] (int i, int j) { return i > 0 && j > 0 && i < height - 1 && j < width - 1; };
    
    int randomPercent      = r32ir(60, 90);
    int requiredEmptyCells = totalEmptyArea * randomPercent / 100;
    int emptyCells         = 0;

    std::stack<std::pair<int, int>> stk;
    const int startX = r32ir(1, height - 2);
    const int startY = r32ir(1, width - 2);
    stk.emplace(startX, startY);

    int min_x, min_y;
    int max_x, max_y;

    min_x = max_x = startX;
    min_y = max_y = startY;
    
    while (stk.size()) {
        auto [i, j] = stk.top(); stk.pop();

        if (emptyCells == requiredEmptyCells)
            continue;

        min_x = std::min(min_x, i);
        max_x = std::max(max_x, i);
        min_y = std::min(min_y, j);
        max_y = std::max(max_y, j);

        if (map.At(i, j).Type() != CellType::EMPTY) {
            map.At(i, j).SetType(CellType::EMPTY);
            emptyCells ++;
        }

        std::vector<std::pair<int, int>> validCoords;
        for (int k = 0; k < 4; k++) {
            int I = i + xCoords[k];
            int J = j + yCoords[k];
            if (valid(I, J))
                validCoords.emplace_back(I, J);
        }
        
        std::shuffle(validCoords.begin(), validCoords.end(), GetRandomGenerator());
        
        for (const auto& coord : validCoords)
            stk.push(coord);
    }

    max_x ++, max_y ++; // moving to adjacent full cell
    min_x --, min_y --; // "

    const int new_height = max_x - min_x + 1;
    const int new_width  = max_y - min_y + 1;
    Map new_map(new_width, new_height);

    for (int i = 0; i < new_height; i++)
        for (int j = 0; j < new_width; j++)
            new_map.At(i, j) = map.At(i + min_x, j + min_y);

    map = new_map;
}

std::shared_ptr<MapNode> ProceduralGeneration::GenerateRooms(const int totalRooms) {
    std::vector<std::shared_ptr<MapNode>> rooms;
    int roomsCreated = 0;
    while (roomsCreated < totalRooms) {
        if (!roomsCreated) {
            rooms.push_back(std::make_shared<MapNode>(CreateMapNode()));
            roomsCreated ++;
            continue;
        }

        int randomRoom  = r32ir(0, int(rooms.size() - 1));
        auto targetRoom = rooms[randomRoom];
        
        NodeDir randomDir = MapNode::RandomNodeDirection();
        
        if (targetRoom->GetAdjacent(randomDir) != nullptr)
            continue;
            
        auto newRoom = std::make_shared<MapNode>(CreateMapNode());
        ConnectRooms(targetRoom, newRoom, randomDir);

        rooms.push_back(newRoom);
        roomsCreated ++;
    }
    // Pick a random room to be the root
    return rooms[r32ir(0, int(rooms.size() - 1))];
}

MapNode ProceduralGeneration::CreateMapNode() {
    int height = r32ir(Map::MAP_MIN_HEIGHT, Map::MAP_MAX_HEIGHT);
    int width  = r32ir(height, Map::MAP_MAX_WIDTH);
    Map newMap = Map(width, height);
    SetEmptyCells(newMap);
    return MapNode(newMap);
}