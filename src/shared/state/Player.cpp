#include "Player.h"

namespace state {

	//Constructeurs et destructeur
	Player::Player(){}
	Player::~Player(){}
    //méthodes
	int Player::attack(Position position){return 0;}
	//Getter et Setter
	std::string Player::getColor (){
		return this->color;
	};
    void Player::setColor (std::string _color){
		this->color = _color;
	};
}
