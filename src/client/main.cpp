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

        state::UnitFactory *unitfact = new state::UnitFactory();
        state::GameInstance *warrior1 = unitfact->createGI((state::GameInstanceTypeID)23, PLAYER_1_ID);
        state::GameInstance *warrior2 = unitfact->createGI((state::GameInstanceTypeID)23, PLAYER_2_ID);

        // state::GameInstance *warrior1 = new state::GameInstance("warrior1", (state::GameInstanceTypeID)23);

        state::GameInstanceManager *gim_warriors = new state::GameInstanceManager("GIM_1", 3, PATH_UNITS);

        // test if order matter
        gim_warriors->add(warrior1);
        gim_warriors->add(warrior2);

        warrior1->assignPosition(0, 0);
        warrior2->assignPosition(15, 15);

        state.addGIM("units", gim_warriors);

        std::thread render_thread(&render::Scene::render2, &s);
        state.turn = 0;

        state::Player P1(PLAYER_1_ID);
        state::Player P2(PLAYER_2_ID);
        state.activePlayer = &P1;

        state.updateRender = true;

        while (1)
        {

            int current_turn = state.turn;

            while (current_turn == state.turn)
            {
                // std::cout << "[MAIN GAME] " << state.turn;

                // BEFORE TURN

                // 1 - choose active player
                if (state.turn % 2 == 0)
                {
                    std::cout << "PLAYER 1 TURN" << std::endl;
                    state.activePlayer = &P1;
                }
                else
                {
                    std::cout << "PLAYER 2 TURN" << std::endl;
                    state.activePlayer = &P2;
                }

                // TURN BEGIN

                // ProcessTurnBegin() from Tim
                // state.ProcessTurnBegin();
                state.prevSelectedGI = {-1, -1};
                std::vector<int> prev = state.prevSelectedGI;

                // wait for two coord inputs from render
                while (prev[0] == state.prevSelectedGI[0] && prev[1] == state.prevSelectedGI[1])
                // while getPrevSelect doesnt change -> wait
                {
                }
                state.updateRender = true;

                auto sel = std::make_shared<SelectionCommand>(state.getPrevSelect()[0], state.getPrevSelect()[1]);
                engine.addCommand(sel);
                engine.processCommands();

                std::cout << "[MAIN] x : " << state.getPrevSelect()[0] << " y: " << state.getPrevSelect()[1] << std::endl;
                std::cout << "[WARRIOR 1] x : " << warrior1->getPosition()[0] << " y: " << warrior1->getPosition()[0] << std::endl;
                // struct {source[GI], target:[GI, pos]}

                // SelectionCommand FAILED : outside map, pos save but no GI
                // SelectionCommand PASS : f(GI)  = source

                // MOVE

                auto move = std::make_shared<MoveCommand>();
                engine.addCommand(move);
                engine.processCommands();
                state.updateRender = true;

                // ATTACK

                auto attack = std::make_shared<AttackCommand>();
                engine.addCommand(attack);
                engine.processCommands();

                state.updateRender = true;
            }
        }
        render_thread.join();
    }

    return 0;
}