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
        UI32 _x;
        UI32 _y;
    public:
        cell(const char __rep, const UI32 __x, const UI32 __y);
        
        cell_type type() const;
        void set_type(const cell_type __type);

        UI32 x() const;
        void set_x(const UI32 __x);

        UI32 y() const;
        void set_y(const UI32 __y);
    };
    
    class map {
        std::vector<std::vector<cell>> _matrix;
        UI32 _width;
        UI32 _height;
    public:
        map(const UI32 __width, const UI32 __height);
        std::vector<std::vector<cell>> matrix() const;
    };
    
    class map_node {
        map_node * adjacents = { nullptr };
    public:
        map_node * get_top();
    };
}