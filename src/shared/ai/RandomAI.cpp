#include "RandomAI.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include "../engine.h"
#include "../state.h"

namespace ai
{
    // Constructeur vide
    RandomAI::RandomAI() {}

    // Destructeur
    RandomAI::~RandomAI() {}

    // Méthode de génération de nombres aléatoires
    int RandomAI::GenRand(int randRange)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, randRange); // distributionin range [0, value]

        return dist(rng);
    }

    // Méthode de génération des commandes aléatoires
    void RandomAI::GenCommands(engine::Engine &engine, state::State &state, int playerID)
    {
        state::GameInstanceManager *unit_gim;
        int unit_layer_id = 2;
        for (state::GameInstanceManager *GIM : state._GImanagers)
        {
            if (GIM->getID() == unit_layer_id)
            {
                unit_gim = GIM;
            }
        }

        for (state::GameInstance *GI : unit_gim->getGameInstances())
        {
            if (GI->getPlayerID() == playerID && GI->getTypeID() > 6)
            {
                int rand_value = RandomAI::GenRand(RandomAI::_unitActionRandRange);
                std::cout << rand_value << std::endl;
                if (rand_value == 1)
                {
                    engine.addCommand(std::make_shared<engine::MoveCommand>(RandomAI::GenRand(16), RandomAI::GenRand(16)));
                    std::cout << "l'unité (id = " << GI->getID() << " de l'IA (player_ID = " << GI->getPlayerID() << " a été déplacée";
                }
            }
        }
    }

}
