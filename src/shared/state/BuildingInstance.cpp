#include "BuildingInstance.h"

namespace state{
    BuildingInstance::BuildingInstance(GameInstanceTypeID typeID, int playerID, int hpGeneration, int manaGeneration){
        _typeID = typeID;
        _playerID = playerID;
        _hpGenRate = hpGeneration;
        _manaGenRate = manaGeneration;
    }

    BuildingInstance::~BuildingInstance (){}

    bool BuildingInstance::isBeignCaptured ()
    {
        if(_captureCounter > 0){
            return true;
        }
        else 
            return false;
    }
    void BuildingInstance::changeOwnerIfCaptured (){
        if(_captureCounter == 2)
        {
            _captureCounter = 0;
            _playerID = _playerCapturing;

        }

    }
    void BuildingInstance::addCaptureCounter (){
        _captureCounter+=1;
        BuildingInstance::changeOwnerIfCaptured();
    }
    void BuildingInstance::capturing(int playerCapturing){
        _playerCapturing = playerCapturing;
    }

}