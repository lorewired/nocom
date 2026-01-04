#pragma once

#include <cmath>

namespace Game::Utils {

    template<typename T, typename Z> struct Vec2 {
    public:
        T first;
        Z second;

        Vec2() = default;
        Vec2(const T& _first, const Z& _second): first(_first), second(_second) {}
        
        Vec2& operator=(const Vec2& other) {
            if (this == &other) return *this;
            first = other.first;
            second = other.second;
            return *this;
        }
        
        bool operator==(const Vec2& other) const { return this == &other; }
        
        bool operator!=(const Vec2& other) const { return ! (*this == other); }
    };

}