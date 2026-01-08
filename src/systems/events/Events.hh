#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/entities/Human.hh"

#include <memory>

// promisse :o
namespace Game::Systems {
    class GameContext; 
}

using GameContextType = Game::Systems::GameContext;

namespace Game::Systems::Events {

    class IEvent {
    public:
        virtual ~IEvent() = default;
        virtual void Execute(GameContextType& gameCtx) = 0;
    };

    enum class EventType {
        PlayerMove,
        RoomChange,
    };

    class EventsHandler {

    public:
        EventsHandler() = default;

        void LoadEvents(GameContextType& gameContext);
    };

    // all events
    class EventPlayerDeath : public IEvent {
    public:
        EventPlayerDeath() = default;
        void Execute(GameContextType& gameCtx) override;
    };

    class EventPlayerMove : public IEvent {
        int targetX;
        int targetY;
    public:
        EventPlayerMove(int x, int y) : targetX(x), targetY(y) {}
        EventPlayerMove(Game::Utils::Vec2<int, int> coords) : targetX(coords.first), targetY(coords.second) {}
        void Execute(GameContextType& gameCtx) override;
    };
    
    class EventRoomChange : public IEvent {
        
    public:
        void Execute(GameContextType& gameCtx) override;
    };
    
    class EventEnemyMove : public IEvent {
        std::shared_ptr<Game::Entities::Enemy> enemy;
        int targetX;
        int targetY;
    public:
        EventEnemyMove(std::shared_ptr<Game::Entities::Enemy> _enemy, int x, int y) : enemy(_enemy), targetX(x), targetY(y) {}
        EventEnemyMove(std::shared_ptr<Game::Entities::Enemy> _enemy, Game::Utils::Vec2<int, int> coords) : enemy(_enemy), targetX(coords.first), targetY(coords.second) {}
        void Execute(GameContextType& gameCtx) override;
    };

}