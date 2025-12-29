#include "proc-gen.hxx"

using namespace proc_gen;

#pragma region Cell_Area

cell::cell(const char __rep)
{
    switch (__rep) {
        case '.': _type = cell_type::EMPTY; break;
        case 'B': _type = cell_type::CHEST; break;
    }
}

cell_type cell::type() const { return _type; }
void cell::set_type(const cell_type __type) { _type = __type; }

#pragma endregion

#pragma region Map_Node_Area
map_node::map_node(const map __map) : _map(__map) {}
map_node ** map_node::adjacents() { return _adjacents; }
map_node * map_node::get_top() { return _adjacents[0]; }
map_node * map_node::get_right() { return _adjacents[1]; }
map_node * map_node::get_down() { return _adjacents[2]; }
map_node * map_node::get_left() { return _adjacents[3]; }
#pragma endregion

#pragma region Map_Area

map::map(const UI32 __width, const UI32 __height)
: _width(__width), _height(__height)
{
    _matrix.assign(_width, std::vector<cell>(_height));
}

std::vector<std::vector<cell>> map::matrix() const { return _matrix; }

#pragma endregion