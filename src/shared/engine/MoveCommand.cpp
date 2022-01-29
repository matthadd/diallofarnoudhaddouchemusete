#include "MoveCommand.h"
#include <iostream>
#include <math.h>
#include "../state.h"
namespace engine
{

    MoveCommand::MoveCommand()
    {

        _commandTypeID = (CommandTypeID)2;
    }
    MoveCommand::MoveCommand(int newPositionX, int newPositionY)
    {
        _newPositionX = newPositionX;
        _newPositionY = newPositionY;
        _commandTypeID = (CommandTypeID)2;
    }

    MoveCommand::~MoveCommand() {}

    bool MoveCommand::process(state::State *state)
    {
        bool res = true;
        try
        {
            state::UnitInstance *_giSource = (state::UnitInstance *)state->getSource();

            if (_giSource == NULL)
                return false;

            int sourceX = state->getSource()->getPosition()[0];
            int sourceY = state->getSource()->getPosition()[1];
            int targetX = state->getPrevSelect()[0];
            int targetY = state->getPrevSelect()[1];

            if (!state->getGI(state->getPrevSelect()[0], state->getPrevSelect()[1]) || state->getGI(state->getPrevSelect()[0], state->getPrevSelect()[1])->getTypeID() < 6)
            {
                // std::cout << "je suis dedans" << std::endl;

                if ((pow((targetX - sourceX), 2) + pow((targetY - sourceY), 2)) < pow(_giSource->getMoveRange(), 2))
                {
                    // std::cout << "je suis rentré" << std::endl;
                    std::cout << "[ENGINE] MOVE" << std::endl;
                    state->getSource()->assignPosition(state->getPrevSelect());
                    std::cout << "[ENGINE] getPrevSelect : " << state->getPrevSelect()[0] << "-" << state->getPrevSelect()[1] << std::endl;

                    return true;
                }
                std::cout << "[ENGINE] NO UNIT HERE" << std::endl;
            }
            else
            {
                res = false;
            }
        }
        catch (std::string strr)
        {
            std::cout << strr;
            return false;
        }
        return res;
    }

    void MoveCommand::setGameInstance(state::GameInstance *ptr_GameInstance)
    {
        _gameInstanceSelected = ptr_GameInstance;
    }
}