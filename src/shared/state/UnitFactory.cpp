#include "UnitFactory.h"
#include "UnitInstance.h"

using namespace std;

namespace state{

    UnitFactory::UnitFactory(){}

    UnitFactory::~UnitFactory(){}

    GameInstance *UnitFactory::createGI(GameInstanceTypeID typeID, int playerID)
    {
        if(typeID == GameInstanceTypeID::BAT){
            return new UnitInstance(typeID, playerID, 10, 10, 40, 100); 
        }
    }
}