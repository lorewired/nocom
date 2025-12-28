#include "proc-gen.hxx"

using namespace proc_gen;

#pragma region Cell_Area

cell::cell(const char __rep, const UI32 __x, const UI32 __y)
: _x(__x), _y(__y)
{
    switch (__rep) {
        case '.': _type = cell_type::EMPTY; break;
        case 'B': _type = cell_type::CHEST; break;
    }
}

cell_type cell::type() const { return _type; }
void cell::set_type(const cell_type __type) { _type = __type; }

UI32 cell::x() const { return _x; }
void cell::set_x(const UI32 __x) { _x = __x; }

UI32 cell::y() const { return _y; }
void cell::set_y(const UI32 __y) { _y = __y; }

#pragma endregion

#pragma region Map_Area

map::map(const UI32 __width, const UI32 __height)
: _width(__width), _height(__height)
{
    _matrix.assign(_width, std::vector<cell>(_height));
}

std::vector<std::vector<cell>> map::matrix() const { return _matrix; }

#pragma endregion