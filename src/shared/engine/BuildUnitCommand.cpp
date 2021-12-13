#include "BuildUnitCommand.h"
#include "../state.h"
#include <iostream>
using namespace state;

namespace engine{

    BuildUnitCommand::BuildUnitCommand (int buildingID, int newUnitTypeID, int uniqueID)
    {
        _buildingID = buildingID;
        _newUnitType = newUnitTypeID;
        _uniqueID = uniqueID;
        _commandTypeID = (CommandTypeID) 4;
    }

    BuildUnitCommand::~BuildUnitCommand(){}

    bool BuildUnitCommand::process (state::State& state)
    {
        bool res = false;
        GameInstanceManager *buildingGIM;
        GameInstanceManager *unitGIM;
        // Recherche des GameInstanceManagers
        for(size_t i=0; i<state._GImanagers.size(); i++)
        {
            if(state._GImanagers[i]->getID() == 1)
            {
                buildingGIM = state._GImanagers[i];
            }
            else if(state._GImanagers[i]->getID() == 2)
            {
                unitGIM = state._GImanagers[i];
            }
        }
        // Vérification du type du bâtiment
        sf::Vector2i buildingPosition;
        int playerID;
        for(size_t i=0; i<buildingGIM->getGameInstances().size(); i++)
        {
            if(buildingGIM->getGameInstances()[i]->getId() == _buildingID)
            {
                switch (buildingGIM->getGameInstances()[i]->getTypeID())
                {
                case 3:
                {
                    res = true;
                    buildingPosition = buildingGIM->getGameInstances()[i]->getPosition();
                    playerID = buildingGIM->getGameInstances()[i]->getPlayerID();
                    break;
                }
                case 6:
                {
                    res = true;
                    buildingPosition = buildingGIM->getGameInstances()[i]->getPosition();
                    playerID = buildingGIM->getGameInstances()[i]->getPlayerID();
                    break;
                }
                default:
                    res = false;
                    break;
                }
            }
        }
        // Vérification du mana
        // A faire lorsqu'on aura fixé le prix de chaque unité

        // Créatiion de l'unité
        if(res)
        {
            GameInstance *newUnit = new GameInstance(_newUnitType, _uniqueID);
            newUnit->setPlayerID(playerID);
            newUnit->setPosition(buildingPosition);
            unitGIM->add(newUnit);
            std::cout << "Le joueur : " << playerID << " a entraîné une unité !\n" << std::endl;
            return true;
        }
        else
        {
            std::cout << "L'unité n'a pas pu être recrutée !\n" << std::endl;
            return false;
        }

    }
}

