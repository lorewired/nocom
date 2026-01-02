#include "proc-gen.hh"

using namespace ProceduralGeneration;

#pragma region Cell_Area

char Cell::Rep() const { return rep; }
CellType Cell::Type() const { return type; }
void Cell::SetType(CellType _type) { type = _type; rep = Glyph[_type]; }

#pragma endregion

#pragma region Map_Node_Area

MapNode::MapNode(Map _map) : map(_map), number(++ID) {}

Map& MapNode::GetMap() { return map; }

int MapNode::Number() const { return number; }

bool ValidDirection(NodeDir dir) { return dir >= 0 && dir <= 3; }

void MapNode::SetEntrances(NodeDir dir, std::shared_ptr<MapNode> other) {
    if (other == nullptr) return;

    std::vector<std::pair<int, int>> cellsCoords;
    
    switch (dir) {
        case NodeDir::TOP:
            for (int i = 1; i < map.Width() - 1; i++)
                if (map.At(1, i).Type() == CellType::EMPTY)
                    cellsCoords.emplace_back(0, i);
            break;
        case NodeDir::RIGHT:
            for (int i = 1; i < map.Height() - 1; i++)
                if (map.At(i, map.Width() - 2).Type() == CellType::EMPTY)
                    cellsCoords.emplace_back(i, map.Width() - 1);
            break;
        case NodeDir::DOWN:
            for (int i = 1; i < map.Width() - 1; i++)
               if (map.At(map.Height() - 2, i).Type() == CellType::EMPTY)
                   cellsCoords.emplace_back(map.Height() - 1, i);
            break;
        case NodeDir::LEFT:
            for (int i = 1; i < map.Height() - 1; i++)
                if (map.At(i, 1).Type() == CellType::EMPTY)
                    cellsCoords.emplace_back(i, 0);
    }

    auto [randomX, randomY] = cellsCoords[r32ir(0, cellsCoords.size() - 1)];
    map.At(randomX, randomY).SetType(CellType::DOOR);
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
    int randomDir = r32ir(0, 3);
    switch (randomDir) {
        case 0: return TOP;
        case 1: return RIGHT;
        case 2: return DOWN;
        case 3: return LEFT;
    }
}

#pragma endregion

#pragma region Map_Area

Map::Map(int _width, int _height)
: width(_width), height(_height)
{
    grid.resize(width * height);
}

int Map::Width() const { return width; }
int Map::Height() const { return height; }

Cell& Map::At(int x, int y) { return grid[x * width + y]; }

const std::vector<Cell>& Map::Data() const { return grid; }

#pragma endregion