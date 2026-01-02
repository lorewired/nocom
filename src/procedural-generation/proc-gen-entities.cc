#include "proc-gen.hh"

using namespace Game::ProceduralGeneration;

#pragma region Map_Node_Area

MapNode::MapNode(Entities::Map _map) : map(_map), number(++ID) {}

Game::Entities::Map& MapNode::GetMap() { return map; }

int MapNode::Number() const { return number; }

bool ValidDirection(NodeDir dir) { return dir >= 0 && dir <= 3; }

void MapNode::SetEntrances(NodeDir dir, std::shared_ptr<MapNode> other) {
if (other == nullptr) return;

    std::vector<std::pair<int, int>> cellsCoords;
    
    switch (dir) {
        case NodeDir::TOP:
            for (int i = 1; i < map.Width() - 1; i++)
                if (map.At(1, i).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(0, i);
            break;
        case NodeDir::RIGHT:
            for (int i = 1; i < map.Height() - 1; i++)
                if (map.At(i, map.Width() - 2).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(i, map.Width() - 1);
            break;
        case NodeDir::DOWN:
            for (int i = 1; i < map.Width() - 1; i++)
               if (map.At(map.Height() - 2, i).Type() == Game::Entities::CellType::EMPTY)
                   cellsCoords.emplace_back(map.Height() - 1, i);
            break;
        case NodeDir::LEFT:
            for (int i = 1; i < map.Height() - 1; i++)
                if (map.At(i, 1).Type() == Game::Entities::CellType::EMPTY)
                    cellsCoords.emplace_back(i, 0);
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
        case 0: return TOP;
        case 1: return RIGHT;
        case 2: return DOWN;
        case 3: return LEFT;
    }
}

#pragma endregion