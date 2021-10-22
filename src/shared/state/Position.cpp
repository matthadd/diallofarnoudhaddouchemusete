#include "Position.h"

namespace state{
	//Constructeurs et destructeur
    Position::Position(int init_x, int init_y) : x(init_x), y(init_y){}
    Position::~Position(){}

    //méthodes
    void Position::move(int inc_x, int inc_y){
        this->x+=inc_x;
        this->y+=inc_y;
    }

    void Position::changePlace(int newX, int newY){
        this->x = newX;
        this->y = newY;
    }
    
	//Getter et Setter
}