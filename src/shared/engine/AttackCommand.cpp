#include "AttackCommand.h"
#include "../state.h"
#include <iostream>
#include <math.h>

using namespace state;

namespace engine
{

    AttackCommand::AttackCommand()
    {

    }
    AttackCommand::~AttackCommand()
    {

    }

    bool AttackCommand::process(state::State& state){
        
        try{
            state::UnitInstance* _giSource =(state::UnitInstance*) state.getSource();
            state::UnitInstance* _giTarget=(state::UnitInstance*) state.getObjective();
            //_giTarget = state.getObjective();
            
            int targetX=_giTarget->getPosition()[0];
            int targetY=_giTarget->getPosition()[1];
            int sourceX=_giSource->getPosition()[0];
            int sourceY=_giSource->getPosition()[1];
            
            if(_giSource->getPlayerID()==_giTarget->getPlayerID()){
                throw std::string("Error the target is an ally");}
            
            if ((pow((targetX-sourceX),2)+pow((targetY-sourceY),2))>pow(_giSource->getSight(),2)){
                   throw std::string("Error the target is out of sigth range");}


            _giTarget->receiveDamage(_giSource->giveDamage());
            std::vector<GameInstance*> units = state._GImanagers["units"]->getGameInstances();
            state.cleanUp(_giTarget);
            
            return true;
        }
        catch(std::string strr)
        {
            std::cout<<strr;
            return false;
        }
    }



}