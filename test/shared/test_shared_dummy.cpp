#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"

using namespace ::state;
using namespace ::engine;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(GameInstanceTest)
{
  {
    GameInstance gi1 ("GI1", 1, 1);
    GameInstance gi2 ("GI2", 2, 2);
    BOOST_REQUIRE_EQUAL(gi1.getId(), 1);
    BOOST_REQUIRE_EQUAL(gi2.getId(), 2);
    BOOST_REQUIRE_EQUAL(gi1.getName(), "GI1");
    BOOST_REQUIRE_EQUAL(gi2.getName(), "GI2");
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 0);
    gi1.setPosition(sf::Vector2i (1,0));
    BOOST_REQUIRE_EQUAL(gi1.getPosition().x, 1);
    gi1.setPlayerID(1);
    gi2.setPlayerID(2);
    BOOST_CHECK_EQUAL(gi1.getPlayerID(), 1);
    BOOST_CHECK_EQUAL(gi2.getPlayerID(), 2);
  }
}
/*
  {
    Exemple ex {};
    ex.setX(21);
    BOOST_CHECK_LE(ex.x, 32); // Less than equal
    BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}
*/
/* vim: set sw=2 sts=2 et : */

BOOST_AUTO_TEST_CASE(TestStateEngine)
{
  State state;

  GameInstance *dwarf1 = new GameInstance("Dwarf_1", 1, 8);
  dwarf1->setPosition(sf::Vector2i(12,15));
  BOOST_REQUIRE_EQUAL(dwarf1->getPosition().y, 15);
  dwarf1->setPlayerID(1);

  GameInstance *dwarf2 = new GameInstance("Dwarf_2", 2, 8);
  dwarf2->setPosition(sf::Vector2i(12,16));
  BOOST_REQUIRE_EQUAL(dwarf2->getPosition().x, 12);
  dwarf2->setPlayerID(2);

  GameInstance *dwarf3 = new GameInstance("Dwarf_3", 3, 8);
  dwarf3->setPosition(sf::Vector2i(12,17));
  BOOST_REQUIRE_EQUAL(dwarf2->getPlayerID(), 2);
  dwarf3->setPlayerID(2);

  GameInstanceManager *unitGI = new GameInstanceManager("Unit's Manager", 1);
  unitGI->add(dwarf1);
  unitGI->add(dwarf2);
  unitGI->add(dwarf3);

  state._GImanagers.push_back(unitGI);

  Engine engine(state);

  std::shared_ptr<SelectionCommand> selecDwarf1 = std::make_shared<SelectionCommand>(12, 15);
  auto selecDwarf1Eff = selecDwarf1;
  std::shared_ptr<MoveCommand> moveDwarf1 = std::make_shared<MoveCommand>(13, 15, dwarf1->getId());
  engine.addCommand(selecDwarf1Eff);
  engine.addCommand(moveDwarf1);
  engine.processCommands();

  state = engine.getState();

  BOOST_REQUIRE_EQUAL(dwarf1->getPosition().x, 13);
  //BOOST_REQUIRE_EQUAL(dwarf1->getPosition().y, 15);

}

/*

// tests state::GameInstance(std::string name, int id)
    state::GameInstance* warrior1 = new state::GameInstance("warrior1",1,1);
    cout << "Resource loaded" << endl;  

    sf::Vector2i pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;

    // test void state::GameInstance::setPosition(sf::Vector2i v)
    warrior1->setPosition(sf::Vector2i(0,1));
    pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;
    
    // tests void state::GameInstance::setPosition(int x, int y)
    warrior1->setPosition(1,1);
    pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;


    // tests state::GameInstanceManager::GameInstanceManager (std::string name, int id)
    state::GameInstanceManager* gim = new state::GameInstanceManager("GIM_0", 0);


    // test void state::GameInstanceManager::add(state::GameInstance* gameInstance)
    gim->add(warrior1);
    
    // tests void state::GameInstanceManager::getArrayFromElements(int* array, int sizeMap)
    int sizeMap = 32*32;
    int array[sizeMap] = {0}; // or whatever is the default value
    for (int k = 0; k < sizeMap; k++)
    {
        cout << "array[" << k <<"] = "<< array[k] << endl;
    }
    gim->getArrayFromElementsIP(array, sizeMap);
    for (int k = 0; k< 100; k++)
    {
        cout << "array[" << k <<"] = "<< array[k] << endl;
    }
.*/