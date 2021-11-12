#include "Unit.h"

namespace state{
    //Constructeurs et destructeur
	// classe abstraite
    //méthodes
    void Unit::init (){}
    void Unit::move (int i, int j){
        positions.move(i,j);
    }
    void Unit::place (int i, int j){
        positions.changePlace(i,j);
    }
    int attack (Position position){
        return 0;
    }

    // Setters and Getters

    Position Unit::getPosition (){
        return positions;
    }    
    int Unit::getSize (){
        return size;
    }
    void Unit::setSize (int _size){
        size = _size;
    }
    int Unit::getSightRange (){
        return sightRange;
    }
    void Unit::setSightRange (int _sightRange){
        sightRange = _sightRange;
    }
    const Position& Unit::getPositions() const{
        return positions;
    }
    void Unit::setPositions(const Position& _positions){
        positions = _positions;
    }
    int Unit::getSingleUnitHp() const{
        return singleUnitHp;
    }
    void Unit::setSingleUnitHp(int _singleUnitHp){
        singleUnitHp = _singleUnitHp;
    }
    int Unit::getGlobalHp() const{
        return globalHp;
    }
    void Unit::setGlobalHp(int _globalHp){
        globalHp = _globalHp;
    }
    int Unit::getAttackRange(){
        return attackRange;
    }
    void Unit::setAttackRange(int _attackRange){
        attackRange = _attackRange;
    }
    int Unit::getGlobalDamage() const{
        return globalDamage;
    }
    void Unit::setGlobalDamage(int _globalDamage){
        globalDamage = _globalDamage;
    }
    const std::string& Unit::getTypeUnit() const{
        return typeUnit;
    }
    void Unit::setTypeUnit(const std::string& _typeUnit){
        typeUnit = _typeUnit;
    }
    int Unit::getUnitID (){
        return unitID;
    }
    void Unit::setUnitID (int _typeID){
        unitID = _typeID;
    }
    int Unit::getGlobalID (){
        return globalID;
    }
    void Unit::setGlobalID (int _globalID){
        globalID = _globalID;
    }
    int Unit::getMoveRange (){
        return moveRange;
    }
    void Unit::setMoveRange (int _moveRange){
        moveRange = _moveRange;
    }

}