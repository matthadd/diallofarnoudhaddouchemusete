
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}
/*
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
  
  //st.ChangePlaying();
  //BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_2);
  
  ///
  Player p1 = st.getPlayer(1);
  p1.setColor("Red");
  BOOST_CHECK_EQUAL(p1.getColor(),"Red");
}

BOOST_AUTO_TEST_CASE(TestEnvironment)
{
    Environment st{};
  
    //BOOST_CHECK_EQUAL(st.getTypeID(),0);
    //st.setTypeID(5);
    //BOOST_CHECK_EQUAL(st.getTypeID(),5);

  
 }



 BOOST_AUTO_TEST_CASE(TestPosition)
{
    Position st{};
    // tests setters getters
    BOOST_CHECK_EQUAL(st.getX(),0);
    st.setX(10);
    BOOST_CHECK_EQUAL(st.getX(),10);

    BOOST_CHECK_EQUAL(st.getY(),0);
    st.setY(10);
    BOOST_CHECK_EQUAL(st.getY(),10);

  //test move( X et Y sont initalement a 10 ici)
    st.move(2,3);
    BOOST_CHECK_EQUAL(st.getX(),12);
    BOOST_CHECK_EQUAL(st.getY(),13);
  //test changePlace
    //on fixe X et Y à 10
    st.setY(10);
    st.setX(10);

    st.changePlace(8,4);
    BOOST_CHECK_EQUAL(st.getX(),8);
    BOOST_CHECK_EQUAL(st.getY(),4);



  
 }

  BOOST_AUTO_TEST_CASE(TestBuilding)
{
    Building st{};
    // tests setters getters
    BOOST_CHECK_EQUAL(st.getAmountMana(),0);
    st.setAmountMana(10);
    BOOST_CHECK_EQUAL(st.getAmountMana(),10);

    BOOST_CHECK_EQUAL(st.getAmountHP(),0);
    st.setAmountHP(10);
    BOOST_CHECK_EQUAL(st.getAmountHP(),10);

    BOOST_CHECK_EQUAL(st.getBuildingID(),0);
    st.setBuildingID(8);
    BOOST_CHECK_EQUAL(st.getBuildingID(),8);

    BOOST_CHECK_EQUAL(st.getTypeID(),"");
    st.setTypeID("type1");
    BOOST_CHECK_EQUAL(st.getTypeID(),"type1");

    BOOST_CHECK_EQUAL(st.getControler(),0);
    st.setControler(1);
    BOOST_CHECK_EQUAL(st.getControler(),1);

    Position p = st.getPosition();
    BOOST_CHECK_EQUAL(p.getX(),0);
    Position position2(2,8) ;
    st.setPosition(position2);
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
  
 }

 

   BOOST_AUTO_TEST_CASE(TestPlayer)
{
    Player st{};
     //tests setters getters
    BOOST_CHECK_EQUAL(st.getColor(),"");
    st.setColor("Red");
    BOOST_CHECK_EQUAL(st.getColor(),"Red");

    BOOST_CHECK_EQUAL(st.getName(),"");
    st.setName("test");
    BOOST_CHECK_EQUAL(st.getName(),"test");

    BOOST_CHECK_EQUAL(st.getStatus(),WAIT);
    st.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(st.getStatus(),PLAYING);

    //Unit u= st.getUnit();
    //BOOST_CHECK_EQUAL(u.getSingleUnitHP(),0);


    ///Building b1());




  
 }