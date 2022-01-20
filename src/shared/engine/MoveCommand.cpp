#include "MoveCommand.h"
#include <iostream>
#include <math.h>
#include "../state.h"
namespace engine
{
    MoveCommand::MoveCommand(int newPositionX, int newPositionY)
    {
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _commandTypeID = (CommandTypeID)2;
    }

    MoveCommand::~MoveCommand() {}

    bool MoveCommand::process(state::State *state)
    {
        // Vérification de la règle
        bool res = true;
           /* 
            if(!state->getGI(_newPositionX, _newPositionY))
            {
                state->getSource()->assignPosition(_newPositionX, _newPositionY);
            }
            else if(state->getGI(_newPositionX, _newPositionY)->getTypeID() > 6)
            {
                throw std::string("This cell is already occupied");
                res = false;
            }
            else
            {
                state->getSource()->assignPosition(_newPositionX, _newPositionY);
            }
*/            

         try{
            state::UnitInstance* _giSource =(state::UnitInstance*) state->getSource();
            int sourceX=state->getSource()->getPosition()[0];
            int sourceY=state->getSource()->getPosition()[1];
            int targetX=state->getPrevSelect()[0];
            int targetY=state->getPrevSelect()[1];
           
            
            if(!state->getGI(state->getPrevSelect()[0], state->getPrevSelect()[1])||state->getGI(state->getPrevSelect()[0], state->getPrevSelect()[1])->getTypeID() < 6)
            {   
                std::cout<<"je suis dedans";
                if ((pow((targetX-sourceX),2)+pow((targetY-sourceY),2))<pow(_giSource->getMoveRange(),2)){
                    std::cout<<"je suis rentré";
                    state->getSource()->assignPosition(state->getPrevSelect());
                }
                
            }
            else{res=false;}
            
         }
        catch(std::string strr)
        {
            std::cout<<strr;
            return false;
        }
        return res;
    }

    void MoveCommand::setGameInstance(state::GameInstance *ptr_GameInstance)
    {
        _gameInstanceSelected = ptr_GameInstance;
    }
}