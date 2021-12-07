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

        //verification
        bool res = false;
        
        for(size_t i=0; i< state._GImanagers.size(); i++){
            for(size_t j=0; j<state._GImanagers[i]->getGameInstances().size(); j++){
                if(state._GImanagers[i]->getGameInstances()[j]->getPosition() == sf::Vector2i(_selectedPositionX,_selectedPositionY)){
                    res = true;
                    _gameInstanceSelected = state._GImanagers[i]->getGameInstances()[j];
                }
            }
        }
        if(res)
        {
            //Traitement à faire sur l'affichage
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