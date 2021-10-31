
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
  State state{};
  BOOST_CHECK_EQUAL(state.getTurn(),0);
  state.setTurn(5);
  BOOST_CHECK_EQUAL(state.getTurn(),5);
  state.IncrementTurn();
  BOOST_CHECK_EQUAL(state.getTurn(),6);

  BOOST_CHECK_EQUAL(state.getPlaying(),NO_PLAYER);
  state.setPlaying(PLAYER_1);
  BOOST_CHECK_EQUAL(state.getPlaying(),PLAYER_1);
  
  //st.ChangePlaying();
  //BOOST_CHECK_EQUAL(st.getPlaying(),PLAYER_2);
  
  ///
  Player player_1 = state.getPlayer(1);
  player_1.setColor("Red");
  BOOST_CHECK_EQUAL(player_1.getColor(),"Red");
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
    Position position{};
    // tests setters getters
    BOOST_CHECK_EQUAL(position.getX(),0);
    position.setX(10);
    BOOST_CHECK_EQUAL(position.getX(),10);

    BOOST_CHECK_EQUAL(position.getY(),0);
    position.setY(10);
    BOOST_CHECK_EQUAL(position.getY(),10);

  //test move( X et Y sont initalement a 10 ici)
    position.move(2,3);
    BOOST_CHECK_EQUAL(position.getX(),12);
    BOOST_CHECK_EQUAL(position.getY(),13);
  //test changePlace
    //on fixe X et Y à 10
    position.setY(10);
    position.setX(10);

    position.changePlace(8,4);
    BOOST_CHECK_EQUAL(position.getX(),8);
    BOOST_CHECK_EQUAL(position.getY(),4);



  
 }

  BOOST_AUTO_TEST_CASE(TestBuilding)
{
    Building building{};
    // tests setters getters
    BOOST_CHECK_EQUAL(building.getAmountMana(),0);
    building.setAmountMana(10);
    BOOST_CHECK_EQUAL(sbuildingt.getAmountMana(),10);

    BOOST_CHECK_EQUAL(building.getAmountHP(),0);
    building.setAmountHP(10);
    BOOST_CHECK_EQUAL(building.getAmountHP(),10);

    BOOST_CHECK_EQUAL(building.getBuildingID(),0);
    building.setBuildingID(8);
    BOOST_CHECK_EQUAL(building.getBuildingID(),8);

    BOOST_CHECK_EQUAL(building.getTypeID(),"");
    building.setTypeID("type1");
    BOOST_CHECK_EQUAL(building.getTypeID(),"type1");

    BOOST_CHECK_EQUAL(building.getControler(),0);
    building.setControler(1);
    BOOST_CHECK_EQUAL(building.getControler(),1);

    Position position = building.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
  
 }

 

   BOOST_AUTO_TEST_CASE(TestPlayer)
{
    Player player{};
     //tests setters getters
    BOOST_CHECK_EQUAL(player.getColor(),"");
    player.setColor("Red");
    BOOST_CHECK_EQUAL(player.getColor(),"Red");

    BOOST_CHECK_EQUAL(player.getName(),"");
    player.setName("test");
    BOOST_CHECK_EQUAL(player.getName(),"test");

    BOOST_CHECK_EQUAL(player.getStatus(),WAIT);
    player.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(player.getStatus(),PLAYING);

    //gobelin u= st.getgobelin();
    //BOOST_CHECK_EQUAL(u.getSinglegobelinHP(),0);


    ///Building b1());

 }

   BOOST_AUTO_TEST_CASE(Gobelin)
{
    Gobelin gobelin{};
     //tests setters getters
    Position position = gobelin.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = gobelin.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinHP(), 10);
    gobelin.setSinglegobelinHP(0);
    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinHP(),0);
    
    BOOST_CHECK_EQUAL(gobelin.getGlobalgobelinHP(), 10);
    gobelin.setGlobalgobelinHP(0);
    BOOST_CHECK_EQUAL(gobelin.getGlobalgobelinHP(),0);

    BOOST_CHECK_EQUAL(gobelin.getSightRange(), 10);
    gobelin.setSightRange(0);
    BOOST_CHECK_EQUAL(gobelin.getSightRange(),0);

    BOOST_CHECK_EQUAL(gobelin.getAttackRange(), 10);
    gobelin.setAttackRange(0);
    BOOST_CHECK_EQUAL(gobelin.getAttackRange(),0);

    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinDamage(), 10);
    gobelin.setSinglegobelinDamage(0);
    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinDamage(),0);

    BOOST_CHECK_EQUAL(gobelin.getGlobalgobelinDamage(), 10);
    gobelin.setGlobalgobelinDamage(0);
    BOOST_CHECK_EQUAL(gobelin.getGlobalgobelinDamage(),0);

    BOOST_CHECK_EQUAL(gobelin.getMoveRange(), 10);
    gobelin.setMoveRange(0);
    BOOST_CHECK_EQUAL(gobelin.getMoveRange(),0);

    BOOST_CHECK_EQUAL(gobelin.getgobelinID(), 10);
    gobelin.setgobelinID(0);
    BOOST_CHECK_EQUAL(gobelin.getgobelinID(),0);

    BOOST_CHECK_EQUAL(gobelin.getTypeID(), 10);
    gobelin.setTypeID(0);
    BOOST_CHECK_EQUAL(gobelin.getTypeID(),0);

    BOOST_CHECK_EQUAL(gobelin.getPositions(), 10);
    gobelin.setPositions(0);
    BOOST_CHECK_EQUAL(gobelin.getPositions(),0);

    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinHp(), 10);
    gobelin.setSinglegobelinHp(0);
    BOOST_CHECK_EQUAL(gobelin.getSinglegobelinHp(),0);

    BOOST_CHECK_EQUAL(gobelin.getGlobalHp(), 10);
    gobelin.setGlobalHp(0);
    BOOST_CHECK_EQUAL(gobelin.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(gobelin.getAttackrange(), 10);
    gobelin.setAttackrange(0);
    BOOST_CHECK_EQUAL(gobelin.getAttackrange(),0);

    BOOST_CHECK_EQUAL(gobelin.getGlobalDamage(), 10);
    gobelin.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(gobelin.getGlobalDamage(),0);
 }