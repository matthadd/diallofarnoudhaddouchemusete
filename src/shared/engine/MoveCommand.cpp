#include "MoveCommand.h"
#include <iostream>
namespace engine{
    MoveCommand::MoveCommand(int newPositionX, int newPositionY){
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _commandTypeID = (CommandTypeID) 2;
    }

    MoveCommand::~MoveCommand(){}

    bool MoveCommand::process(state::State& state){
        MoveCommandHandler* handler = new MoveCommandHandler(_newPositionX, _newPositionY);
        if(handler->process(state))
        {
            _gameInstanceSelected->setPosition(sf::Vector2i(_newPositionX, _newPositionY));
            for(size_t i = 0; i<state._GImanagers.size(); i++)
            {
                for(size_t j =0; j<state._GImanagers[i]->getGameInstances().size(); j++)
                {
                    if(state._GImanagers[i]->getGameInstances()[j]->getPosition() == _gameInstanceSelected->getPosition()
                    && state._GImanagers[i]->getGameInstances()[j]->getId() == _gameInstanceSelected->getId())
                    {
                        state._GImanagers[i]->getGameInstances()[j]->setPosition(_newPositionX,_newPositionY);
                    }
                }
            }
            std::cout << "L'unité se trouve maintenant sur la case de coordonnées : (" << _newPositionX << "," << _newPositionY << ")\n" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Vous ne pouvez pas déplacer l'unité à la case de coordonnées : (" << _newPositionX << "," << _newPositionY << ")\n" << std::endl;
            return false;
        }
    }

    void MoveCommand::setGameInstance(state::GameInstance* ptr_GameInstance){
        _gameInstanceSelected = ptr_GameInstance;
    }
}