#include "UnitInstance.h"

namespace state{
    UnitInstance::UnitInstance ( GameInstanceTypeID gameInstanceTypeID, int playerID)
    {
        _id = ++_idCounter;
        _typeID = gameInstanceTypeID;
        _playerID = playerID;
        //init();

    }

    UnitInstance::UnitInstance (GameInstanceTypeID typeID, int playerID, int HP, int damage, int sight, int moveRange)
    {
            _id = ++_idCounter;
            _typeID = typeID;
            _playerID = playerID;
            _HP = HP;
            _damage = damage;
            _sight = sight;
            _moveRange = moveRange;
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

    bool UnitInstance::isUnit()
    {
        return true;
    }

};