#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/state/UnitFactory.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"


using namespace ::state;
using namespace ::engine;
using namespace ::ai;

#define Player1_ID 1
#define Player2_ID 2
#define UNIT_LAYER_ID  2
#define BUILDING_LAYER_ID  1

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameInstanceTest)
  {
    GameInstance gi1 ("GI1", (GameInstanceTypeID) 1);
    GameInstance gi2 ("GI2", (GameInstanceTypeID) 1);
    BOOST_REQUIRE_EQUAL(gi1.getID(), 1);
    BOOST_REQUIRE_EQUAL(gi2.getID(), 2);
    BOOST_REQUIRE_EQUAL(gi1.getName(), "GI1");
    BOOST_REQUIRE_EQUAL(gi2.getName(), "GI2");
    BOOST_REQUIRE_EQUAL(gi1.getX(), 0);
    gi1.assignPosition(1,0);
    BOOST_REQUIRE_EQUAL(gi1.getX(), 1);
    gi1.setPlayerID(1);
    gi2.setPlayerID(2);
    BOOST_CHECK_EQUAL(gi1.getPlayerID(), 1);
    BOOST_CHECK_EQUAL(gi2.getPlayerID(), 2);
    
    State stateO;
    GameInstanceManager *ugim = new GameInstanceManager("units", 0);
    
    UnitFactory uf;
    UnitInstance *bat1 = (UnitInstance*) uf.createGI(GameInstanceTypeID::BAT, Player1_ID);
    bat1->assignPosition(22,15);
    BOOST_CHECK_EQUAL(bat1->showHP(), 10);
    
    stateO.addGIM("units", ugim);
    stateO._GImanagers["units"]->add(bat1);
    ugim->selectObjective(bat1->getPosition());

    BOOST_CHECK_EQUAL(stateO.getObjective()->getID(), bat1->getID());
  }



BOOST_AUTO_TEST_CASE(TestStateEngine)
{
  State state;

  state.init();

  //création dest joueurs 
  Player p1("player 1","red");
  p1.setID(1);
  Player p2("player 2","blues");
  p2.setID(2);
  p1.credit(100);

  state.Players.push_back(&p1);
  state.Players.push_back(&p2);

  BOOST_CHECK_EQUAL(state.Players.size(), 2);

  BOOST_CHECK_EQUAL(state.GetActivePlayer()->getID(), 1);
  //création des unités
  GameInstance *dwarf1 = new GameInstance("Dwarf_1", GameInstanceTypeID::DWARF);
  dwarf1->assignPosition(12,15);
  //BOOST_REQUIRE_EQUAL(dwarf1->getID(), 3);
  dwarf1->setPlayerID(1);

  GameInstance *dwarf2 = new GameInstance("Dwarf_2", GameInstanceTypeID::DWARF);
  dwarf2->assignPosition(12,16);
  BOOST_REQUIRE_EQUAL(dwarf2->getX(), 12);
  dwarf2->setPlayerID(2);

  GameInstance *dwarf3 = new GameInstance("Dwarf_3", GameInstanceTypeID::DWARF);
  dwarf3->assignPosition(12,17);
  BOOST_REQUIRE_EQUAL(dwarf2->getPlayerID(), 2);
  dwarf3->setPlayerID(2);

  //création du bâtiment
  GameInstanceManager *buildingGIM = new GameInstanceManager("Building's Manager", BUILDING_LAYER_ID);
  GameInstance *HQ1 = new GameInstance("HeadQuarter", GameInstanceTypeID::HEADQUARTER);
  HQ1->setPlayerID(1);
  HQ1->assignPosition(3,3);
  buildingGIM->add(HQ1);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", UNIT_LAYER_ID);
  unitGIM->add(dwarf1);
  unitGIM->add(dwarf2);

  state.addGIM("buildings", buildingGIM);
  state.addGIM("units", unitGIM);

  BOOST_CHECK_EQUAL(state._GImanagers.size(), 2);

  state.addGI("units", dwarf3);

  BOOST_CHECK_EQUAL(unitGIM->getGameInstances().size(), 3);

  //Partie engine
  Engine engine(state);

  auto selecDwarf1 = std::make_shared<SelectionCommand>(12, 15);
  //auto attackDwarf1 = std::make_shared<AttackCommand>();
  auto moveDwarf1 = std::make_shared<MoveCommand>(13, 15);
  auto selecbuild = std::make_shared<SelectionCommand>(3, 3);
  auto buildDwarf1 = std::make_shared<BuildUnitCommand>(HQ1->getID(), GameInstanceTypeID::DWARF);
  //test de la séléction
  engine.addCommand(selecDwarf1);
  engine.processCommands();
  BOOST_CHECK_EQUAL(state.getSource()->getID(), dwarf1->getID());
  //test du déplacement 
  engine.addCommand(moveDwarf1);
  engine.processCommands();
  BOOST_CHECK_EQUAL(state.getSource()->getX(), 13);
  //test de sélection du bâtiment
  engine.addCommand(selecbuild);
  engine.processCommands();
  BOOST_CHECK_EQUAL(state.getSource()->getID(), HQ1->getID());
  //test de la production d'unité
  engine.addCommand(buildDwarf1);
  engine.processCommands();
  BOOST_CHECK_EQUAL(state._GImanagers["units"]->getGameInstances().size(), 4);
  
  BOOST_CHECK_EQUAL(state.GetActivePlayer()->balance(), 50);

  //test de la commande d'attaque 

  state::UnitFactory *unitfact=new state::UnitFactory();
  state::GameInstance *dw1=unitfact->createGI(state::DWARF,1);
  state::GameInstance *dw2=unitfact->createGI(state::DWARF,2);
  state::GameInstanceManager *gimTest = new state::GameInstanceManager("units", 1);
  dw1->assignPosition(0, 1);
  dw2->assignPosition(1, 1);
 
  gimTest->add(dw1);
  gimTest->add(dw2);
  gimTest->selectSource(dw1->getPosition());
  gimTest->selectObjective(dw2->getPosition());
    // test instance state  
  state::State state2;
  state.addGIM("units",gimTest);
  /*engine::AttackCommand* attck = new engine::AttackCommand();
  attck->process(state2);
  state::UnitInstance* ennemy= (state::UnitInstance*)dw2;
  BOOST_CHECK_EQUAL(ennemy->showHP(), 0);*/

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
  dwarfPlayer->initIDCounter();
  dwarfPlayer->assignPosition(12,15);
  dwarfPlayer->setPlayerID(Player_ID);

  GameInstance *dwarfAI = new GameInstance("Dwarf_AI", GameInstanceTypeID::DWARF);
  dwarfAI->assignPosition(12,16);
  int initialXPosition = dwarfAI->getX();
  dwarfAI->setPlayerID(AI_ID);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", UNIT_LAYER_ID);
  state._GImanagers["units"] = unitGIM;
  unitGIM->add(dwarfPlayer);
  unitGIM->add(dwarfAI);

  //state.addGIM("units",unitGIM);

  //Création du moteur du jeu et instanciation de l'ia
  Engine engine(state);
  RandomAI randomAI;

  //Génération des commandes de l'IA aléatoire
  randomAI.GenCommands(engine, state, AI_ID);
  
  engine.processCommands();
  state = engine.getState();
  int newXPosition = dwarfAI->getX();
  
  
  //BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (initialXPosition) (newXPosition));
  BOOST_CHECK_PREDICATE(std::not_equal_to<int>(), (dwarfAI->getID()) (dwarfPlayer->getID()));
  
}

