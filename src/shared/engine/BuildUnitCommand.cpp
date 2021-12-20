#include "BuildUnitCommand.h"
#include "../state.h"
#include <iostream>
using namespace state;

namespace engine
{

    BuildUnitCommand::BuildUnitCommand(int buildingID, GameInstanceTypeID newUnitTypeID)
    {
        _buildingID = buildingID;
        _newUnitType = newUnitTypeID;
        _commandTypeID = (CommandTypeID)4;
    }

    BuildUnitCommand::~BuildUnitCommand() {}

    bool BuildUnitCommand::process(state::State &state)
    {
        bool res = true;
        try
        {
            //Checking typeID
            if(state.getSource()->getTypeID() != GameInstanceTypeID::HEADQUARTER && 
               state.getSource()->getTypeID() != GameInstanceTypeID::TRAININGCAMP)
            {   
                throw std::string("Only training camps and headquarters can produce unit");
                res = false;
            }

            Player *ply_ptr = state.GetActivePlayer();
            UnitFactory uf;
            UnitInstance* createdUnit = (UnitInstance*) uf.createGI(_newUnitType, ply_ptr->getID());
            
            // Checking mana balance
            if(ply_ptr->balance() < createdUnit->cost())
            {
                throw std::string("You do not have enough mana to produce this unit !");
                delete createdUnit;
                res = false;
            }

            //debit player mana wallet

            ply_ptr->debit(createdUnit->cost());
            //state._GImanagers["units"]->add(createdUnit);
            state.addGI("units", createdUnit);
            return res;
            
        }
        catch(std::string& str)
        {
            std::cerr << str << '\n';
            return res;
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cout << "BuilUnitCommand error" << '\n';
        }

    }
}
