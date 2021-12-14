#include "SelectionCommand.h"
#include <iostream>

namespace engine
{

    SelectionCommand::SelectionCommand(int x, int y)
    {
        _selectedPositionX = x;
        _selectedPositionY = y;
        _commandTypeID = (CommandTypeID)1;
    }

    SelectionCommand::~SelectionCommand() {}

    bool SelectionCommand::process(state::State &state)
    {

        // verification
        bool res = false;

        for (auto gim : state._GImanagers)
        {
            for (auto gi : gim->getGameInstances())
            {
                if (gi->getPosition() == sf::Vector2i(_selectedPositionX, _selectedPositionY))
                {
                    res = true;
                    gi->select();
                    _gameInstanceSelected = gi;
                }
            }
        }
        if (res)
        {
            // Traitement à faire sur l'affichage
            return true;
        }
        else
        {
            std::cout << "La commande n'a pas été exécutée\n"
                      << std::endl;
            return false;
        }
    }

    state::GameInstance *SelectionCommand::getGameInstance()
    {
        return _gameInstanceSelected;
    }

}