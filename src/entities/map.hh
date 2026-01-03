#pragma once

#include "src/utils/vec2.hh"

#include <vector>
#include <map>

namespace Game::Entities {

    enum class CellType {
        EMPTY,
        WALL,
        DOOR,
    };
    
    inline std::map<CellType, char> Glyph = {
        { CellType::EMPTY, '.' },
        { CellType::WALL,  '#' },
        { CellType::DOOR,  '$' },
    };
    
    class Cell {
        CellType type;
        char rep;
    
    public:
        Cell() : type(CellType::WALL), rep(Glyph[CellType::WALL]) {}
        Cell& operator= (const Cell& other) {
            if (this == &other) return *this;
            type = other.Type();
            rep  = other.Rep();
            return *this;
        }
        char Rep() const;
        CellType Type() const;
        void SetType(CellType type);
    };
    
    class Map {
        std::vector<Cell> grid;
        int width;
        int height;
    
    public:
        static const int MAP_MAX_WIDTH = 50;
        static const int MAP_MAX_HEIGHT = 20;
        static const int MAP_MIN_WIDTH = 35;
        static const int MAP_MIN_HEIGHT = 15;
    
        Map(const int width, const int height);
    
        Map& operator= (const Map& other) {
            if (this == &other) return *this;
            width  = other.Width();
            height = other.Height();
            grid   = other.Data();
            return *this;
        }
    
        int Width() const;
        int Height() const;
    
        Cell &At(int x, int y);
        Cell &At(const Game::Utils::Vec2& coords);
        const std::vector<Cell> &Data() const;
    };
    
}