#include "Engine.h"
#include <deque>
#include "engine.h"
#include <iostream>
#include "Command.h"
#include <memory>

namespace engine
{
    Engine::Engine(state::State *state_ptr)
    {
        _currentState = state_ptr;
    }

    Engine::~Engine() {}

    void Engine::addCommand(std::shared_ptr<Command> ptr_incomingCmd)
    {
        _commandQueue.push(ptr_incomingCmd);
    }

    void Engine::processCommands()
    {
        while (_commandQueue.size() != 0)
        {
            try
            {
                _commandQueue.front()->process(_currentState);
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << '\n';
                _commandQueue.pop();
                continue;
            }
            _commandQueue.pop();    
        }
    }

    state::State *Engine::getState()
    {
        return _currentState;
    }
}
