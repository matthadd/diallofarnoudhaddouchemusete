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

    void HeuristicAI::GenCommands (engine::Engine& engine, state::State *state, int playerID) 
    {
        PathsMap firstpaths(NULL,_height,_length);
        firstpaths.init();
        for (auto ally : state->findPlayerAllies(state->playing))
        {
            if(ally->getTypeID()>6)
            {
                PathsMap* paths = new PathsMap((state::UnitInstance*) ally, _length, _height); 
                auto closestEnemy = paths->findClosestEnemy(*state);
                if( closestEnemy != std::pair<int,int>(-1, -1))
                {
                    //sélection de l'unité
                    engine.addCommand(std::make_shared<engine::SelectionCommand>(ally->getX(), ally->getY()));
                    Position* bestPosition = paths->giveBestPosition(*state, closestEnemy);

                    // si l'unité ennemi est à portée d'attaque
                    if(paths->distance(closestEnemy, std::pair<int, int>(ally->getX(), ally->getY()))==1 && 
                        state->getGI(closestEnemy.first, closestEnemy.second)->getTypeID()>6)
                    {
                        state->selectObjective(std::vector<int>{closestEnemy.first, closestEnemy.second});
                        engine.addCommand(std::make_shared<engine::AttackCommand>());
                    }

                    //si le bâtiment ennemi est à  1 case
                    else if(paths->distance(closestEnemy, std::pair<int, int>(ally->getX(), ally->getY()))<1 && 
                            state->getGI(closestEnemy.first, closestEnemy.second)->getTypeID()<7)
                    {
                        engine.addCommand(std::make_shared<engine::MoveCommand>(closestEnemy.first, closestEnemy.second));
                    }
                    else{
                        engine.addCommand(std::make_shared<engine::MoveCommand>(bestPosition->getX(), bestPosition->getY()));
                    }
                    run(engine);
                }
            }
        }
        //on termine le tour
        engine.addCommand(std::make_shared<engine::EndTurnCommand>((state::Playing) playerID));
    }

    

}