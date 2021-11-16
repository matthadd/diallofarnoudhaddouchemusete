#include "State.h"
#include <iostream>

void state::State::onTurnBegin()
{
    turn++;
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
state::Player* state::State::GetMyPlayer()
{
    return Players[id];
}
bool state::State::isOver()
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
}
void state::State::init()
{
    CurrentEnvironnement = NULL;
    turn = 0;
    instance = 0;
    status = 0;
    printf("Initialisation done ... \n");
}
void state::State::init(Environnement* env)
{
    CurrentEnvironnement = env;
    turn = 0;
    instance = 0;
    status = 0;
}
void* state::State::ProcessAllAsync(void* func)
{
    (*((std::function<void()>*)func))();
    return NULL;
}

/*
SUBSCRIBERS ??


template <class T> 
void state::State::Subscribe2TurnBegin()
{
    TurnBeginEvents.push_back(T::onTurnBegin);
}
template <class T> 
void state::State::Subscribe2TurnBeginAsync()
{
    TurnBeginEvents.push_back(T::onTurnBeginAsync);
}
template <class T> 
void state::State::Subscribe2TurnEnd()
{
    TurnEndEvents.push_back(T::onTurnEnd);
}
template <class T> 
void state::State::Subscribe2TurnEndAsync()
{
    TurnEndEvents.push_back(T::onTurnEndAsync);
}

*/