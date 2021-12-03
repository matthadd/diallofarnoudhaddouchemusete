#include "MoveCommandHandler.h"
#include <iostream>

namespace engine{
    MoveCommandHandler::MoveCommandHandler(int newPositionX, int newPositionY){
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
    }

    MoveCommandHandler::~MoveCommandHandler(){}

    bool MoveCommandHandler::process(state::State& state){
        sf::Vector2i vec = sf::Vector2i(_newPositionX,_newPositionY);
        for(size_t i = 0; i<state._GImanagers.size(); i++){
            for(size_t j =0; j<state._GImanagers[i]->getGameInstances().size(); j++){
                if(state._GImanagers[i]->getGameInstances()[j]->getPosition() == vec){
                    if(state._GImanagers[i]->getGameInstances()[j]->getTypeID()>6)
                    {
                        return false;
                    }
                    else if(state._GImanagers[i]->getGameInstances()[j]->getTypeID()==2){
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
            }
        }
        return true;
    }
}