#include "Engine.h"
#include <queue>
#include "engine.h"
#include <iostream>
#include "Command.h"
#include <memory>

namespace engine{
    Engine::Engine(state::State state){
        _currentState = state;
    }

    Engine::~Engine(){}

    void Engine::addCommand(std::shared_ptr<Command> ptr_cmd){
        _commandQueue.push(ptr_cmd);
    }

    void Engine::processCommands(){
        // On copie les commandes dans un buffer
        std::unique_ptr<std::queue< std::shared_ptr<Command>> > commands_buffer;
        commands_buffer.reset(new std::queue<std::shared_ptr<Command>>(_commandQueue));
        // On clear la fifo de commandes
        std::cout << "taille de la queue avant le front : " << _commandQueue.size() << "\n" << std::endl;
        std::queue<std::shared_ptr<Command>> empty;
        std::swap(_commandQueue, empty);
        std::cout << "taille de la queue après le swap : " << _commandQueue.size() << "\n" << std::endl;
        std::cout << "La taille du buffer : " << commands_buffer->size() << "\n" <<  std::endl;
        size_t buff_size = commands_buffer->size();
        for(size_t i = 0; i < buff_size; i++){
            CommandTypeID type = commands_buffer->front()->getCommandTypeID();
            std::cout << type << std::endl;
            switch (type)
            {

            case 1://SelectionCommand
            {
                std::cout << "Vous avez activez une commande de sélection\n" << std::endl;
                if(commands_buffer->front()->process(_currentState)){
                    SelectionCommand* command = (SelectionCommand*) commands_buffer->front().get();
                    _currentSelectedInstance = command->getGameInstance();
                    std::cout << "la commande de sélection a été exécutée\n" << std::endl;
                }    
                commands_buffer->pop();
                break;
            }

            case 2://MoveCommand
            {
                std::cout << "Vous avez activez une commande move\n" << std::endl;
                std::shared_ptr<MoveCommand> moveCommand = std::dynamic_pointer_cast<MoveCommand>(commands_buffer->front());
                moveCommand->setGameInstance(_currentSelectedInstance);
                if(moveCommand->process(_currentState)){
                    std::cout << "La commande de déplacement a été exécutée\n" << std::endl;
                }
                else{
                    std::cout << "La commande de déplacement n'a pas été exécutée." << std::endl;
                }
                commands_buffer->pop();
                break;
            }

            case 4://BuildUnitCommand
            {
                std::shared_ptr<BuildUnitCommand> buildUnitCommand = std::dynamic_pointer_cast<BuildUnitCommand>(commands_buffer->front());
                if(buildUnitCommand->process(_currentState)){
                    std::cout << "La commande de création d'unité a été exécutée\n" << std::endl;
                }
                else{
                    std::cout << "La commande de création d'unité n'a pas été exécutée." << std::endl;
                }
                commands_buffer->pop();
                break;
            }
            
            }
            std::cout << "La taille du buffer : " << commands_buffer->size() << "\n" <<  std::endl;

        }

    }


    state::State& Engine::getState(){
        return _currentState;
    }
}

