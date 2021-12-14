#include "Engine.h"
#include <queue>
#include "engine.h"
#include <iostream>
#include "Command.h"
#include <memory>

namespace engine
{
    Engine::Engine(state::State state)
    {
        _currentState = state;
    }

    Engine::~Engine() {}

    void Engine::addCommand(std::shared_ptr<Command> ptr_cmd)
    {
        _commandQueue.push(ptr_cmd);
    }

    void Engine::processCommands()
    {
        while (_commandQueue.size() != 0)
        {
            _commandQueue.front()->process(_currentState);
            _commandQueue.pop();
        }
    }

    state::State &Engine::getState()
    {
        return _currentState;
    }
}
