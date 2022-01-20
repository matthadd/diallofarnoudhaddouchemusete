#include "HeuristicAI.h"
#include "../engine.h"
#include "PathsMap.h"


namespace ai{
    HeuristicAI::HeuristicAI (int length, int height)
    {
        _height = height;
        _length = length;
    }
    HeuristicAI::~HeuristicAI (){}

        void HeuristicAI::run (engine::Engine& engine)
    {
        engine.processCommands();
    }

    void HeuristicAI::GenCommands (engine::Engine& engine, state::State& state, int playerID) 
    {
        PathsMap firstpaths(NULL,_height,_length);
        firstpaths.init();
        for (auto ally : state.findPlayerAllies(state.GetActivePlayer()->getID()))
        {
            PathsMap* paths = new PathsMap((state::UnitInstance*) ally, _length, _height); 
            auto closestEnemy = paths->findClosestEnemy(state);
            if( closestEnemy != std::pair<int,int>(-1, -1))
            {
                engine.addCommand(std::make_shared<engine::SelectionCommand>(ally->getX(), ally->getY()));
                Position bestPosition = paths->giveBestPosition(state, closestEnemy);
                engine.addCommand(std::make_shared<engine::MoveCommand>(bestPosition.getX(), bestPosition.getY()));
                run(engine);
            }
        }
        engine.addCommand(std::make_shared<engine::EndTurnCommand>((state::Playing) playerID));
    }

    

}