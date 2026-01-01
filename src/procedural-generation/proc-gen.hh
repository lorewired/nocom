#pragma once

#include "../utils/rand.hh"

#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <tuple>

#include <algorithm>
#include <utility>
#include <memory>

// for debug
#include <iostream>

namespace ProceduralGeneration {
    inline int ID = 0;

    enum class CellType {
        EMPTY,
        WALL,
        CHEST
    };

    inline std::map<CellType, char> Glyph = {
        {CellType::EMPTY, '.'},
        {CellType::WALL, '#'},
        {CellType::CHEST, 'B'},
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
        const std::vector<Cell> &Data() const;
    };

    enum NodeDir {
        TOP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    class MapNode {
        Map map;
        int number;
        std::shared_ptr<MapNode> adjacents[4];

    public:
        MapNode(Map map);

        Map& GetMap();
        int Number() const;
        
        std::shared_ptr<MapNode> GetAdjacent(NodeDir dir);
        void SetAdjacent(NodeDir dir, std::shared_ptr<MapNode> node);
        
        static NodeDir RandomNodeDirection();
    };

    MapNode CreateMapNode();

    std::shared_ptr<MapNode> GenerateRooms(int total_rooms);
    void ConnectRooms(std::shared_ptr<MapNode> room1, std::shared_ptr<MapNode> room2, NodeDir dir);
    void SetEmptyCells(Map& map);
    
    // debug
    inline void DebugMap(std::shared_ptr<MapNode> root) {
        using namespace std;
        auto cur = root;
        char c = ' ';
        std::cout << root->GetMap().Width() << ' ' << root->GetMap().Height() << '\n';
        while (c != '0') {
            system("clear");
            for (int i = 0; i < cur->GetMap().Height(); i++) {
                for (int j = 0; j < cur->GetMap().Width(); j++)
                    std::cout << cur->GetMap().At(i, j).Rep();
                std::cout << '\n';
            }
            std::cout << "\n0 to stop\nroom: " << cur->Number() << "\navaiable: ";
            if (cur->GetAdjacent(TOP) != nullptr)
                std::cout << "W ";
            if (cur->GetAdjacent(RIGHT) != nullptr)
                std::cout << "R ";
            if (cur->GetAdjacent(DOWN) != nullptr)
                std::cout << "D ";
            if (cur->GetAdjacent(LEFT) != nullptr)
                std::cout << "L ";
            std::cout << "\n: "; char c; std::cin >> c; c ^= 0x20;
            if (c == 'W' && cur->GetAdjacent(TOP) != nullptr) cur = cur->GetAdjacent(TOP);
            if (c == 'R' && cur->GetAdjacent(RIGHT) != nullptr) cur = cur->GetAdjacent(RIGHT);
            if (c == 'D' && cur->GetAdjacent(DOWN) != nullptr) cur = cur->GetAdjacent(DOWN);
            if (c == 'L' && cur->GetAdjacent(LEFT) != nullptr) cur = cur->GetAdjacent(LEFT);
            std::cout << '\n';
        }
    }

    inline void DebugMap2(std::shared_ptr<MapNode> root) {
        using namespace std;
        int N = 100;
        vector<vector<bool>> vis(N / 2, vector<bool>(N));
        auto traverse = [&](auto &&traverse, int i, int j, shared_ptr<MapNode> cur) -> void {
            if (i < 0 || j < 0 || i == N / 2 || j == N || vis[i][j] || cur == nullptr)
                return;
            vis[i][j] = true;
            if (cur->GetAdjacent(TOP) != nullptr)
                traverse(traverse, i - 1, j, cur->GetAdjacent(TOP));
            if (cur->GetAdjacent(RIGHT) != nullptr)
                traverse(traverse, i, j + 1, cur->GetAdjacent(RIGHT));
            if (cur->GetAdjacent(DOWN) != nullptr)
                traverse(traverse, i + 1, j, cur->GetAdjacent(DOWN));
            if (cur->GetAdjacent(LEFT) != nullptr)
                traverse(traverse, i, j - 1, cur->GetAdjacent(LEFT));
        };
        traverse(traverse, N / 4, N >> 1, root);
        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N; j++)
                cout << (vis[i][j] ? 'O' : '.');
            cout << '\n';
        }
    }
}