#pragma once

#include "src/utils/vec2.hh"

#include <string>

namespace Game::Entities {

    constexpr unsigned HUMANOID_BASE_HP = 100;
    constexpr unsigned HUMAN_BASE_DAMAGE = 25;
    constexpr unsigned ENEMY_BASE_DAMAGE = 5;

    class Humanoid {
        std::string name;

        int hp = HUMANOID_BASE_HP;
        int damage = 0;
        
        Game::Utils::Vec2 coords;
        
    public:
        Humanoid(const std::string& _name);
        Humanoid(const std::string& _name, const int& _damage);

        std::string Name() const;
        int Hp() const;
        int Damage() const;

        void SetName(const std::string& new_name);
        void SetHp(const int& value);
        void SetDamage(const int& value);

        void TakeDamage(const int& value);
        void Heal(const int& value);
        
        Game::Utils::Vec2 Coords() const;
        
        void SetCoords(const Game::Utils::Vec2& new_coords);
        
        int X() const;
        int Y() const;

        void SetX(const int& new_x);
        void SetY(const int& new_y);
    };

}