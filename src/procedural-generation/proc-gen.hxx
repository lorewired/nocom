#pragma once

#include "../utils/data-types.hxx"
#include "../utils/rand.hxx"

#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <utility>
#include <memory>

// for debug
#include <iostream>

namespace procedural_generation {
    static I32 ID = 0;

    enum class cell_type {
        EMPTY,
        CHEST
    };

    class cell {
        cell_type _type;
        char _rep;

    public:
        cell() : _type(cell_type::EMPTY), _rep(' ') {}
        cell(char __rep);
        cell_type type() const;
        void set_type(cell_type __type);
    };

    class map {
        std::vector<cell> _grid;
        UI32 _width;
        UI32 _height;

    public:
        static const UI32 MAP_MAX_WIDTH = 50;
        static const UI32 MAP_MAX_HEIGHT = 25;
        static const UI32 MAP_MIN_WIDTH = 20;
        static const UI32 MAP_MIN_HEIGHT = 12;

        UI32 width() const;
        UI32 height() const;

        map(const UI32 __width, const UI32 __height);

        const cell &at(UI32 x, UI32 y) const;

        const std::vector<cell> &data() const;
    };

    enum node_dir {
        TOP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };

    class map_node {
        map _map;
        I32 _number;
        std::shared_ptr<map_node> _adjacents[4];

    public:
        map_node(map __map);

        I32 number() const;
        const map &get_map() const;
        std::shared_ptr<map_node> get_adjacent(node_dir dir);
        void set_adjacent(node_dir dir, std::shared_ptr<map_node> node);
        static node_dir rdn_node_dir();
    };

    map_node create_map_node();

    std::shared_ptr<map_node> generate_rooms(UI32 __total_rooms);
    void connect_rooms(std::shared_ptr<map_node> room1, std::shared_ptr<map_node> room2, node_dir dir);
    void create_room_path(std::shared_ptr<map_node> room);

    void drunkards_walk_dfs();
    
    // debug
    inline void debug_map(std::shared_ptr<map_node> root) {
        using namespace std;
        auto cur = root;
        char c = ' ';
        while (c != '0') {
            system("cls");
            for (int i = 0; i < cur->get_map().height(); i++) {
                for (int j = 0; j < cur->get_map().width(); j++)
                    std::cout << '.';
                std::cout << '\n';
            }
            std::cout << "\n0 to stop\nroom: " << cur->number() << "\navaiable: ";
            if (cur->get_adjacent(TOP) != nullptr)
                std::cout << "W ";
            if (cur->get_adjacent(RIGHT) != nullptr)
                std::cout << "R ";
            if (cur->get_adjacent(DOWN) != nullptr)
                std::cout << "D ";
            if (cur->get_adjacent(LEFT) != nullptr)
                std::cout << "L ";
            std::cout << "\n: "; char c; std::cin >> c;
            if (c == 'W') cur = cur->get_adjacent(TOP);
            if (c == 'R') cur = cur->get_adjacent(RIGHT);
            if (c == 'D') cur = cur->get_adjacent(DOWN);
            if (c == 'L') cur = cur->get_adjacent(LEFT);
            std::cout << '\n';
        }
    }

    inline void debug_map2(std::shared_ptr<map_node> root) {
        using namespace std;
        I32 N = 100;
        vector<vector<bool>> vis(N / 2, vector<bool>(N));
        auto traverse = [&](auto &&traverse, I32 i, I32 j, shared_ptr<map_node> cur) -> void {
            if (i < 0 || j < 0 || i == N / 2 || j == N || vis[i][j] || cur == nullptr)
                return;
            vis[i][j] = true;
            if (cur->get_adjacent(TOP) != nullptr)
                traverse(traverse, i - 1, j, cur->get_adjacent(TOP));
            if (cur->get_adjacent(RIGHT) != nullptr)
                traverse(traverse, i, j + 1, cur->get_adjacent(RIGHT));
            if (cur->get_adjacent(DOWN) != nullptr)
                traverse(traverse, i + 1, j, cur->get_adjacent(DOWN));
            if (cur->get_adjacent(LEFT) != nullptr)
                traverse(traverse, i, j - 1, cur->get_adjacent(LEFT));
        };
        traverse(traverse, N / 4, N >> 1, root);
        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N; j++)
                cout << (vis[i][j] ? 'O' : '.');
            cout << '\n';
        }
    }
}