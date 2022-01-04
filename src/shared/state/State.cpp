#include "State.h"
#include <iostream>
#include <map>

namespace state{
    state::State::State(){}

    state::State::~State(){}

    void state::State::onTurnBegin()
    {
        state::State::turn++;
        std::cout << "ON_TURN_BEGIN_STATE" << std::endl;
    }
    void state::State::onTurnBeginAsync()
    {
        std::cout << "ON_TURN_BEGIN_ASYNC_STATE" << std::endl;
    }
    void state::State::onTurnEnd()
    {
        std::cout << "ON_TURN_END_STATE" << std::endl;
    }
    void state::State::onTurnEndAsync()
    {
        std::cout << "ON_TURN_END_ASYNC_WH" << std::endl;
    }
    state::Player* state::State::GetActivePlayer()
    {
        return Players[turn % Players.size()];
    }

    /*bool state::State::isOver()
    {
        if(!((status >> 4) ^ 0xF))
            return true;
        return false;
    }
    char state::State::WinnerID()
    {
        if(!isOver())
            return -1;
        return status & 0xF;
    }*/
    void state::State::init()
    {
        CurrentMap = NULL;
        turn = 0;
        instance = 0;
        status = 0;
        printf("Initialisation done ... \n");
    }
    void state::State::init(Map* map)
    {
        CurrentMap = map;
        turn = 0;
        instance = 0;
        status = 0;
    }
    void* state::State::ProcessAllAsync(void* func)
    {
        (*((std::function<void()>*)func))();
        return NULL;
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
                if(gi->getPosition() == vec)
                {
                    return gi;
                    break;
                }
            }
        }
        return NULL;
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
