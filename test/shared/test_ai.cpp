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
  randomAI.GenCommands(engine, state, AI_ID);
  
  engine.processCommands();
  int newXPosition = dwarfAI->getX();
  
}

BOOST_AUTO_TEST_CASE(HeuristicAiTest){
  #define HEURISTIC_ID 1
  #define RANDOM_ID 2
  #define LENGTH 4
  #define HEIGHT 4

  State state;
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
  GameInstanceManager* units = new GameInstanceManager("units", 1);
  GameInstanceManager* buildings = new GameInstanceManager("building", 2);
  state.addGIM("units", units); 
  state.addGIM("buildings", buildings);

}

