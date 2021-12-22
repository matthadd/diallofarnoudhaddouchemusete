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
        bool res = false;
        GameInstanceManager *buildingGIM;
        GameInstanceManager *unitGIM;
        // Recherche des GameInstanceManagers
        for (auto gim : state._GImanagers)
        {
            if (gim->getID() == 2) // macro GIMTypeID::BUILDING
            {
                buildingGIM = gim;
            }
            else if (gim->getID() == 3) // macro GIMTypeID::UNIT
            {
                unitGIM = gim;
            }
        }
        // Vérification du type du bâtiment
        sf::Vector2i buildingPosition;
        int playerID;
        for (auto gi : buildingGIM->getGameInstances())
        {
            if (gi->getID() == _buildingID)
            {
                if (gi->getTypeID() == state::GameInstanceTypeID::HEADQUARTER || state::GameInstanceTypeID::TRAININGCAMP)
                {
                    res = true;
                    buildingPosition = gi->getPosition();
                    playerID = gi->getPlayerID();
                }
                else
                {
                    res = false;
                    std::cout << "Il ne s'agit pas d'un bâtiment" << std::endl;
                }
            }
        }
        // Vérification du mana
        // A faire lorsqu'on aura fixé le prix de chaque unité

        // Créatiion de l'unité
        if (res)
        {
            GameInstance *newUnit = new GameInstance(_newUnitType);
            newUnit->setPlayerID(playerID);
            newUnit->setPosition(buildingPosition);
            unitGIM->add(newUnit);
            std::cout << "Le joueur : " << playerID << " a entraîné une unité !\n"
                      << std::endl;
            return true;
        }
        else
        {
            std::cout << "L'unité n'a pas pu être recrutée !\n"
                      << std::endl;
            return false;
        }
    }
}
