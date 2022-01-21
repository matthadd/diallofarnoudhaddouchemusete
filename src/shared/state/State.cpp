#include "State.h"
#include <iostream>
#include <map>
#include "BuildingInstance.h"
#include "UnitInstance.h"

namespace state{
    state::State::State(){}

    state::State::~State(){}

    state::Player* state::State::GetActivePlayer()
    {
        return Players[turn % Players.size()];
    }

    Playing state::State::whoIsPlaying() const {
        return playing;
    }

    int state::State::showTurnNumber () const {
        return turn;
    }

    void state::State::endTurn()
    {
        turn++;
        if(playing != NO_PLAYER || playing != END_GAME)
        {
            if(playing == PLAYER_1){
                playing = PLAYER_2;
            }
            else if(playing == PLAYER_2){
                playing = PLAYER_1;
            }
        }           
        else
        {
            throw std::logic_error("No one can currently play");
        }
        onTurnEnd();
        //endGameCheck();
    }

    void state::State::onTurnEnd()
    {
        for(auto building : _GImanagers["buildings"]->getGameInstances())
        {
            auto unit = findUnit(building->getX(), building->getY());
            auto building2 = (BuildingInstance*) building;
            if(unit)
                if(unit->getPlayerID() != building->getPlayerID())
                {  
                    building2->capturing(unit->getPlayerID());
                    building2->addCaptureCounter();
                }
            else  
                building2->resetCaptureCounter();  

            /*//checking endgame           
            if(building2->getPlayerID()==HEADQUARTER && building2->wasCaptured()){
                this->winner = (Playing) unit->getPlayerID();
                this->playing = (Playing) unit->getPlayerID();
            }*/

        }
    }
    
    void state::State::init()
    {
        CurrentMap = NULL;
        turn = 0;
        instance = 0;
        status = 0;
        playing = PLAYER_1;
        isOver =false;
        printf("Initialisation done ... \n");
    }
    void state::State::init(Map* map)
    {
        CurrentMap = map;
        turn = 0;
        instance = 0;
        status = 0;
        playing = PLAYER_1;
        isOver =false;
    }

    GameInstance *state::State::getSource()
    {
        return _GImanagers["units"]->getSource();
    }

    GameInstance *state::State::getObjective()
    {
        return _GImanagers["units"]->getObjective();
    }

    void state::State::addGI(std::string key, GameInstance *gi)
    {
        _GImanagers[key]->add(gi);
    }

    void state::State::addGIM(std::string key, GameInstanceManager* gim)
    {

     _GImanagers[key] = gim;
 
    }

    void state::State::selectObjective(std::vector<int> unitPos)
    {
        for(auto elt : _GImanagers)
        {
            elt.second->selectObjective(unitPos);
        }
    }

    void state::State::selectSource(std::vector<int> unitPos)
    {
        for(auto elt : _GImanagers)
        {
            elt.second->selectSource(unitPos);
        }
    }

    GameInstance* state::State::getGI(int x, int y)
    {
        std::vector<int> vec = {x,y};
        for(auto elt : _GImanagers)
        {
            for(auto gi : elt.second->getGameInstances())
            {
                if(gi->getPosition() == vec && gi != getSource())
                {
                    return gi;
                }
            }
        }
        return NULL;
    }

    UnitInstance* state::State::findUnit(int x, int y)
    {
        std::vector<int> vec = {x,y};
        for(auto gi : _GImanagers["units"]->getGameInstances())
        {
            if(gi->getPosition() == vec)
                {
                    auto unit = (UnitInstance*) gi;
                    return unit;
                }
        }
        return NULL;
    }

    BuildingInstance* state::State::findBuilding(int x, int y)
    {
        std::vector<int> vec = {x,y};
        for(auto gi : _GImanagers["buildings"]->getGameInstances())
        {
            if(gi->getPosition() == vec)
                {
                    auto building = (BuildingInstance*) gi;
                    return building;
                }
        }
        return NULL;
    }

    bool state::State::comparePlayerID(GameInstance* gi1, GameInstance* gi2){
        if(gi1->getPlayerID() == gi2->getPlayerID())
            return true;
        return false;
    }

    std::vector<GameInstance*> state::State::findPlayerAllies(int playerID)
    {
        std::vector<GameInstance*> allies;
        for(auto elt : _GImanagers)
        {
            for(auto gi : elt.second->getGameInstances())
            {
                if(gi->getPlayerID() == playerID)
                {
                    auto gi2 = gi;
                    allies.push_back(gi2);
                }
            }
        }
        return allies;
    }

    std::vector< std::pair<int,int> > state::State::showEnemies()
    {
        std::vector< std::pair<int, int>> enemies;
        for(auto elt : _GImanagers){
            for(auto gi : elt.second->getGameInstances())
            {
                if(gi->getPlayerID() != (int) playing)
                {
                    enemies.push_back(std::pair<int,int>(gi->getX(),gi->getY()) );
                }
            }
        }
        return enemies;
    } 
    
    void state::State:: cleanUp (GameInstance* gi){
        _GImanagers["units"]->deleteIfDead(gi);
    }

    void state::State:: captureBuilding(GameInstance* unit, GameInstance* building_gi){
        if(unit->getTypeID()>6){
            state::BuildingInstance* building = (BuildingInstance*) building_gi;
            building->capturing(unit->getPlayerID());
            building->addCaptureCounter();
        }
        else
            throw std::runtime_error("Only units can capture a building");
    }

    void state::State:: endGameCheck()
    {
        /*for(auto building : _GImanagers["building"]->getGameInstances())
        {
            if(building->getTypeID() == HEADQUARTER)
                {
                    auto hq = (BuildingInstance*) building;
                    if(hq->wasCaptured()){
                        isOver = true;
                        playing = END_GAME;
                        if(hq->getPlayerID()== PLAYER_1)
                            winner = PLAYER_2;
                        else
                            winner = PLAYER_1;
                    }
                        
                }
        }*/
    }
    /*
    SUBSCRIBERS ??


    template <class T> 
    void state::State::subscribeTurnBegin()
    {
        TurnBeginEvents.push_back(T::onTurnBegin);
    }
    template <class T> 
    void state::State::subscribeTurnBeginAsync()
    {
        TurnBeginEvents.push_back(T::onTurnBeginAsync);
    }
    template <class T> 
    void state::State::subscribeTurnEnd()
    {
        TurnEndEvents.push_back(T::onTurnEnd);
    }
    template <class T> 
    void state::State::subscribeTurnEndAsync()
    {
        TurnEndEvents.push_back(T::onTurnEndAsync);
    }

    */
}
