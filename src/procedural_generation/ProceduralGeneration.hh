#pragma once

#include "src/entities/Map.hh"
#include "src/entities/Enemy.hh"
#include "src/utils/Rand.hh"

#include <vector>
#include <stack>

#include <algorithm>
#include <utility>
#include <memory>

// for debug
#include <iostream>

namespace Game::ProceduralGeneration {
    inline int ID = 0;

    enum NodeDir {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    class MapNode {
        Game::Entities::Map map;
        std::shared_ptr<MapNode> adjacents[4];
        std::vector<std::shared_ptr<Game::Entities::Enemy>> enemies;
        int number;

    public:
        MapNode(Game::Entities::Map map);

        int Number() const;
        std::vector<std::shared_ptr<Game::Entities::Enemy>>& Enemies();
        Game::Entities::Map& GetMap();
        std::shared_ptr<MapNode> GetAdjacent(NodeDir dir);
        Game::Utils::Vec2<std::shared_ptr<MapNode>, Game::Utils::Vec2<int, int>> GetNextRoom(
            Game::Utils::Vec2<int, int> coords
        );

        void SetAdjacent(NodeDir dir, std::shared_ptr<MapNode> other);
        void SetEntrances(NodeDir dir, std::shared_ptr<MapNode> other);
        
        static NodeDir RandomNodeDirection();
    };

    MapNode CreateMapNode();

    std::shared_ptr<MapNode> GenerateRooms(int total_rooms);
    void ConnectRooms(std::shared_ptr<MapNode> room1, std::shared_ptr<MapNode> room2, NodeDir dir);
    void SetEmptyCells(Game::Entities::Map& map);
    void PositionEnemies(MapNode& mapNode);
    
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
            if (cur->GetAdjacent(UP) != nullptr)
                std::cout << "W ";
            if (cur->GetAdjacent(RIGHT) != nullptr)
                std::cout << "R ";
            if (cur->GetAdjacent(DOWN) != nullptr)
                std::cout << "D ";
            if (cur->GetAdjacent(LEFT) != nullptr)
                std::cout << "L ";
            std::cout << "\n: "; char c; std::cin >> c; c ^= 0x20;
            if (c == 'W' && cur->GetAdjacent(UP) != nullptr) cur = cur->GetAdjacent(UP);
            if (c == 'R' && cur->GetAdjacent(RIGHT) != nullptr) cur = cur->GetAdjacent(RIGHT);
            if (c == 'D' && cur->GetAdjacent(DOWN) != nullptr) cur = cur->GetAdjacent(DOWN);
            if (c == 'L' && cur->GetAdjacent(LEFT) != nullptr) cur = cur->GetAdjacent(LEFT);
            std::cout << '\n';
        }
    }

}