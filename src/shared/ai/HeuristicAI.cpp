#include "HeuristicAI.h"
#include "../engine.h"
#include "PathsMap.h"


namespace ai{
    HeuristicAI::HeuristicAI (){}
    HeuristicAI::~HeuristicAI (){}

        void HeuristicAI::run (engine::Engine& engine)
    {
        engine.processCommands();
    }

    void HeuristicAI::GenCommands (engine::Engine& engine, state::State& state, int playerID, int length, int height) 
    {
        PathsMap firstpaths(NULL,height,length);
        firstpaths.init();
        for (auto ally : state.showAllies())
        {
            PathsMap* paths = new PathsMap((state::UnitInstance*) ally, length, height); 
            if(paths->findClosestEnemy(state) != std::pair<int,int>(-1, -1))
            {
                engine.addCommand(std::make_shared<engine::SelectionCommand>(ally->getX(), ally->getY()));
                Position bestPosition = paths->bestPosition(state);
                engine.addCommand(std::make_shared<engine::MoveCommand>(bestPosition.getX(), bestPosition.getY()));
            }
        }
    }

    

}