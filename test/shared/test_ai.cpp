#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/state/UnitFactory.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include <memory>
#include <iostream>

using namespace state;
using namespace engine;
using namespace ai;

#define Player1_ID 1
#define Player2_ID 2
#define UNIT_LAYER_ID  2
#define BUILDING_LAYER_ID  1

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TetsAiEngine){
  
  #define Player_ID 1
  #define AI_ID 2
 
  //Initialisation d'un état du jeu
  State state;
  Player* player = new Player("player", "red", Player1_ID);
  Player* ai = new Player("ai", "blue" ,AI_ID);

  player->credit(200);
  ai->credit(200);

  state.Players.push_back(player);
  state.Players.push_back(ai);

  GameInstance *dwarfPlayer = new GameInstance("Dwarf_Player", GameInstanceTypeID::DWARF);
  dwarfPlayer->assignPosition(12,15);
  dwarfPlayer->setPlayerID(Player_ID);

  GameInstance *dwarfAI = new GameInstance("Dwarf_AI", GameInstanceTypeID::DWARF);
  dwarfAI->assignPosition(12,16);
  int initialXPosition = dwarfAI->getX();
  dwarfAI->setPlayerID(AI_ID);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", UNIT_LAYER_ID);
  state.addGIM("units",unitGIM);
  unitGIM->add(dwarfPlayer);
  unitGIM->add(dwarfAI);

  //state.addGIM("units",unitGIM);

  //Création du moteur du jeu et instanciation de l'ia
  Engine engine(&state);
  RandomAI randomAI(16,16);

  //Génération des commandes de l'IA aléatoire
  randomAI.GenCommands(engine, &state, AI_ID);
  
  engine.processCommands();
  int newXPosition = dwarfAI->getX();
  
}

BOOST_AUTO_TEST_CASE(HeuristicAiTest){
  #define HEURISTIC_ID 1
  #define RANDOM_ID 2
  #define LENGTH 4
  #define HEIGHT 4
  int winCounter_H = 0;
  int winCounter_R = 0;
  int nb_turn = 100;

  for(int j = 0; j<nb_turn; j++){
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
    state.addGIM("units", new GameInstanceManager("units", UNIT_LAYER_ID)); 
    state.addGIM("buildings", new GameInstanceManager("building", BUILDING_LAYER_ID));

    //mise en place des quartiers généraux
    BuildingFactory bf;
    auto hqH = (BuildingInstance*) bf.createGI(HEADQUARTER, HEURISTIC_ID);
    auto hqR = (BuildingInstance*) bf.createGI(HEADQUARTER, RANDOM_ID);

    hqH->assignPosition(0,3);
    hqR->assignPosition(3,0);
    state.addGI("buildings",hqH);
    state.addGI("buildings",hqR);

    //mise en place des unités

    UnitFactory uf;
    auto batH = (UnitInstance*) uf.createGI(DWARF, HEURISTIC_ID);
    auto batR = (BuildingInstance*) uf.createGI(DWARF, RANDOM_ID);
    batH->assignPosition(0,2);
    batR->assignPosition(2,1);
    state.addGI("units",batH);
    state.addGI("units",batR);

    Engine engine(&state);
    int i=0;
    while(state.playing != END_GAME)
    {
      i++;
      std::cout<< "HEURISTIC TURN\n"<<std::endl;
      std::cout<< "turn : " << state.turn <<std::endl;
      heuristicAi.GenCommands(engine, &state, HEURISTIC_ID);
      heuristicAi.run(engine);
      std::cout << "batH is at : (" << batH->getX() << "," << batH->getY() << ")\n" << std::endl; 
      
      std::cout<< "RANDOM TURN\n"<<std::endl;
      std::cout<< "turn : " << state.turn <<std::endl;
      randomAi.GenCommands(engine, &state, RANDOM_ID); 
      randomAi.run(engine);
      std::cout << "batR is at : (" << batR->getX() << "," << batR->getY() << ")\n" << std::endl;

      if(hqR->wasCaptured()){
        state.winner = (Playing) hqR->getPlayerID();
        state.playing=END_GAME;
      }
      else if(hqH->wasCaptured()){
        state.winner = (Playing) hqH->getPlayerID();
        state.playing=END_GAME;
      }

      if(state.winner == PLAYER_1)
        winCounter_H++;
      else if(state.winner == PLAYER_2)
        winCounter_R++; 
      if(i>100) break;
      
    }
  }
  std::cout << "heuristic win rate : " << (double) 100*winCounter_H/nb_turn << "%" << std::endl;
  std::cout << "random win rate : " << (double) 100*winCounter_R/nb_turn << "%" <<std::endl;
  
}

