#include "BuildingFactory.h"

namespace state
{
    BuildingFactory::BuildingFactory (){}
    BuildingFactory::~BuildingFactory (){}
    GameInstance* createGI (GameInstanceTypeID typeID, int playerID)
    {
        if(typeID == GameInstanceTypeID::HEADQUARTER){
            return (GameInstance*) new BuildingInstance(typeID, playerID, 10, 15); 
        }
        else if(typeID == GameInstanceTypeID::TRAININGCAMP)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 0, 0);
        }
        else if(typeID == GameInstanceTypeID::MANAMINE)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 0, 20);
        }
        else if(typeID == GameInstanceTypeID::TOWN)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, 10, 0); 
        }
        else
        {
            return NULL;
        }
    }
    GameInstance* createGIat(state::GameInstanceTypeID typeID, int playerID, int x, int y)
    {
        if(typeID == GameInstanceTypeID::HEADQUARTER){
            return (GameInstance*) new BuildingInstance(typeID, playerID, x, y, 10, 15); 
        }
        else if(typeID == GameInstanceTypeID::TRAININGCAMP)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, x, y, 0, 0);
        }
        else if(typeID == GameInstanceTypeID::MANAMINE)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, x, y, 0, 20);
        }
        else if(typeID == GameInstanceTypeID::TOWN)
        {
            return (GameInstance*) new BuildingInstance(typeID, playerID, x, y, 10, 0); 
        }
        else
        {
            return NULL;
        }
    }
}
    