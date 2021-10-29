#include "UnitFactory.h"
#include "../state.h"

namespace state {
//constructor
    UnitFactory::UnitFactory(){}
//destructor
    UnitFactory::~UnitFactory(){}
//operations
    Unit* UnitFactory::createUnit(std::string typeUnitID, Position position){
        if(typeUnitID.compare("Bat") == 0){
            return new Bat();
        }
        if(typeUnitID.compare("Dwarf") == 0){
            return new Dwarf();
        }
        if(typeUnitID.compare("Goblin") == 0){
            return new Goblin();
        }
        if(typeUnitID.compare("Golem") == 0){
            return new Golem();
        }
        if(typeUnitID.compare("Kninght") == 0){
            return new Knight();
        }
        if(typeUnitID.compare("Wizard") == 0){
            return new Wizard();
        }
    }
}