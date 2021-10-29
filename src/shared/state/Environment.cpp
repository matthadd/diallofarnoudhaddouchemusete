#include "Environment.h"

namespace state {


    std::string Environment:: getTypeID  (){
        return this->typeID; 
    };
    void Environment::setTypeID (std::string typeID){
        this->typeID= typeID;
    }
    const std::vector<Position>& Environment::getAllPositions() const{
        return allPositions;
    }
    void Environment::setAllPositions(std::vector<Position>& allPositions){
        this->allPositions = allPositions;
    }
    

}