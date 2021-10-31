#include "Building.h"

namespace state {

    
    
    int Building::getAmountMana (){
        return this->amountMana; 
    };
    void Building::setAmountMana (int newAmountMana){
        this->amountMana = newAmountMana;
    };

    
    
    int Building::getBuildingID (){
        return this->buildingID; 
    };
    void Building::setBuildingID (int newBuildingID){
        this->buildingID = newBuildingID;
    };


    
    int Building::getAmountHP  (){
        return this->amountHp; 
    };
    void Building::setAmountHP (int newAmountHP){
        this->amountHp = newAmountHP;
    };


    std::string Building::getTypeID (){
        return this->typeID; 
    };
    void Building::setTypeID (std::string  newTypeID){
        this->typeID = newTypeID;
    };



    int Building::getControler () const{
        return this->controler; 
    };
    void Building::setControler (int newcontroller){
        this->controler = newcontroller;
    };

     //pointeur 
    const Position& Building::getPosition() const{
        return this->position; 
    };


    //pointeur 
    void Building::setPosition(const Position& newposition){
         this->position = newposition;
    };


    


}
