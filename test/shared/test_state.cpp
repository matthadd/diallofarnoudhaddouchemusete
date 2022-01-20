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

//TESTS DE GAMEINSTANCE

BOOST_AUTO_TEST_CASE(GameInstance_Constructor1_Test){
  //Test du premier constructeur de GameInstance
  GameInstance gi = GameInstance("a dwarf", DWARF);
  //Vérification des attributs attribués par le constructeur
  BOOST_CHECK_EQUAL(gi.getName(), "a dwarf"); //nom
  BOOST_CHECK_EQUAL(gi.getID(), 0); //ID
  BOOST_CHECK_EQUAL(gi.getTypeID(), DWARF); //type DWARF
  BOOST_CHECK_EQUAL(gi.getX(), 0); //position X
  BOOST_CHECK_EQUAL(gi.getY(), 0); //position Y
}

BOOST_AUTO_TEST_CASE(GameInstance_Constructor2_Test){
  //Test du deuxième constructeur de GameInstance
  GameInstance gi = GameInstance(BAT);
  //Vérification des attributs attribués par le constructeur
  BOOST_CHECK_EQUAL(gi.getID(), 1);//ID
  BOOST_CHECK_EQUAL(gi.getTypeID(), BAT);//type BAT
}


//TEST DE UNITINSTANCE


//TESTS DE STATE
BOOST_AUTO_TEST_CASE(State_findPlayerAllies_Test){
  //Test de la méthode findPlayerAllies de State

  State state;
  UnitInstance unit1 = UnitInstance(BAT, Player1_ID);

  
}

BOOST_AUTO_TEST_CASE(GameInstanceTest)
  {
    GameInstance gi1 ("GI1", (GameInstanceTypeID) 1);
    //BOOST_CHECK_EQUAL(gi1.getID(), 1);
    BOOST_CHECK_EQUAL(gi1.getX(), 0);
    BOOST_CHECK_EQUAL(gi1.getY(), 0);
    BOOST_CHECK_EQUAL(gi1.getName(), "GI1");
    GameInstance gi2 ((GameInstanceTypeID) 1);
    //BOOST_CHECK_EQUAL(gi2.getID(), 2);

    std::vector<int> newPos = {2,3};
    gi1.assignPosition(1,0);
    BOOST_CHECK_EQUAL(gi1.getX(), 1);
    BOOST_CHECK_EQUAL(gi1.getY(), 0);
    gi2.assignPosition(newPos);
    BOOST_CHECK_EQUAL(gi2.getX(), 2);
    BOOST_CHECK_EQUAL(gi2.getY(), 3);

    gi1.select();
    BOOST_CHECK_EQUAL(gi1.isSelected(), true);
    gi1.unselect();
    BOOST_CHECK_EQUAL(gi1.isSelected(), false);

    gi1.setPlayerID(1); 
    BOOST_CHECK_EQUAL(gi1.getPlayerID(), 1);
    gi2.setPlayerID(2);
    BOOST_CHECK_EQUAL(gi2.getPlayerID(), 2);
    
    State stateO;

    GameInstanceManager *ugim = new GameInstanceManager("units", 0);
    BOOST_CHECK_EQUAL(ugim->getID(), 0);
    BOOST_CHECK_EQUAL(ugim->getSize(), 0);
    
    UnitFactory uf;
    UnitInstance *bat1 = (UnitInstance*) uf.createGI(GameInstanceTypeID::BAT, Player1_ID);
    bat1->assignPosition(22,15);
    BOOST_CHECK_EQUAL(bat1->showHP(), 10);

    
    
    stateO.addGIM("units", ugim);
    stateO._GImanagers["units"]->add(bat1);
    BOOST_CHECK_EQUAL(ugim->getSize(), 1);
    ugim->selectObjective(bat1->getPosition());
    BOOST_CHECK_EQUAL(bat1, stateO.getObjective());

    int test_id = stateO.getGI(bat1->getX(), bat1->getY())->getID();
    BOOST_CHECK_EQUAL(test_id, bat1->getID());

    ugim->remove(bat1);
    BOOST_CHECK_EQUAL(ugim->getSize(), 0);


    BOOST_CHECK_EQUAL(stateO.getObjective()->getID(), bat1->getID());
    
  }


BOOST_AUTO_TEST_CASE(UnitFactoryTest_and_checkFunctionTest){
  UnitFactory uf;
  UnitInstance* D1 = (UnitInstance*) uf.createGI(GameInstanceTypeID::DWARF, Player1_ID);
  BOOST_CHECK(D1->isUnit());
  BOOST_CHECK(!D1->isBuilding());
  D1->receiveDamage(D1->showHP());
  BOOST_CHECK(D1->isDead());
}

BOOST_AUTO_TEST_CASE(BuildingFactoryTest){
  BuildingFactory bf;
  BuildingInstance* HQ = (BuildingInstance*) bf.createGI(GameInstanceTypeID::HEADQUARTER, Player1_ID);
  BOOST_CHECK(!HQ->isBeignCaptured());
  HQ->capturing(Player2_ID);
  HQ->addCaptureCounter();
  BOOST_CHECK(HQ->isBeignCaptured());
  HQ->addCaptureCounter();
  BOOST_CHECK(HQ->getPlayerID() == Player2_ID);
  BOOST_CHECK(HQ->isBuilding());
}

BOOST_AUTO_TEST_CASE(CaptureBuildingTest){
  BuildingFactory bf;
  BuildingInstance* HQ = (BuildingInstance*) bf.createGI(GameInstanceTypeID::HEADQUARTER, PLAYER_1);
  UnitFactory uf;
  UnitInstance* D1 = (UnitInstance*) uf.createGI(GameInstanceTypeID::DWARF, PLAYER_2);
  State *state_ptr = new State();
  state_ptr->init();
  auto gim_unit = new GameInstanceManager("units", UNIT_LAYER_ID);
  auto gim_building = new GameInstanceManager("buildings", BUILDING_LAYER_ID);
  state_ptr->addGIM("units", gim_unit);
  state_ptr->addGIM("buildings", gim_building);
  state_ptr->addGI("units",D1);
  state_ptr->addGI("buildings", HQ);

  BOOST_CHECK(!HQ->isBeignCaptured());

  HQ->assignPosition(0,0);
  D1->assignPosition(0,0);

  state_ptr->endTurn();
  state_ptr->endTurn();
  BOOST_CHECK(HQ->wasCaptured());
  
}
