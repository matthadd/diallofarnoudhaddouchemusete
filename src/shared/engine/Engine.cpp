#include "Engine.h"
#include <queue>
#include "engine.h"
#include <iostream>
#include "Command.h"


namespace engine{
    Engine::Engine(state::State state){
        _currentState = state;
    }

    Engine::~Engine(){}

    void Engine::addCommand(Command* ptr_cmd){
        _commandQueue.push(ptr_cmd);
    }

    void Engine::processCommands(){
        for(size_t i = 0; i < _commandQueue.size(); i++){
            CommandTypeID type = _commandQueue.front()->getCommandTypeID();
            switch (type)
            {
            case 1://SelectionCommand
                if(_commandQueue.front()->process(_currentState)){
                    SelectionCommand* command = (SelectionCommand*)malloc(sizeof(*command));
                    command = (SelectionCommand*) _commandQueue.front();
                    _currentSelectedInstance = command->getGameInstance();
                    free(command);
                }
                _commandQueue.pop();
                break;
            case 2://MoveCommand
                MoveCommand* command = (MoveCommand*)malloc(sizeof(*command));
                command = (MoveCommand*) _commandQueue.front();
                command->setGameInstance(_currentSelectedInstance);
                if(command->process(_currentState)){
                    std::cout << "MoveCommand a réussi\n" << std::endl;
                }
                free(command);
                _commandQueue.pop();
                break;
            /*case 3:
                break;
            case 4:
                break;*/
            }
            _commandQueue.pop();
        }
    }

    state::State& Engine::getState(){
        return _currentState;
    }
}

