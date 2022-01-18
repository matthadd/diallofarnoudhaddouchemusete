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
        state->selectSource(std::vector<int> {_selectedPositionX, _selectedPositionY});    
        return true;       
    }

    state::GameInstance *SelectionCommand::getGameInstance()
    {
        return _gameInstanceSelected;
    }

}