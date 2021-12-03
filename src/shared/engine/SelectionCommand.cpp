#include "SelectionCommand.h"

namespace engine{

    SelectionCommand::SelectionCommand(int x, int y){
        _selectedPositionX = x;
        _selectedPositionY = y;
        _commandTypeID = (CommandTypeID) 1;

    }

    SelectionCommand::~SelectionCommand(){}

    bool SelectionCommand::process(state::State& state){

        SelectionCommandHandler* handler = new SelectionCommandHandler(_selectedPositionX, _selectedPositionY);
        
        //verification
        if(handler->process(state)){
            //process principal
        }
    }

    state::GameInstance* SelectionCommand::getGameInstance (){
        return _gameInstanceSelected;
    }
    
}