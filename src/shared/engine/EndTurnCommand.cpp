#include "EndTurnCommand.h"
#include <iostream>

namespace engine{
    EndTurnCommand::EndTurnCommand (state::Playing playerID){
        _playing = playerID;
    }
    
    EndTurnCommand::~EndTurnCommand (){}

    bool EndTurnCommand::process  (state::State *state)
    {
        // verifying the rights of the command user
        if(state->whoIsPlaying() == _playing){
            state->endTurn(_playing);
            std::cout << "turn  : " << state->showTurnNumber() << "\n";
            return true;
        }
        else{
            throw std::runtime_error("It is not your turn");
            return false;
        }
    }
}    
    