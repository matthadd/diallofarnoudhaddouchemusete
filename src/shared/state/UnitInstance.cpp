#include "UnitInstance.h"

namespace state{
    UnitInstance::UnitInstance (int id, GameInstanceTypeID gameInstanceTypeID, int playerID)
    {
        _id = id;
        _typeID = gameInstanceTypeID;
        _playerID = playerID;
        init();

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

};