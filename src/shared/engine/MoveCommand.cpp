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
        _gameInstanceSelected = state->getSource();
        state::GameInstance* target = state->getGI(_newPositionX, _newPositionY);
        if(target == NULL)
        {
            _gameInstanceSelected->assignPosition(_newPositionX, _newPositionY);
        }
        else if(target->getTypeID() > 6)
        {
            throw std::runtime_error("This cell is already occupied");
            res = false;
        }
        else
        {
            _gameInstanceSelected->assignPosition(_newPositionX, _newPositionY);
        }

        return res;
    }

    void MoveCommand::setGameInstance(state::GameInstance *ptr_GameInstance)
    {
        _gameInstanceSelected = ptr_GameInstance;
    }
}