#include "MoveCommand.h"
#include <iostream>

namespace engine
{
    MoveCommand::MoveCommand(int newPositionX, int newPositionY)
    {
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _commandTypeID = (CommandTypeID)2;
    }

    MoveCommand::~MoveCommand() {}

    bool MoveCommand::process(state::State *state)
    {
        // Vérification de la règle
        bool res = true;
        
            if(!state->getGI(_newPositionX, _newPositionY))
            {
                state->getSource()->assignPosition(_newPositionX, _newPositionY);
            }
            else if(state->getGI(_newPositionX, _newPositionY)->getTypeID() > 6)
            {
                throw std::string("This cell is already occupied");
                res = false;
            }
            else
            {
                state->getSource()->assignPosition(_newPositionX, _newPositionY);
            }

        return res;
    }

    void MoveCommand::setGameInstance(state::GameInstance *ptr_GameInstance)
    {
        _gameInstanceSelected = ptr_GameInstance;
    }
}