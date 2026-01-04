#include "Humanoid.hh"

using namespace Game::Entities;

Game::Entities::Humanoid::Humanoid(const std::string& _name)
: name(_name) {}

Game::Entities::Humanoid::Humanoid(const std::string& _name, int _damage)
: name(_name), damage(_damage) {}

std::string Game::Entities::Humanoid::Name() const { return name; }

int Game::Entities::Humanoid::Hp() const { return hp; }

int Game::Entities::Humanoid::Damage() const { return damage; }

void Game::Entities::Humanoid::SetName(const std::string& new_name) { name = new_name; }

void Game::Entities::Humanoid::SetHp(int value) { hp = value; }

void Game::Entities::Humanoid::SetDamage(int value) { damage = value; }

void Game::Entities::Humanoid::TakeDamage(int value) {
    if (hp - value < 0) {
        hp = 0;
        return;
    }
    hp -= value;
}

void Game::Entities::Humanoid::Heal(int value) {
    if (hp + value > HUMANOID_BASE_HP) {
        hp = Game::Entities::HUMANOID_BASE_HP;
        return;
    }
    hp += value;
}

Game::Utils::Vec2<int, int> Game::Entities::Humanoid::Coords() const { return coords; }

int Game::Entities::Humanoid::X() const { return coords.first; }

int Game::Entities::Humanoid::Y() const { return coords.second; }

void Game::Entities::Humanoid::SetCoords(const Game::Utils::Vec2<int, int>& new_coords)
{ coords = new_coords; }

void Game::Entities::Humanoid::SetCoords(int new_x, int new_y)
{ coords = Game::Utils::Vec2<int, int>(new_x, new_y); }

void Game::Entities::Humanoid::SetX(int new_x) { coords.first = new_x; }

void Game::Entities::Humanoid::SetY(int new_y) { coords.second = new_y; }