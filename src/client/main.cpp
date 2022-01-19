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

#define Player_ID 1
#define AI_ID 2
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
        state::UnitInstance *OtherUnit = new UnitInstance(BAT, Player_ID);
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
        render::Scene s(render::MENU, &state, 32, 32, "title");
        engine::Engine engine(&state);

        state::GameInstance *warrior = new state::GameInstance("warrior", (state::GameInstanceTypeID)23);
        state::GameInstanceManager *gim_warriors = new state::GameInstanceManager("GIM_1", 3, "res/Tileset/png/Static_Global_Tileset_2_(32).png");

        // test if order matter
        warrior->assignPosition(0, 0);
        gim_warriors->add(warrior);
        state.addGIM("units", gim_warriors);

        std::thread render_thread(&render::Scene::render2, &s);

        while (1)
        {

            warrior->assignPosition(0, 0);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(4);
            warrior->assignPosition(1, 0);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(4);
            warrior->assignPosition(2, 0);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);
            warrior->assignPosition(3, 0);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);

            warrior->assignPosition(0, 1);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);
            warrior->assignPosition(0, 2);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);
            warrior->assignPosition(0, 3);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);
            warrior->assignPosition(0, 4);

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            sleep(2);

            break;

            std::cout << "[MAIN] START" << std::endl;

            std::cout << "[START] "
                      << "x: " << warrior->getX() << " y: " << warrior->getY() << std::endl;
            engine.addCommand(std::make_shared<engine::SelectionCommand>(warrior->getX(), warrior->getY()));
            engine.addCommand(std::make_shared<engine::MoveCommand>((warrior->getX() + 1) % 16, warrior->getY()));
            engine.processCommands();

            std::cout << "[MAIN] END" << std::endl;
            sleep(3);
        }
        render_thread.join();
    }

    return 0;
}