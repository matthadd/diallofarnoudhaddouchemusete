#include "UnitFactory.h"

using namespace std;

namespace state{

    UnitFactory::UnitFactory (){}

    UnitFactory::~UnitFactory(){}

    GameInstance* UnitFactory::createGI(GameInstanceTypeID typeID, int playerID)
    {
        if(typeID == GameInstanceTypeID::BAT){
            return (GameInstance*) new UnitInstance(typeID, playerID, 10, 10, 4, 10, 20); 
        }
        else if(typeID == GameInstanceTypeID::DWARF)
        {
            return (GameInstance*) new UnitInstance(typeID, playerID, 50, 50, 1, 4, 50); 
        }
        else
        {
            return NULL;
        }
    }
}