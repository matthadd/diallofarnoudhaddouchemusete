#include "BuildingInstance.h"
#include "GameInstance.h"

namespace state
{
    BuildingInstance::BuildingInstance (state::GameInstanceTypeID typeID, int playerID, int x, int y, int hpGeneration, int manaGeneration)
    {
        _manaGenRate = manaGeneration;
        _hpGenRate = hpGeneration;
        this->assignPosition(x,y);
        _playerID = playerID;
        _typeID = typeID;
    }
    BuildingInstance::BuildingInstance (state::GameInstanceTypeID typeID, int playerID)
    {
        _typeID = typeID;
        _playerID = playerID;
    }
    BuildingInstance::~BuildingInstance (){}
    bool const BuildingInstance::isBuilding ()
    {
        return true;
    }
    bool BuildingInstance::isBeingCaptured ()
    {
        if(_captureCounter > 0)
        {
            return true; 
        }
        else
        {
            return false;
        }
    }
    void BuildingInstance::changeOwner (int playerID)
    {
        _playerID = playerID;
    }
}

