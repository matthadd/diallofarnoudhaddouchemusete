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
        for (auto x : state._GImanagers)
        {
            if (x.first == "units")
            {
                unit_gim = x.second;
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

    void RandomAI::run(engine::Engine &engine)
    {
        engine.processCommands();
    }

}
