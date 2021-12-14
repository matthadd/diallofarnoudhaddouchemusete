#include "MoveCommand.h"
#include <iostream>

namespace engine
{
    MoveCommand::MoveCommand(int newPositionX, int newPositionY, int unitID)
    {
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _unitID = unitID;
        _commandTypeID = (CommandTypeID)2;
    }

    MoveCommand::~MoveCommand() {}

    bool MoveCommand::process(state::State &state)
    {

        // Vérification de la règle
        bool res = true;
        sf::Vector2i vec = sf::Vector2i(_newPositionX, _newPositionY);
        state::GameInstance *unit;

        for (auto gim : state._GImanagers)
        {
            for (auto gm : gim->getGameInstances())
            {
                if (gm->getID() == _unitID)
                {
                    unit = gm;
                }
                if (gm->getPosition() == vec)
                {
                    if (gm->getTypeID() > 6)
                    {
                        res = false;
                    }
                    if (gm->getTypeID() == 2)
                    {
                        res = false;
                    }
                }
            }
        }

        // Modification du state
        if (res)
        {
            unit->setPosition(vec);
            std::cout << "L'unité se trouve maintenant sur la case de coordonnées : (" << _newPositionX << "," << _newPositionY << ")\n"
                      << std::endl;
            return true;
        }
        else
        {
            std::cout << "Vous ne pouvez pas déplacer l'unité à la case de coordonnées : (" << _newPositionX << "," << _newPositionY << ")\n"
                      << std::endl;
            return false;
        }
    }

    void MoveCommand::setGameInstance(state::GameInstance *ptr_GameInstance)
    {
        _gameInstanceSelected = ptr_GameInstance;
    }
}