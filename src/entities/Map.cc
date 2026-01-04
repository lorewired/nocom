#include "Map.hh"

using namespace Game::Entities;

#pragma region Cell_Area

char Cell::Rep() const { return rep; }
CellType Cell::Type() const { return type; }
void Cell::SetType(CellType _type) { type = _type; rep = Glyph[_type]; }

#pragma endregion

#pragma region Map_Area

Map::Map(int _width, int _height)
: width(_width), height(_height)
{
    grid.resize(width * height);
}

int Map::Width() const { return width; }
int Map::Height() const { return height; }

Cell& Map::At(int x, int y) { return grid[y * width + x]; }
Cell& Map::At(const Game::Utils::Vec2<int, int>& coords) { return grid[coords.second * width + coords.first]; }

const std::vector<Cell>& Map::Data() const { return grid; }

#pragma endregion