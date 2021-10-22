#include "Building.h"

namespace state {
    void setBuildingID (int buildingID){};
    int Building::getAmountMana (){
        return this->amountMana; 
    };
    void Building::setAmountMana (int newAmountMana){
        this->amountMana = newAmountMana;
    };
}
