#include <iostream>
#include "stdio.h"
#include "SFML/Graphics.hpp"
#include <unistd.h>
#include "SFML/Window.hpp"
#include <thread>

#include <state.h>
#include <render.h>
#include <engine.h>
#include <ai.h>

#include "macro.hpp"

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
using namespace state;
using namespace engine;
using namespace ai;

int main(int argc, char *argv[])
{

    if (argc == 2 && argv[1] == string("random"))
    {
        state::State state;
        state::UnitInstance *AIunit = new UnitInstance(DWARF, AI_ID);
        state::UnitInstance *OtherUnit = new UnitInstance(BAT, PLAYER_ID);
        AIunit->setPlayerID(AI_ID);

        ai::RandomAI randomAI;

        // Initialisation d'un état du jeu
        state::Player *ai = new Player("ai", "blue", 0);
        ai->setID(AI_ID);

        state.Players.push_back(ai);

        AIunit->assignPosition(10, 10);
        OtherUnit->assignPosition(24, 24);

        state::GameInstanceManager *unitGIM = new GameInstanceManager("Units' Manager", 2);
        unitGIM->add(AIunit);
        unitGIM->add(OtherUnit);
        state.addGIM("units", unitGIM);

        // Création du moteur du jeu
        engine::Engine engine(&state);

        // Génération des commandes de l'IA aléatoire
        state.selectObjective(OtherUnit->getPosition());
        randomAI.GenCommands(engine, state, ai->getID());
        randomAI.run(engine);

        cout << "The new unit position (" << AIunit->getX()
             << "," << AIunit->getY() << ")" << endl;
    }
    else
    {
        state::State state;
        render::Scene s(render::MENU, &state, 32, 32);
        engine::Engine engine(&state);

        state::GameInstance *warrior = new state::GameInstance("warrior", (state::GameInstanceTypeID)23);
        state::GameInstanceManager *gim_warriors = new state::GameInstanceManager("GIM_1", 3, PATH_UNITS);

        // test if order matter
        warrior->assignPosition(0, 0);
        gim_warriors->add(warrior);
        state.addGIM("units", gim_warriors);

        std::thread render_thread(&render::Scene::render2, &s);
        state.turn = 3;

        while (1)
        {
            std::cout << "[MAIN GAME] " << state.turn;

            // BEFORE TURN
            // activePlayer = turn % 2

            


            // TURN BEGIN
            // wait for two coord inputs from render
            // loop while updateOnClick != true. Go true if 1 input are in

              // selection command with engine : check if 1 input are legit if not go TURN BEGIN

                // if yes choose if MOVE or ATTACK 

                // else goto END TURN
            
            // END TURN : turn++

        }
        render_thread.join();
    }

    return 0;
}