#include "map.hh"

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

Cell& Map::At(int x, int y) { return grid[x * width + y]; }

const std::vector<Cell>& Map::Data() const { return grid; }

#pragma endregion