#pragma once

#include "src/utils/Vec2.hh"

#include <string>

namespace Game::Entities {

    constexpr unsigned HUMANOID_BASE_HP = 100;
    constexpr unsigned HUMAN_BASE_DAMAGE = 25;
    constexpr unsigned ENEMY_BASE_DAMAGE = 5;

    class Humanoid {
    protected:
        std::string name;

        int hp = HUMANOID_BASE_HP;
        int damage = 0;
        
        Game::Utils::Vec2<int, int> coords;

    public:
        Humanoid() = default;
        ~Humanoid() = default;

        Humanoid(const std::string& _name);
        Humanoid(const std::string& _name, int _damage);

        std::string Name() const;
        int Hp() const;
        int Damage() const;

        void SetName(const std::string& new_name);
        void SetHp(int value);
        void SetDamage(int value);

        void TakeDamage(int value);
        void Heal(int value);
        
        Game::Utils::Vec2<int, int> Coords() const;
        
        void SetCoords(const Game::Utils::Vec2<int, int>& new_coords);
        void SetCoords(int new_x, int new_y);
        
        int X() const;
        int Y() const;

        void SetX(int new_x);
        void SetY(int new_y);
    };

}