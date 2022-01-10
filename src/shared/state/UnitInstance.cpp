#include "UnitInstance.h"

namespace state{
    UnitInstance::UnitInstance ( GameInstanceTypeID gameInstanceTypeID, int playerID)
    {
        _id = ++_idCounter;
        _typeID = gameInstanceTypeID;
        _playerID = playerID;
        //init();

    }

    UnitInstance::UnitInstance (GameInstanceTypeID typeID, int playerID, int HP, int damage, int sight, int moveRange, int price)
    {
            _id = ++_idCounter;
            _typeID = typeID;
            _playerID = playerID;
            _HP = HP;
            _damage = damage;
            _sight = sight;
            _moveRange = moveRange;
            _price = price;
    }


    UnitInstance::UnitInstance(){}

    UnitInstance::~UnitInstance(){}

    void UnitInstance::init()
    {
        if(_typeID == GameInstanceTypeID::DWARF)
        {
            _HP = 5;
            _damage = 6;
        }
    }

    int UnitInstance::showHP() const
    {
        return _HP;
    }
    int UnitInstance::getSight() 
    {
        return _sight;
    }    
    bool UnitInstance::isUnit()
    {
        return true;
    }

    int UnitInstance::cost() const
    {
        return _price;
    };
    int UnitInstance::getDamage() 
    {
        return _damage;
    }
    void UnitInstance::setDamage (int damage)
    {
        _HP-= damage;
    }

    int UnitInstance::getMoveRange()
    {
        return _moveRange;
    }

};