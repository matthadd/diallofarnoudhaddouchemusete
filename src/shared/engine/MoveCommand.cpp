#include "MoveCommand.h"
#include <iostream>
namespace engine{
    MoveCommand::MoveCommand(int newPositionX, int newPositionY){
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _commandTypeID = (CommandTypeID) 2;
    }

    MoveCommand::~MoveCommand(){}

    bool MoveCommand::process(state::State& state){
        MoveCommandHandler* handler = new MoveCommandHandler(_newPositionX, _newPositionY);
        if(handler->process(state)){
            std::cout << "Vous pouvez déplacer ce joueur ici." << std::endl;
        }
    }

    void MoveCommand::setGameInstance(state::GameInstance* ptr_GameInstance){
        _gameInstanceSelected = ptr_GameInstance;
    }
}