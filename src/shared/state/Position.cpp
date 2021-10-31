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
        //this->x = newX;
        //this->y = newY;

        setY(newY);
        setX(newX);
    }
    
	//Getter et SetterS

    void Position::setX (int newX){
        this-> x= newX;
    };
    void Position::setY (int newY){
        this-> y= newY;
    };

    int Position::getX (){
        return this->x; 
    };

    int Position::getY (){
        return this->y; 
    };

}