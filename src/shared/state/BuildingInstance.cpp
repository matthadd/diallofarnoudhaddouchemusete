#include "BuildingInstance.h"

namespace state{
    BuildingInstance::BuildingInstance(GameInstanceTypeID typeID, int playerID, int hpGeneration, int manaGeneration){
        _typeID = typeID;
        _playerID = playerID;
        _hpGenRate = hpGeneration;
        _manaGenRate = manaGeneration;
        _isCaptured = false;
        _captureCounter = 0;
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
            _isCaptured = true;

        }

    }
    void BuildingInstance::addCaptureCounter (){
        _captureCounter+=1;
        BuildingInstance::changeOwnerIfCaptured();
    }
    void BuildingInstance::capturing(int playerCapturing){
        _playerCapturing = playerCapturing;
    }

    int BuildingInstance::showCaptureCounter() const{
        return _captureCounter;
    }

    bool BuildingInstance::isUnit()
    {
        return false;
    }

    bool BuildingInstance::isBuilding()
    {
        return true;
    }

    void state::BuildingInstance::resetCaptureCounter(){
        _captureCounter =0;
    }

    bool state::BuildingInstance::wasCaptured()
    {
        return _isCaptured;
    }

    GameInstanceTypeID state::BuildingInstance::getTypeID()
    {
        return _typeID;
    }

}