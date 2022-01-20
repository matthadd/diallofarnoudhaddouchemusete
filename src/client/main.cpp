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
        state::UnitInstance* AIunit = new UnitInstance(DWARF, AI_ID);
        state::UnitInstance* OtherUnit = new UnitInstance(BAT, Player_ID);
        AIunit->setPlayerID(AI_ID);

        ai::RandomAI randomAI;
        
        //Initialisation d'un état du jeu
        state::Player* ai = new Player("ai", "blue", 0);
        ai->setID(AI_ID);

        state.Players.push_back(ai);

        AIunit->assignPosition(10,10);
        OtherUnit->assignPosition(24,24);


        state::GameInstanceManager* unitGIM = new GameInstanceManager("Units' Manager", 2);
        unitGIM->add(AIunit);
        unitGIM->add(OtherUnit);
        state.addGIM("units", unitGIM);

        //Création du moteur du jeu 
        engine::Engine engine(&state);

        //Génération des commandes de l'IA aléatoire
        state.selectObjective(OtherUnit->getPosition());
        randomAI.GenCommands(engine, &state, ai->getID());
        randomAI.run(engine);

        cout<< "La nouvelle position de l'unité est (" << AIunit->getX() 
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

    
        // tests state::GameInstance(std::string name, int id)
        state::GameInstance *warrior1 = new state::GameInstance("warrior1", (state::GameInstanceTypeID)129);
        cout << "Resource loaded" << endl;

        std::vector<int> pos = warrior1->getPosition();
        cout << "x:" << pos[0] << " y:" << pos[1] << endl;

        // test void state::GameInstance::setPosition(sf::Vector2i v)
        warrior1->assignPosition(0, 1);
        pos = warrior1->getPosition();
        cout << "x:" << pos[0] << " y:" << pos[1] << endl;

        // tests void state::GameInstance::setPosition(int x, int y)
        warrior1->assignPosition(15, 0);
        pos = warrior1->getPosition();
        cout << "x:" << pos[0] << " y:" << pos[1] << endl;

        // tests state::GameInstanceManager::GameInstanceManager (std::string name, int id)
        state::GameInstanceManager *gim = new state::GameInstanceManager("GIM_1", 3, "res/Tileset/png/Unit_Map_(32).png"); // unit

        // test void state::GameInstanceManager::add(state::GameInstance* gameInstance)
        gim->add(warrior1);

        // tests void state::GameInstanceManager::getArrayFromElements(int* array, int sizeMap)
        int sizeMap = 16 * 16;
        int array[sizeMap] = {0}; // or whatever is the default value
        gim->getArrayFromElementsIP(array, sizeMap);

        // Process to create Unit and add it to GIM
        state::GameInstance *warrior2 = new state::GameInstance("warrior2", (state::GameInstanceTypeID)129);
        warrior2->assignPosition(2, 2);
        gim->add(warrior2);

        // Process to add GIM to Layer
        int warriors_arr[sizeMap] = {0};
        // for (int i = 0; i < sizeMap; i++){ warriors_arr[i] = 0;}
        gim->getArrayFromElementsIP(warriors_arr, sizeMap);

        // tests render::Layer construct
        render::Layer l;

        // tests render::Layer(args) construct
        render::Layer warrior_layer(0, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16);

        // test instance state
        state::State state;

        // test instance state with args
        render::Scene s(render::MENU, state, 32, 32, "title");

        // tests int Scene::render(int* warriors_arr)
        // s.render(warriors_arr);

        // tests int Scene::render2(int* arr)
        int background_arr[32 * 32] = {0};
        render::Layer background_l(0, "res/Tileset/png/Static_Global_Tileset_(32).png", sf::Vector2u(32, 32), background_arr, 16, 16);
        render::Layer warrior_l(1, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16);
        s.add(background_l);
        s.add(warrior_l);

        std::thread t(&render::Scene::render2, &s);
        printf("------------------------------\n");
        int i = 0;
        while (1)
        {
            printf("[MAIN] add start\n");

            // update new positions with engine
            warrior1->assignPosition(4, i%16);
            i += 1;
            gim->getArrayFromElementsIP(warriors_arr, sizeMap);

            // add map and other layers
            s.add(background_l);
            s.add(render::Layer(1, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16));

            printf("[MAIN] add end\n");
            s.updateLayout = true;
            sleep(2);

            warriors_arr[0] = 0;
        }
        // test state::GameInstanceManager::GameInstanceManager (std::string name, int id)
        // test reference to own GIM
        state::GameInstanceManager *gim2 = new state::GameInstanceManager("GIM_0", 3, ""); // unit

        for (state::GameInstanceManager *g : gim->_GameManagers)
        {
            cout << g->getSize() << endl;
        }
        t.join();
    }

    return 0;
}