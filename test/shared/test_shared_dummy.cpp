
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Ressources.h"
#include "../../src/shared/state/State.h"
#include "../../src/shared/state/Player.h"
#include "../../src/shared/state/Building.h"
using namespace ::state;
/*
BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(RessourcesTest)
{
  {
    Ressources mana(10);
    BOOST_REQUIRE_EQUAL(ex.x, 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.x, 21);
  }

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
  State st{};
  BOOST_CHECK_EQUAL(st.getTurn(),0);
  st.setTurn(5);
  BOOST_CHECK_EQUAL(st.getTurn(),5);
  st.IncrementTurn();
  BOOST_CHECK_EQUAL(st.getTurn(),6);

  BOOST_CHECK_EQUAL(st.getPlaying(),NO_PLAYER);
  st.setPlaying(PLAYER_1)
  BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_1);
  st.ChangePlaying();
  BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_2);





  ///
  Player value=st.getPlayer();
  


  value.setColor('Red');
  BOOST_CHECK_EQUAL(value.getColor(),'Red');


}

BOOST_AUTO_TEST_CASE(TestBuilding)
{
  Building st{};
  
  BOOST_CHECK_EQUAL(st.getamountMana(),0);
  st.setamountMana(5);
  BOOST_CHECK_EQUAL(st.getamountMana(),5);

  BOOST_CHECK_EQUAL(st.getamountHp(),0);
  st.setamountHp(5);
  BOOST_CHECK_EQUAL(st.getamountHp(),5);
  
  BOOST_CHECK_EQUAL(st.getbuildingID(),0);
  st.setbuildingID(5);
  BOOST_CHECK_EQUAL(st.getbuildingID(),5);

  BOOST_CHECK_EQUAL(st.typeID(),0);
  st.setID(5);
  BOOST_CHECK_EQUAL(st.typeID(),5);

  BOOST_CHECK_EQUAL(st.controler(),0);
  st.setcontroler(5);
  BOOST_CHECK_EQUAL(st.controler(),5);
 }

BOOST_AUTO_TEST_CASE(TestEnvironment)
{
  

  
 }