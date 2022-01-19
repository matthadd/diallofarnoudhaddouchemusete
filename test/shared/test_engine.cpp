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

BOOST_AUTO_TEST_CASE(TestStateEngine)
{
  State state;
  state.init();

  //création dest joueurs 
  Player p1("player 1","red");
  p1.setID(1);
  Player p2("player 2","blues");
  p2.setName("Player_2");
  BOOST_CHECK_EQUAL(p2.getName(), "Player_2");
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
  GameInstanceManager *buildingGIM = new GameInstanceManager("Building's Manager", 2, ""); // macro BUILDING_LAYER_ID
  GameInstance *HQ1 = new GameInstance("HeadQuarter", GameInstanceTypeID::HEADQUARTER);
  HQ1->setPlayerID(1);
  HQ1->assignPosition(3,3);
  buildingGIM->add(HQ1);

  GameInstanceManager *unitGIM = new GameInstanceManager("Unit's Manager", 3, ""); //macro UNIT_LAYER_ID
  unitGIM->add(dwarf1);
  unitGIM->add(dwarf2);

  state.addGIM("buildings", buildingGIM);
  state.addGIM("units", unitGIM);

  BOOST_CHECK_EQUAL(state._GImanagers.size(), 2);

  state.addGI("units", dwarf3);

  BOOST_CHECK_EQUAL(unitGIM->getGameInstances().size(), 3);

  //Partie engine
  Engine engine(&state);
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

  //test de fin de jeu
  //BOOST_CHECK_EQUAL(state.isOver, false);
  //BOOST_CHECK_EQUAL(state.WinnerID(), -1); //la méthode retourne -1 si persnne n'a gagné

}

BOOST_AUTO_TEST_CASE(AttackCommandTest){
  State state;
  UnitFactory uf;
  GameInstanceManager* units = new GameInstanceManager("units", UNIT_LAYER_ID);
  state.addGIM("units", units); 
  //création des unités et assignement des positions
  UnitInstance* bat = (UnitInstance*) uf.createGI(BAT, Player1_ID);
  bat->assignPosition(0,0);
  state.addGI("units", bat);
  UnitInstance* cyclop = (UnitInstance*) uf.createGI(CYCLOPS, Player2_ID);
  cyclop->assignPosition(0,1);
  state.addGI("units", cyclop);
  //sélection de la cible et de la source
  state.selectSource(cyclop->getPosition());
  state.selectObjective(bat->getPosition());
  //vérification de la taille du GIM des unités
  BOOST_CHECK(bat->isDead()==false);
  
  //gestion de la commande
  Engine engine(&state);
  engine.addCommand(std::make_shared<AttackCommand>());
  engine.processCommands();
  //vérification de la mort du bat
  BOOST_CHECK(bat->isDead()==true);
  BOOST_CHECK(units->getGameInstances().size() == 1);
}

BOOST_AUTO_TEST_CASE(MoveCommandTest)
{
  //création du state
  State *state_ptr = new State();

  //création du bâtiment
  BuildingFactory bf;
  BuildingInstance* HQ = (BuildingInstance*) bf.createGI(HEADQUARTER, PLAYER_1);
  state_ptr->addGIM("buildings", new GameInstanceManager("buildings", BUILDING_LAYER_ID));
  HQ->assignPosition(2,0);

  //création des unités
  UnitFactory uf;
  state_ptr->addGIM("units", new GameInstanceManager("units", UNIT_LAYER_ID));
  GameInstance* dwarf = uf.createGI(DWARF,PLAYER_1);
  dwarf->assignPosition(0,0);
  state_ptr->addGI("units", dwarf);
  UnitInstance* cyclop = (UnitInstance*) uf.createGI(CYCLOPS,PLAYER_2);
  cyclop->assignPosition(1,0);
  state_ptr->addGI("units", cyclop);

  //création des commandes
  Engine engine(state_ptr);
  std::shared_ptr<SelectionCommand> s1(new SelectionCommand(cyclop->getX(), cyclop->getY()));
  std::shared_ptr<MoveCommand> mv1(new MoveCommand(dwarf->getX(), dwarf->getY()));

  //test du conflit de deux unité sur la même case
  engine.addCommand(s1);
  engine.addCommand(mv1);
  engine.processCommands();
  BOOST_CHECK(cyclop == state_ptr->getSource());
  BOOST_CHECK_EQUAL(cyclop->getX(),1);

  //test avec un bâtiment
  std::shared_ptr<MoveCommand> mv2(new MoveCommand(HQ->getX(), HQ->getY()));
  engine.addCommand(mv2);
  engine.processCommands();
  BOOST_CHECK_EQUAL(cyclop->getX(),2);
}

BOOST_AUTO_TEST_CASE(EndTurnTest){
  State *state_ptr = new State();
  state_ptr->init();
  Player p1("player 1","red");
  p1.setID((int) PLAYER_1);
  Player p2("player 2","blues");
  p2.setID((int) PLAYER_2);
  state_ptr->Players.push_back(&p1);
  state_ptr->Players.push_back(&p2);

  BOOST_CHECK_EQUAL(state_ptr->whoIsPlaying(), PLAYER_1);
  BOOST_CHECK_EQUAL(state_ptr->showTurnNumber(), 0);
  
  Engine e(state_ptr);
  //the player 2 cannot use this command
  std::shared_ptr<EndTurnCommand> et2(new EndTurnCommand(PLAYER_2));
  e.addCommand(et2);
  e.processCommands();
  //testing the command with player 1
  BOOST_CHECK_EQUAL(state_ptr->whoIsPlaying(), PLAYER_1);
  std::shared_ptr<EndTurnCommand> et1(new EndTurnCommand(PLAYER_1));
  e.addCommand(et1);
  //BOOST_CHECK_NO_THROW(et->process(&state));
  BOOST_CHECK_NO_THROW(e.processCommands());
  BOOST_CHECK_EQUAL(state_ptr->showTurnNumber(), 1);
}


