
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

    BOOST_AUTO_TEST_CASE(TestWizard)
{
    Wizard wizard{};
     //tests setters getters
    Position position = wizard.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = wizard.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(wizard.getSinglewizardHP(), 10);
    wizard.setSinglewizardHP(0);
    BOOST_CHECK_EQUAL(wizard.getSinglewizardHP(),0);
    
    BOOST_CHECK_EQUAL(wizard.getGlobalwizardHP(), 10);
    wizard.setGlobalwizardHP(0);
    BOOST_CHECK_EQUAL(wizard.getGlobalwizardHP(),0);

    BOOST_CHECK_EQUAL(wizard.getSightRange(), 10);
    wizard.setSightRange(0);
    BOOST_CHECK_EQUAL(wizard.getSightRange(),0);

    BOOST_CHECK_EQUAL(wizard.getAttackRange(), 10);
    wizard.setAttackRange(0);
    BOOST_CHECK_EQUAL(wizard.getAttackRange(),0);

    BOOST_CHECK_EQUAL(wizard.getSinglewizardDamage(), 10);
    wizard.setSinglewizardDamage(0);
    BOOST_CHECK_EQUAL(wizard.getSinglewizardDamage(),0);

    BOOST_CHECK_EQUAL(wizard.getGlobalwizardDamage(), 10);
    wizard.setGlobalwizardDamage(0);
    BOOST_CHECK_EQUAL(wizard.getGlobalwizardDamage(),0);

    BOOST_CHECK_EQUAL(wizard.getMoveRange(), 10);
    wizard.setMoveRange(0);
    BOOST_CHECK_EQUAL(wizard.getMoveRange(),0);

    BOOST_CHECK_EQUAL(wizard.getwizardID(), 10);
    wizard.setwizardID(0);
    BOOST_CHECK_EQUAL(wizard.getwizardID(),0);

    BOOST_CHECK_EQUAL(wizard.getTypeID(), 10);
    wizard.setTypeID(0);
    BOOST_CHECK_EQUAL(wizard.getTypeID(),0);

    BOOST_CHECK_EQUAL(wizard.getSinglewizardHp(), 10);
    wizard.setSinglewizardHp(0);
    BOOST_CHECK_EQUAL(wizard.getSinglewizardHp(),0);

    BOOST_CHECK_EQUAL(wizard.getGlobalHp(), 10);
    wizard.setGlobalHp(0);
    BOOST_CHECK_EQUAL(wizard.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(wizard.getAttackrange(), 10);
    wizard.setAttackrange(0);
    BOOST_CHECK_EQUAL(wizard.getAttackrange(),0);

    BOOST_CHECK_EQUAL(wizard.getGlobalDamage(), 10);
    wizard.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(wizard.getGlobalDamage(),0);
 }

    BOOST_AUTO_TEST_CASE(TestKnight)
{
    Knight knight{};
     //tests setters getters
    Position position = knight.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = knight.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(knight.getSingleknightHP(), 10);
    knight.setSingleknightHP(0);
    BOOST_CHECK_EQUAL(knight.getSingleknightHP(),0);
    
    BOOST_CHECK_EQUAL(knight.getGlobalknightHP(), 10);
    knight.setGlobalknightHP(0);
    BOOST_CHECK_EQUAL(knight.getGlobalknightHP(),0);

    BOOST_CHECK_EQUAL(knight.getSightRange(), 10);
    knight.setSightRange(0);
    BOOST_CHECK_EQUAL(knight.getSightRange(),0);

    BOOST_CHECK_EQUAL(knight.getAttackRange(), 10);
    knight.setAttackRange(0);
    BOOST_CHECK_EQUAL(knight.getAttackRange(),0);

    BOOST_CHECK_EQUAL(knight.getSingleknightDamage(), 10);
    knight.setSingleknightDamage(0);
    BOOST_CHECK_EQUAL(knight.getSingleknightDamage(),0);

    BOOST_CHECK_EQUAL(knight.getGlobalknightDamage(), 10);
    knight.setGlobalknightDamage(0);
    BOOST_CHECK_EQUAL(knight.getGlobalknightDamage(),0);

    BOOST_CHECK_EQUAL(knight.getMoveRange(), 10);
    knight.setMoveRange(0);
    BOOST_CHECK_EQUAL(knight.getMoveRange(),0);

    BOOST_CHECK_EQUAL(knight.getknightID(), 10);
    knight.setknightID(0);
    BOOST_CHECK_EQUAL(knight.getknightID(),0);

    BOOST_CHECK_EQUAL(knight.getTypeID(), 10);
    knight.setTypeID(0);
    BOOST_CHECK_EQUAL(knight.getTypeID(),0);


    BOOST_CHECK_EQUAL(knight.getSingleknightHp(), 10);
    knight.setSingleknightHp(0);
    BOOST_CHECK_EQUAL(knight.getSingleknightHp(),0);

    BOOST_CHECK_EQUAL(knight.getGlobalHp(), 10);
    knight.setGlobalHp(0);
    BOOST_CHECK_EQUAL(knight.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(knight.getAttackrange(), 10);
    knight.setAttackrange(0);
    BOOST_CHECK_EQUAL(knight.getAttackrange(),0);

    BOOST_CHECK_EQUAL(knight.getGlobalDamage(), 10);
    knight.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(knight.getGlobalDamage(),0);
 }

    BOOST_AUTO_TEST_CASE(TestGolem)
{
    Golem golem{};
     //tests setters getters
    Position position = golem.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = golem.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(golem.getSinglegolemHP(), 10);
    golem.setSinglegolemHP(0);
    BOOST_CHECK_EQUAL(golem.getSinglegolemHP(),0);
    
    BOOST_CHECK_EQUAL(golem.getGlobalgolemHP(), 10);
    golem.setGlobalgolemHP(0);
    BOOST_CHECK_EQUAL(golem.getGlobalgolemHP(),0);

    BOOST_CHECK_EQUAL(golem.getSightRange(), 10);
    golem.setSightRange(0);
    BOOST_CHECK_EQUAL(golem.getSightRange(),0);

    BOOST_CHECK_EQUAL(golem.getAttackRange(), 10);
    golem.setAttackRange(0);
    BOOST_CHECK_EQUAL(golem.getAttackRange(),0);

    BOOST_CHECK_EQUAL(golem.getSinglegolemDamage(), 10);
    golem.setSinglegolemDamage(0);
    BOOST_CHECK_EQUAL(golem.getSinglegolemDamage(),0);

    BOOST_CHECK_EQUAL(golem.getGlobalgolemDamage(), 10);
    golem.setGlobalgolemDamage(0);
    BOOST_CHECK_EQUAL(golem.getGlobalgolemDamage(),0);

    BOOST_CHECK_EQUAL(golem.getMoveRange(), 10);
    golem.setMoveRange(0);
    BOOST_CHECK_EQUAL(golem.getMoveRange(),0);

    BOOST_CHECK_EQUAL(golem.getgolemID(), 10);
    golem.setgolemID(0);
    BOOST_CHECK_EQUAL(golem.getgolemID(),0);

    BOOST_CHECK_EQUAL(golem.getTypeID(), 10);
    golem.setTypeID(0);
    BOOST_CHECK_EQUAL(golem.getTypeID(),0);


    BOOST_CHECK_EQUAL(golem.getSinglegolemHp(), 10);
    golem.setSinglegolemHp(0);
    BOOST_CHECK_EQUAL(golem.getSinglegolemHp(),0);

    BOOST_CHECK_EQUAL(golem.getGlobalHp(), 10);
    golem.setGlobalHp(0);
    BOOST_CHECK_EQUAL(golem.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(golem.getAttackrange(), 10);
    golem.setAttackrange(0);
    BOOST_CHECK_EQUAL(golem.getAttackrange(),0);

    BOOST_CHECK_EQUAL(golem.getGlobalDamage(), 10);
    golem.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(golem.getGlobalDamage(),0);
 }

    BOOST_AUTO_TEST_CASE(TestdDwarf)
{
    Dwarf dwarf{};
     //tests setters getters
    Position position = dwarf.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = dwarf.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(dwarf.getSingledwarfHP(), 10);
    dwarf.setSingledwarfHP(0);
    BOOST_CHECK_EQUAL(dwarf.getSingledwarfHP(),0);
    
    BOOST_CHECK_EQUAL(dwarf.getGlobaldwarfHP(), 10);
    dwarf.setGlobaldwarfHP(0);
    BOOST_CHECK_EQUAL(dwarf.getGlobaldwarfHP(),0);

    BOOST_CHECK_EQUAL(dwarf.getSightRange(), 10);
    dwarf.setSightRange(0);
    BOOST_CHECK_EQUAL(dwarf.getSightRange(),0);

    BOOST_CHECK_EQUAL(dwarf.getAttackRange(), 10);
    dwarf.setAttackRange(0);
    BOOST_CHECK_EQUAL(dwarf.getAttackRange(),0);

    BOOST_CHECK_EQUAL(dwarf.getSingledwarfDamage(), 10);
    dwarf.setSingledwarfDamage(0);
    BOOST_CHECK_EQUAL(dwarf.getSingledwarfDamage(),0);

    BOOST_CHECK_EQUAL(dwarf.getGlobaldwarfDamage(), 10);
    dwarf.setGlobaldwarfDamage(0);
    BOOST_CHECK_EQUAL(dwarf.getGlobaldwarfDamage(),0);

    BOOST_CHECK_EQUAL(dwarf.getMoveRange(), 10);
    dwarf.setMoveRange(0);
    BOOST_CHECK_EQUAL(dwarf.getMoveRange(),0);

    BOOST_CHECK_EQUAL(dwarf.getdwarfID(), 10);
    dwarf.setdwarfID(0);
    BOOST_CHECK_EQUAL(dwarf.getdwarfID(),0);

    BOOST_CHECK_EQUAL(dwarf.getTypeID(), 10);
    dwarf.setTypeID(0);
    BOOST_CHECK_EQUAL(dwarf.getTypeID(),0);


    BOOST_CHECK_EQUAL(dwarf.getSingledwarfHp(), 10);
    dwarf.setSingledwarfHp(0);
    BOOST_CHECK_EQUAL(dwarf.getSingledwarfHp(),0);

    BOOST_CHECK_EQUAL(dwarf.getGlobalHp(), 10);
    dwarf.setGlobalHp(0);
    BOOST_CHECK_EQUAL(dwarf.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(dwarf.getAttackrange(), 10);
    dwarf.setAttackrange(0);
    BOOST_CHECK_EQUAL(dwarf.getAttackrange(),0);

    BOOST_CHECK_EQUAL(dwarf.getGlobalDamage(), 10);
    dwarf.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(dwarf.getGlobalDamage(),0);
 }

    BOOST_AUTO_TEST_CASE(TestdBat)
{
    Bat bat{};
     //tests setters getters
    Position position = bat.getPosition();
    BOOST_CHECK_EQUAL(position.getX(),0);
    Position position2(2,8) ;
    building.setPosition(position2);
    Position newPosition = bat.getPosition();
    BOOST_CHECK_EQUAL(position2.getX(),2);
    BOOST_CHECK_EQUAL(position2.getY(),8);
    
    BOOST_CHECK_EQUAL(bat.getSinglebatHP(), 10);
    bat.setSinglebatHP(0);
    BOOST_CHECK_EQUAL(bat.getSinglebatHP(),0);
    
    BOOST_CHECK_EQUAL(bat.getGlobalbatHP(), 10);
    bat.setGlobalbatHP(0);
    BOOST_CHECK_EQUAL(bat.getGlobalbatHP(),0);

    BOOST_CHECK_EQUAL(bat.getSightRange(), 10);
    bat.setSightRange(0);
    BOOST_CHECK_EQUAL(bat.getSightRange(),0);

    BOOST_CHECK_EQUAL(bat.getAttackRange(), 10);
    bat.setAttackRange(0);
    BOOST_CHECK_EQUAL(bat.getAttackRange(),0);

    BOOST_CHECK_EQUAL(bat.getSinglebatDamage(), 10);
    bat.setSinglebatDamage(0);
    BOOST_CHECK_EQUAL(bat.getSinglebatDamage(),0);

    BOOST_CHECK_EQUAL(bat.getGlobalbatDamage(), 10);
    bat.setGlobalbatDamage(0);
    BOOST_CHECK_EQUAL(bat.getGlobalbatDamage(),0);

    BOOST_CHECK_EQUAL(bat.getMoveRange(), 10);
    bat.setMoveRange(0);
    BOOST_CHECK_EQUAL(bat.getMoveRange(),0);

    BOOST_CHECK_EQUAL(bat.getbatID(), 10);
    bat.setbatID(0);
    BOOST_CHECK_EQUAL(bat.getbatID(),0);

    BOOST_CHECK_EQUAL(bat.getTypeID(), 10);
    bat.setTypeID(0);
    BOOST_CHECK_EQUAL(bat.getTypeID(),0);


    BOOST_CHECK_EQUAL(bat.getSinglebatHp(), 10);
    bat.setSinglebatHp(0);
    BOOST_CHECK_EQUAL(bat.getSinglebatHp(),0);

    BOOST_CHECK_EQUAL(bat.getGlobalHp(), 10);
    bat.setGlobalHp(0);
    BOOST_CHECK_EQUAL(bat.getGlobalHp(),0);

    BOOST_CHECK_EQUAL(bat.getAttackrange(), 10);
    bat.setAttackrange(0);
    BOOST_CHECK_EQUAL(bat.getAttackrange(),0);

    BOOST_CHECK_EQUAL(bat.getGlobalDamage(), 10);
    bat.getGlobalDamage(0);
    BOOST_CHECK_EQUAL(bat.getGlobalDamage(),0);
 }