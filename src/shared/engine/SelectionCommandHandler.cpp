#include "SelectionCommandHandler.h"
using namespace sf;
namespace engine{

    SelectionCommandHandler::SelectionCommandHandler(int x, int y){
        _selectedPositionX = x;
        _selectedPositionY = y;
    }

    SelectionCommandHandler::~SelectionCommandHandler(){}

    bool SelectionCommandHandler::process(state::State& state){

        bool res = false;
        sf::Vector2i vec = sf::Vector2i(_selectedPositionX,_selectedPositionY);
        
        for(size_t i=0; i< state._GImanagers.size(); i++){
            for(size_t j=0; j<state._GImanagers[i]->getGameInstances().size(); j++){
                if(state._GImanagers[i]->getGameInstances()[j]->getPosition() == vec){
                    res = true;
                    _gameInstanceSelected = state._GImanagers[i]->getGameInstances()[j];
                }
            }
        }
        return res;
    }

    state::GameInstance* SelectionCommandHandler::getGameInstance(){
        return _gameInstanceSelected;
    }
}