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
    RandomAI::RandomAI(int height, int length) 
    {
        _length = length;
        _height  = height;
    }

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
        for (state::GameInstance *GI : state._GImanagers["units"]->getGameInstances())
        {
            if (GI->getPlayerID() == playerID && GI->getTypeID() > 6)
            {
                int rand_value = RandomAI::GenRand(RandomAI::_unitActionRandRange);
                std::cout << rand_value << std::endl;
                if (rand_value == 1){
                    //commande de sélection
                    engine.addCommand(std::make_shared<engine::SelectionCommand>(GI->getX(), GI->getY()));

                    //commande de déplacement
                    engine.addCommand(std::make_shared<engine::MoveCommand>(11, 11));
                    std::cout << "l'unité (id = " << GI->getID() << ") de l'IA (player_ID = " 
                    << GI->getPlayerID() << ") a été déplacée" << std::endl;
                }
                else if(rand_value == 2){
                    //comande de sélection
                    engine.addCommand(std::make_shared<engine::SelectionCommand>(GI->getX(), GI->getY()));

                    //commande d'attaque (à revoir une fois la sélection de l'objective possible avec
                    //la commande de sélection)
                    /*engine.addCommand(std::make_shared<engine::AttackCommand>());
                    std::cout << "l'unité (id = " << GI->getID() << ") de l'IA (player_ID = " 
                    << GI->getPlayerID() << ") a attaqué" << std::endl;*/
                }
                else if(rand_value == 3){
                    //commande de sélection
                    engine.addCommand(std::make_shared<engine::SelectionCommand>(GI->getX(), GI->getY()));
                    std::cout << "l'unité a été sélectionnée pour être déplacée" << std::endl;

                    //commande de déplacement
                    engine.addCommand(std::make_shared<engine::MoveCommand>(11, 11));
                    std::cout << "l'unité (id = " << GI->getID() << ") de l'IA (player_ID = " 
                    << GI->getPlayerID() << ") a été déplacée" << std::endl;

                    //commande de sélection
                    engine.addCommand(std::make_shared<engine::SelectionCommand>(GI->getX(), GI->getY()));
                    std::cout<< "lunité a été resélecionnée pour attaquer" << std::endl;

                    //commande d'attaque (à revoir une fois la sélection de l'objective possible avec
                    //la commande de sélection)
                    /*engine.addCommand(std::make_shared<engine::AttackCommand>());
                    std::cout << "l'unité (id = " << GI->getID() << ") de l'IA (player_ID = " 
                    << GI->getPlayerID() << ") a attaqué" << std::endl;*/
                }
            }
            run(engine);
        }
        engine.addCommand(std::make_shared<engine::EndTurnCommand>((state::Playing) playerID));
    }

    void RandomAI::run(engine::Engine &engine)
    {
        engine.processCommands();
    }

}
