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

    void HeuristicAI::GenCommands (engine::Engine& engine, state::State& state, int playerID) 
    {
        PathsMap firstpaths(NULL,32,32);
        firstpaths.init();
        for (auto ally : state.showAllies())
        {
            PathsMap* paths = new PathsMap((state::UnitInstance*) ally, 32, 32); 
            if(Position* pos =paths->findClosestEnemy() != NULL)
            {
                engine.addCommand(std::make_shared<engine::SelectionCommand>(ally->getX(), ally->getY()));
                engine.addCommand(std::make_shared<engine::MoveCommand>(paths->bestPositon().first, paths->bestPositon().second));
            }
        }
    }

    

}