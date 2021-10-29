#include "UnitFactory.h"

namespace state {
//constructor
    UnitFactory::UnitFactory(){}
//destructor
    UnitFactory::~UnitFactory(){}
//operations
    Unit UnitFactory::createUnit(int typeUnitID, Position position){
        if(typeUnitID == 0){
            return state::Bat new Bat();
        }
    }
}