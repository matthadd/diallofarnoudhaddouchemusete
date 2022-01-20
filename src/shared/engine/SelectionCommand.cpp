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

    bool SelectionCommand::process(state::State *state)
    {
        // state->selectSource(std::vector<int>{_selectedPositionX, _selectedPositionY});
        int idPlayer = -1;
        if (state->getGI(_selectedPositionX, _selectedPositionY))
        // if there is GI in these positions
        {
            idPlayer = state->getGI(_selectedPositionX, _selectedPositionY)->getPlayerID();
        }
        if (idPlayer == state->activePlayer->getID())
        // if GI is owned by player
        {
            state->selectSource(std::vector<int>{_selectedPositionX, _selectedPositionY});
            return true;
        }
        if (idPlayer == -1)
        // if there is no GI in these positions
        {
            state->selectObjective(std::vector<int>{_selectedPositionX, _selectedPositionY});
            return true;
        }
        if (idPlayer == state->activePlayer->getID())
        // if there is a GI but it is not owned by the player
        {
            state->selectObjective(std::vector<int>{_selectedPositionX, _selectedPositionY});
            return true;
        }

        return false;
    }

    state::GameInstance *SelectionCommand::getGameInstance()
    {
        return _gameInstanceSelected;
    }

}