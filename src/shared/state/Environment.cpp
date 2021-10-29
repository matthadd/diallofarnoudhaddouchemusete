#include "Environment.h"

namespace state {


    int Environment:: getTypeID  (){
        return this->typeID; 
    };
    void Environment::setTypeID (int typeID){
        this->typeID= typeID;
    };

}