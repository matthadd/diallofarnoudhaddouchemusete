#include "UnitFactory.h"

using namespace std;

namespace state
{

    UnitFactory::UnitFactory() {}

    UnitFactory::~UnitFactory() {}

    GameInstance *UnitFactory::createGI(GameInstanceTypeID typeID, int playerID)
    {
        if (typeID == GameInstanceTypeID::BAT)
        {
            return (GameInstance *)new UnitInstance(typeID, playerID, 10, 10, 4, 11, 20);
        }
        else if (typeID == GameInstanceTypeID::CYCLOPS)
        {
            return (GameInstance *)new UnitInstance(typeID, playerID, 100, 100, 1, 2, 200);
        }
        else if (typeID == GameInstanceTypeID::WITCH)
        {
            return (GameInstance *)new UnitInstance(typeID, playerID, 30, 40, 2, 2, 70);
        }
        else if (typeID == GameInstanceTypeID::DWARF)
        {
            return (GameInstance *)new UnitInstance(typeID, playerID, 50, 50, 1, 3, 50);
        }
        else
        {
            return NULL;
        }
    }
}