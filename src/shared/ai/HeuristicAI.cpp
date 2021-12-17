#include "HeuristicAI.h"
#include "../engine.h"


namespace ai{
    HeuristicAI::HeuristicAI (){}
    HeuristicAI::~HeuristicAI (){}

        void HeuristicAI::run (engine::Engine& engine)
    {
        engine.processCommands();
    }

        void HeuristicAI::GenCommands (engine::Engine& engine, state::State& state, int playerID) {}

}