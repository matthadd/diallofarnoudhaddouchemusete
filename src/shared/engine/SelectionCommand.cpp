#include "SelectionCommand.h"
#include <iostream>

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
        if(handler->process(state))
        {
            //process principal

            return true;
        }
        else 
        {
            std::cout << "La commande n'a pas été exécutée\n" << std::endl;
            return false;
        }


    }

    state::GameInstance* SelectionCommand::getGameInstance (){
        return _gameInstanceSelected;
    }
    
}