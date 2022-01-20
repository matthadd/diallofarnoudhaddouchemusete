#include "State.h"
#include <iostream>
#include <map>

namespace state
{
    state::State::State() {}

    state::State::~State() {}

    state::Player *state::State::GetActivePlayer()
    {
        return Players[turn % Players.size()];
    }

    void state::State::endTurn(int playerID)
    {
        if (!playerID == state::State::GetActivePlayer()->getID())
        {
            std::cout << "It is not your turn !\n";
        }
        else
        {
            turn++;
            if (state::State::GetActivePlayer()->getID() == state::Playing::PLAYER_1)
            {
                playing = state::Playing::PLAYER_1;
            }
            else if (state::State::GetActivePlayer()->getID() == state::Playing::PLAYER_2)
            {
                playing = state::Playing::PLAYER_2;
            }
            std::cout << "turn  : " << turn << "\n";
        }
    }

    void state::State::init()
    {
        CurrentMap = NULL;
        turn = 0;
        instance = 0;
        status = 0;
        printf("Initialisation done ... \n");
    }
    void state::State::init(Map *map)
    {
        CurrentMap = map;
        turn = 0;
        instance = 0;
        status = 0;
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

    void state::State::addGIM(std::string key, GameInstanceManager *gim)
    {

        _GImanagers[key] = gim;
    }

    void state::State::selectObjective(std::vector<int> unitPos)
    {
        for (auto elt : _GImanagers)
        {
            elt.second->selectObjective(unitPos);
        }
    }

    void state::State::selectSource(std::vector<int> unitPos)
    {
        prevSelectedGI = unitPos;
        for (auto elt : _GImanagers)
        {
            elt.second->selectSource(unitPos, activePlayer->getID());
        }
    }

    GameInstance *state::State::getGI(int x, int y)
    {
        std::vector<int> vec = {x, y};
        for (auto elt : _GImanagers)
        {
            for (auto gi : elt.second->getGameInstances())
            {
                if (gi->getPosition() == vec)
                {
                    return gi;
                    break;
                }
            }
        }
        return NULL;
    }

    std::vector<GameInstance *> state::State::findPlayerAllies(int playerID)
    {
        std::vector<GameInstance *> allies;
        for (auto elt : _GImanagers["units"]->getGameInstances())
        {
            if (elt->getPlayerID() == playerID)
            {
                allies.push_back(elt);
            }
        }
        return allies;
    }

    std::vector<std::pair<int, int>> state::State::showEnemies()
    {
        std::vector<std::pair<int, int>> enemies;
        for (auto gi : _GImanagers["units"]->getGameInstances())
        {
            if (gi->getPlayerID() != GetActivePlayer()->getID())
            {
                enemies.push_back(std::pair<int, int>(gi->getX(), gi->getY()));
            }
        }
        for (auto gi : _GImanagers["buildings"]->getGameInstances())
        {
            if (gi->getPlayerID() != GetActivePlayer()->getID())
            {
                enemies.push_back(std::pair<int, int>(gi->getX(), gi->getY()));
            }
        }
        return enemies;
    }

    void state::State::cleanUp(GameInstance *gi)
    {
        _GImanagers["units"]->deleteIfDead(gi);
    }

    std::vector<int> state::State::getPrevSelect()
    {
        return prevSelectedGI;
    }

    void state::State::setPrevSelect(std::vector<int> v)
    {
        prevSelectedGI = v;
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