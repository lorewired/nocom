#pragma once

#include "utils/data-types.hxx"

#include <vector>

namespace proc_gen {
    enum class cell_type {
        EMPTY,
        CHEST
    };
    
    class cell {
        cell_type _type;
        char _rep;
    public:
        cell(const char __rep);
        cell_type type() const;
        void set_type(const cell_type __type);
    };
    
    class map {
        std::vector<std::vector<cell>> _matrix;
        UI32 _width;
        UI32 _height;
    public:
        static const UI32 MAP_MAX_WIDTH = 50;
        static const UI32 MAP_MAX_HEIGHT = 50;
        static const UI32 MAP_MIN_WIDTH = 15;
        static const UI32 MAP_MIN_HEIGHT = 15;

        map(const UI32 __width, const UI32 __height);
        std::vector<std::vector<cell>> matrix() const;
    };
    
    class map_node {
        map _map;
        map_node * _adjacents[4];
    public:
        map_node(const map __map);
        map_node ** adjacents();
        map_node * get_top();
        map_node * get_right();
        map_node * get_down();
        map_node * get_left();
    };

    void generate_rooms(const UI32 total_rooms) {
        for (int i = 0; i < total_rooms; i++) {

        }
    }

    void new_adjacent(map_node * node);
}