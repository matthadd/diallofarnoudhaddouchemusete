#include "DeepAI.h"

namespace ai{

    DeepAI::DeepAI(int length, int height){
        _length = length;
        _height = height;
    }

    DeepAI::~DeepAI(){}

    void DeepAI::GenCommands(engine::Engine& engine, state::State *state, int playerID){
        state::State *state1 = state;
        state::State *state2 = state;
        state::State *state3 = state;

        
    }

    void DeepAI::run(engine::Engine& engine){
        //engine.processCommands();
    }
}