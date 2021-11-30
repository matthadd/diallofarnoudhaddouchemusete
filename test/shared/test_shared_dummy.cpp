#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace ::state;

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
    BOOST_REQUIRE_EQUAL(gi1.getPlayerID(), gi2.getPlayerID());
    /*
    gi1.setPlayerID(1);
    gi2.setPlayerID(2);
    BOOST_CHECK_EQUAL(gi1.getPlayerID(), 1);
    BOOST_CHECK_EQUAL(gi2.getPlayerID(), 2);
    */
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

BOOST_AUTO_TEST_CASE(TestState)
{
  /*BOOST_CHECK_EQUAL(State::turn,0);
  State::turn += 10;
  BOOST_CHECK_EQUAL(State::turn,10);*/
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