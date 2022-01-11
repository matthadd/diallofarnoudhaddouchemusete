#include "BuildingFactory.h"

namespace state{
    
    BuildingFactory::BuildingFactory (){}
    BuildingFactory::~BuildingFactory (){}

    GameInstance* BuildingFactory::createGI (GameInstanceTypeID typeID, int playerID){
        if(typeID == GameInstanceTypeID::HEADQUARTER){
            return (GameInstance*) new BuildingInstance(typeID, playerID, 15, 15); 
        }
        else if(typeID == GameInstanceTypeID::TOWN)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 10, 0);
        }
        else if(typeID == GameInstanceTypeID::MANAMINE)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 0, 15);
        }
        else if(typeID == GameInstanceTypeID::TRAININGCAMP)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 0, 0); 
        }
        else
        {
            return NULL;
        }
    }
}