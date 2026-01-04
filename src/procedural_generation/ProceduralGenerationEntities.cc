#include "ProceduralGeneration.hh"

using namespace Game::ProceduralGeneration;

#pragma region Map_Node_Area

Game::Utils::Vec2<MapNode, Game::Utils::Vec2<int, int>> Game::ProceduralGeneration::MapNode::GetNextRoom(Game::Utils::Vec2<int, int> coords)
{
    using namespace Game::Entities;
    using namespace Game::Utils;

    NodeDir dir =
        coords.first    == map.Width() - 1 ? NodeDir::RIGHT
        : coords.first  == 0                         ? NodeDir::LEFT
        : coords.second == 0                         ? NodeDir::UP
        :                                              NodeDir::DOWN;

    auto nextRoom = GetAdjacent(dir);
    auto& nextRoomMap = nextRoom->GetMap();

    auto findDoor = [&] (bool verticalSearch, int fixedIndex) -> Vec2<int, int> {
        int limit = verticalSearch ? nextRoomMap.Height() : nextRoomMap.Width();

        for (int i = 0; i < limit; i++) {
            Vec2<int, int> coord = verticalSearch ? Vec2<int, int>(fixedIndex, i) : Vec2<int, int>(i, fixedIndex);
            auto& cell = nextRoomMap.At(coord);
            if (cell.Type() == Game::Entities::CellType::DOOR)
                return coord;
        }

        return { -1, -1 };
    };

    Vec2<int, int> doorCoords;

    switch (dir) {
        case NodeDir::RIGHT:
            doorCoords = findDoor(true, 0); 
            break;
        case NodeDir::LEFT:
            doorCoords = findDoor(true, nextRoomMap.Width() - 1); 
            break;
        case NodeDir::UP:  
            doorCoords = findDoor(false, 0); 
            break;
        case NodeDir::DOWN:
            doorCoords = findDoor(false, nextRoomMap.Height() - 1); 
    }
    
    return Vec2<MapNode, Vec2<int, int>>(*nextRoom, doorCoords);
}

MapNode::MapNode(Entities::Map _map) : map(_map), number(++ID) {}

Game::Entities::Map& MapNode::GetMap() { return map; }

int MapNode::Number() const { return number; }

bool ValidDirection(NodeDir dir) { return dir >= 0 && dir <= 3; }

void MapNode::SetEntrances(NodeDir dir, std::shared_ptr<MapNode> other) {
if (other == nullptr) return;

    std::vector<std::pair<int, int>> cellsCoords;
    
    switch (dir) {
        case NodeDir::UP:
            for (int x = 1; x < map.Width() - 1; x++)
                if (map.At(x, 1).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(x, 0);
            break;
        case NodeDir::RIGHT:
            for (int y = 1; y < map.Height() - 1; y++)
                if (map.At(map.Width() - 2, y).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(map.Width() - 1, y);
            break;
        case NodeDir::DOWN:
            for (int x = 1; x < map.Width() - 1; x++)
               if (map.At(x, map.Height() - 2).Type() == Game::Entities::CellType::EMPTY)
                   cellsCoords.emplace_back(x, map.Height() - 1);
            break;
        case NodeDir::LEFT:
            for (int y = 1; y < map.Height() - 1; y++)
                if (map.At(1, y).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(0, y);
    }

    auto [randomX, randomY] = cellsCoords[Game::Utils::r32ir(0, cellsCoords.size() - 1)];
    map.At(randomX, randomY).SetType(Game::Entities::CellType::DOOR);
}

void MapNode::SetAdjacent(NodeDir dir, std::shared_ptr<MapNode> other) {
    if (!ValidDirection(dir)) return;
    adjacents[dir] = other;
    MapNode::SetEntrances(dir, other);
}

std::shared_ptr<MapNode> MapNode::GetAdjacent(NodeDir dir) {
    return ValidDirection(dir) ? adjacents[dir] : nullptr;
}

NodeDir MapNode::RandomNodeDirection() {
    int randomDir = Game::Utils::r32ir(0, 3);
    switch (randomDir) {
        case 0: return UP;
        case 1: return RIGHT;
        case 2: return DOWN;
        case 3: return LEFT;
    }
}

#pragma endregion