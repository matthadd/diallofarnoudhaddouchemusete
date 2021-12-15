#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"


using namespace ::state;
using namespace ::engine;
using namespace ::ai;

#define Player1_ID 1
#define Player2_ID 2
#define UNIT_LAYER_ID (state::GIMTypeID) 2
#define BUILDING_LAYER_ID (state::GIMTypeID) 1

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameInstanceTest)
{
  {
    GameInstance gi1 ("GI1", (GameInstanceTypeID) 1);
    GameInstance gi2 ("GI2", (GameInstanceTypeID) 1);
    BOOST_REQUIRE_EQUAL(gi1.getID(), 1);
    BOOST_REQUIRE_EQUAL(gi2.getID(), 2);
    BOOST_REQUIRE_EQUAL(gi1.getName(), "GI1");
    BOOST_REQUIRE_EQUAL(gi2.getName(), "GI2");
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 0);
    gi1.setPosition(sf::Vector2i (1,0));
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 1);
    gi1.setPlayerID(1);
    gi2.setPlayerID(2);
    BOOST_CHECK_EQUAL(gi1.getPlayerID(), 1);
    BOOST_CHECK_EQUAL(gi2.getPlayerID(), 2);

    //UnitInstance dwarf1 (3,GameInstanceTypeID::DWARF,Player1_ID);
    //BOOST_CHECK_EQUAL(dwarf1.showHP(), 5);
  }
}


BOOST_AUTO_TEST_CASE(TestStateEngine)
{
  State state;

  //création des unités
  GameInstance *dwarf1 = new GameInstance("Dwarf_1", GameInstanceTypeID::DWARF);
  dwarf1->setPosition(sf::Vector2i(12,15));
  BOOST_REQUIRE_EQUAL(dwarf1->getID(), 3);
  dwarf1->setPlayerID(1);

  GameInstance *dwarf2 = new GameInstance("Dwarf_2", GameInstanceTypeID::DWARF);
  dwarf2->setPosition(sf::Vector2i(12,16));
  BOOST_REQUIRE_EQUAL(dwarf2->getPosition().x, 12);
  dwarf2->setPlayerID(2);

  GameInstance *dwarf3 = new GameInstance("Dwarf_3", GameInstanceTypeID::DWARF);
  dwarf3->setPosition(sf::Vector2i(12,17));
  BOOST_REQUIRE_EQUAL(dwarf2->getPlayerID(), 2);
  dwarf3->setPlayerID(2);

  //création du bâtiment
  GameInstanceManager *buildingGIM = new GameInstanceManager("Building's Manager", BUILDING_LAYER_ID);
  GameInstance *HQ1 = new GameInstance("HeadQuarter", GameInstanceTypeID::HEADQUARTER);
  HQ1->setPlayerID(1);
  HQ1->setPosition(3,3);
  buildingGIM->add(HQ1);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", UNIT_LAYER_ID);
  unitGIM->add(dwarf1);
  unitGIM->add(dwarf2);
  unitGIM->add(dwarf3);

  state._GImanagers.push_back(buildingGIM);
  state._GImanagers.push_back(unitGIM);

  //Partie engine
  Engine engine(state);

  auto selecDwarf1 = std::make_shared<SelectionCommand>(12, 15);
  auto moveDwarf1 = std::make_shared<MoveCommand>(13, 15);
  auto selecbuild = std::make_shared<SelectionCommand>(3, 3);
  auto buildCylop1 = std::make_shared<BuildUnitCommand>(HQ1->getID(), (GameInstanceTypeID) 10);
  engine.addCommand(selecDwarf1);
  engine.addCommand(moveDwarf1);
  engine.addCommand(buildCylop1);
  engine.processCommands();

  state = engine.getState();

  BOOST_REQUIRE_EQUAL(unitGIM->getGameInstances().size(), 4);

  BOOST_REQUIRE_EQUAL(dwarf1->getPosition().x, 13);

  std::cout << "test sur les types des GameInstance, \n BAT = "  << (int) GameInstanceTypeID::BAT << "\n" << std::endl;

}

BOOST_AUTO_TEST_CASE(TetsAiEngine){
  
  #define Player_ID 1
  #define AI_ID 2
  
  //Initialisation d'un état du jeu
  State state;

  GameInstance *dwarfPlayer = new GameInstance("Dwarf_Player", GameInstanceTypeID::DWARF);
  dwarfPlayer->initIDCounter();
  dwarfPlayer->setPosition(sf::Vector2i(12,15));
  dwarfPlayer->setPlayerID(Player_ID);

  GameInstance *dwarfAI = new GameInstance("Dwarf_AI", GameInstanceTypeID::DWARF);
  dwarfAI->setPosition(sf::Vector2i(12,16));
  int initialXPosition = dwarfAI->getPosition().x;
  dwarfAI->setPlayerID(AI_ID);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", UNIT_LAYER_ID);
  unitGIM->add(dwarfPlayer);
  unitGIM->add(dwarfAI);

  state._GImanagers.push_back(unitGIM);

  //Création du moteur du jeu et instanciation de l'ia
  Engine engine(state);
  RandomAI randomAI;

  //Génération des commandes de l'IA aléatoire
  randomAI.GenCommands(engine, state, AI_ID);
  
  engine.processCommands();
  state = engine.getState();
  int newXPosition = dwarfAI->getPosition().x;
  
  
  BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (initialXPosition) (newXPosition));
  BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (dwarfAI->getID()) (dwarfPlayer->getID()));
  
}

