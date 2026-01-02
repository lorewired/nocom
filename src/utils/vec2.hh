#pragma once

#include <cmath>

namespace Game::Utils {

    struct Vec2 {
    public:
        int x = 0;
        int y = 0;

        Vec2() = default;
        Vec2(const int _x, const int _y): x(_x), y(_y) {}
        
        Vec2& operator=(const Vec2& other) {
            if (this == &other) return *this;
            x = other.x;
            y = other.y;
            return *this;
        }
        
        bool operator==(const Vec2& other) { return x == other.x && y == other.y; }
        
        bool operator!=(const Vec2& other) { return ! (*this == other); }

        float Magnitude() const { return std::sqrt(x * x + y * y); }

        // vectorial operations

        Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
        
        Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
        
        Vec2 operator*(const Vec2& other) const { return Vec2(x * other.x, y * other.y); }
        
        Vec2 operator/(const Vec2& other) const { return Vec2(x / other.x, y / other.y); }

        // by scalar

        Vec2 operator*(const int& value) const { return Vec2(x * value, y * value); }
        
        Vec2 operator/(const int& value) const { return Vec2(x / value, y / value); }
    };

}