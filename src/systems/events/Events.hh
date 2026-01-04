#pragma once

#include "src/procedural_generation/ProceduralGeneration.hh"
#include "src/systems/GameContext.hh"
#include "src/entities/Human.hh"

#include <memory>

typedef Game::Systems::GameContext GameContextType;

namespace Game::Systems::Events {

    enum class EventType {
        PlayerMove,
        RoomChange,
    };

    class EventContext {
    protected:
        EventType type;
        // future attributes
    public:
        EventContext() = default;
        EventContext(EventType _type) : type(_type) {}
        EventType Type() const { return type; }
    };

    class EventsHandler {

    public:
        EventsHandler() = default;

        void LoadEvents(GameContextType& gameContext, std::queue<Game::Systems::Events::EventContext>& eventsPoll);
    };

    void RunEventPlayerMove(EventContext& eventContext, GameContextType& gameContext, std::queue<Game::Systems::Events::EventContext>& eventsPoll);
    void RunEventRoomChange(EventContext& eventContext, GameContextType& gameContext);

}