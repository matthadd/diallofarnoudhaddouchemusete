#include "UnitInstance.h"
#include <iostream>

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

    UnitInstance::UnitInstance (GameInstanceTypeID typeID, int playerID, int HP, int damage, int sight, int moveRange, int price, int x, int y)
    {
            _id = ++_idCounter;
            _typeID = typeID;
            _playerID = playerID;
            _HP = HP;
            _damage = damage;
            _sight = sight;
            _moveRange = moveRange;
            _price = price;
            this->assignPosition(x,y);
    }


    UnitInstance::UnitInstance(){}

    UnitInstance::~UnitInstance(){}

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
    int UnitInstance::giveDamage() 
    {
        if(_HP <= 0)
        {
            std::cout << "unit is dying...\n";
            _isDead = true;
        }
        return _damage;
    }
    void UnitInstance::receiveDamage (int damage)
    {
        _HP -= damage;
        if(_HP <= 0)
        {
            std::cout << "unit is dying...\n";
            _isDead = true;
        }
    }

    bool UnitInstance::isDead()
    {
        return _isDead;
    }

    int UnitInstance::getMoveRange()
    {
        return _moveRange;
    }

};