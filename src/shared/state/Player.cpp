#include "Player.h"

namespace state {

	//Constructeurs et destructeur
	Player::Player(){}
	Player::~Player(){}
    //méthodes
	int Player::attack(Position position, int unitID){return 0;}
	//Getter et Setter
	std::string Player::getColor (){
		return this->color;
	};
    void Player::setColor (std::string _color){
		this->color = _color;
	};


	std::string Player::getName (){
		return this->name;
	};
    void Player::setName (std::string name){
		this->name = name;
	};



	GameStatus Player::getStatus (){
		return this->status;
	};
    void Player::setStatus (GameStatus _status){
		this->status = _status;
	};
}
