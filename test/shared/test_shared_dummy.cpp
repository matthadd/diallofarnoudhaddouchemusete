
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

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
  st.setPlaying(PLAYER_1);
  BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_1);
  /*
  st.ChangePlaying();
  BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_2);
  */
  ///
  Player p1 = st.getPlayer(1);
  p1.setColor("Red");
  BOOST_CHECK_EQUAL(p1.getColor(),"Red");
}

BOOST_AUTO_TEST_CASE(TestBuilding)
{
  Building st{};
  
  BOOST_CHECK_EQUAL(st.getAmountMana(),0);
  st.setAmountMana(5);
  BOOST_CHECK_EQUAL(st.getAmountMana(),5);
 }

BOOST_AUTO_TEST_CASE(TestEnvironment)
{
    Environment st{};
  
    BOOST_CHECK_EQUAL(st.getTypeID(),0);
    st.setTypeID(5);
    BOOST_CHECK_EQUAL(st.getTypeID(),5);

  
 }

BOOST_AUTO_TEST_CASE(TestPlayer)
{
    Player st{};
  
    BOOST_CHECK_EQUAL(st.getColor(),"");
    st.setColor("YELLOW");
    BOOST_CHECK_EQUAL(st.getColor(),"YELLOW");

    BOOST_CHECK_EQUAL(st.getName(),"");
    st.setName("Name");
    BOOST_CHECK_EQUAL(st.getName(),"Name");

    BOOST_CHECK_EQUAL(st.getStatus(),WAIT);
    st.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(st.getStatus(),PLAYING);
  
 }