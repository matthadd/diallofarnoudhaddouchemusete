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
        randomAI.GenCommands(engine, &state, ai->getID());
        randomAI.run(engine);

        cout << "The new unit position (" << AIunit->getX()
             << "," << AIunit->getY() << ")" << endl;
    }
    else if (argc == 2 && argv[1] == string("heuristic"))
    {
        #define HEURISTIC_ID 1
        #define RANDOM_ID 2
        #define LENGTH 4
        #define HEIGHT 4
        int winCounter_H = 0;
        int winCounter_R = 0;

        for(int i =0; i<20; i++)
        {
            State state;
            state.init();
            //Tests de l'IA Heuristic sur une petite map 4*4
            state::State heuristicAiState;
            //création de l'ia heuristique :
            ai::HeuristicAI heuristicAi(4,4);
            Player hAi("Heuristic AI", "red", HEURISTIC_ID);
            //création de l'ia random :
            ai::RandomAI randomAi(4,4);
            Player rAi("Random AI", "blue", RANDOM_ID);

            state.Players.push_back(&hAi);
            state.Players.push_back(&rAi);

            //création des unités et bâtiments
            state.addGIM("units", new GameInstanceManager("units", 0)); 
            state.addGIM("buildings", new GameInstanceManager("building", 1));

            //mise en place des quartiers généraux
            BuildingFactory bf;
            auto hqH = (BuildingInstance*) bf.createGI(HEADQUARTER, HEURISTIC_ID);
            auto hqR = (BuildingInstance*) bf.createGI(HEADQUARTER, RANDOM_ID);

            hqH->assignPosition(0,3);
            hqR->assignPosition(3,0);

            //mise en place des unités

            UnitFactory uf;
            auto batH = (UnitInstance*) uf.createGI(BAT, HEURISTIC_ID);
            auto batR = (BuildingInstance*) uf.createGI(BAT, RANDOM_ID);
            batH->assignPosition(0,2);
            batR->assignPosition(1,3);

            Engine engine(&state);
            
            while(state.playing != END_GAME)
            {
                heuristicAi.GenCommands(engine, &state, HEURISTIC_ID);
                heuristicAi.run(engine);
                randomAi.GenCommands(engine, &state, RANDOM_ID);
                randomAi.run(engine);
                }

                if(state.winner == PLAYER_1)
                winCounter_H++;
                else if(state.winner == PLAYER_2)
                winCounter_R++; 
                }
                std::cout << "heuristic win rate : " << winCounter_H/20 << std::endl;
                std::cout << "random win rate : " << winCounter_R/20 << std::endl;
            }
    else{
        
        state::State state;
        render::Scene s(render::MENU, &state, 32, 32);
        engine::Engine engine(&state);

        state::UnitFactory *unitfact = new state::UnitFactory();
        state::GameInstance *warrior1 = unitfact->createGI((state::GameInstanceTypeID)WARRIOR_DWARF_1, PLAYER_1_ID);
        state::GameInstance *warrior2 = unitfact->createGI((state::GameInstanceTypeID)WARRIOR_HUMAN_1, PLAYER_2_ID);

        state::BuildingFactory *buildingFactory = new state::BuildingFactory();
        state::GameInstance *HQ = buildingFactory->createGI((state::GameInstanceTypeID)6, PLAYER_1_ID);
        state::GameInstance *HQ2 = buildingFactory->createGI((state::GameInstanceTypeID)6, PLAYER_1_ID);
        state::GameInstanceManager *gim_building = new state::GameInstanceManager("GIM_2", 2, PATH_UNITS);

        state::GameInstanceManager *gim_warriors = new state::GameInstanceManager("GIM_1", 3, PATH_UNITS);

        // gim_warriors->add(warrior1);
        // gim_warriors->add(warrior2);
        gim_warriors->add(HQ);
        gim_warriors->add(HQ2);

        // warrior1->assignPosition(0, 0);
        // warrior2->assignPosition(15, 15);
        HQ->assignPosition(1, 1);
        HQ2->assignPosition(9, 17);

        for (int i = 0; i < 10; i++)
        {
            state::GameInstance *w1 = unitfact->createGI((state::GameInstanceTypeID)WARRIOR_DWARF_1, PLAYER_1_ID);
            gim_warriors->add(w1);
            w1->assignPosition(i, 2);

            state::GameInstance *w2 = unitfact->createGI((state::GameInstanceTypeID)WARRIOR_GOLEM_2, PLAYER_2_ID);
            gim_warriors->add(w2);
            w2->assignPosition(i+2, 16);
        }

        // state.addGIM("buildings", gim_building);
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
                state.updateRender = true;

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

                auto sel = std::make_shared<SelectionCommand>(state.getPrevSelect()[1], state.getPrevSelect()[0]);
                engine.addCommand(sel);
                engine.processCommands();

                std::cout << "[MAIN] x : " << state.getPrevSelect()[0] << " y: " << state.getPrevSelect()[1] << std::endl;
                std::cout << "[WARRIOR 1] x : " << warrior1->getPosition()[0] << " y: " << warrior1->getPosition()[0] << std::endl;

                // MOVE
                auto move = std::make_shared<MoveCommand>();
                engine.addCommand(move);
                engine.processCommands();

                // warrior1->assignPosition(state.getPrevSelect()[0], state.getPrevSelect()[1]);
                state.updateRender = true;
                std::cout << "[WARRIOR 1 AFTER] x : " << warrior1->getPosition()[0] << " y: " << warrior1->getPosition()[0] << std::endl;

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