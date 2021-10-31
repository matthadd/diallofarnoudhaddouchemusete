#include "Player.h"

namespace state {

	//Constructeurs et destructeur
	Player::Player(){}
	Player::~Player(){}
    //méthodes
	int Player::attack(Position position, int unitID){
	
		//return getUnit(unitID).attack(position);
		return 0;
	}
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

	Building Player::getBuildings (int buildingID ){
		return this->buildings[buildingID];
	};
    
	Unit Player::getUnit (int unitID ){	
		return this->army[unitID];
	};

	UnitFactory Player:: getUnitFactory ( ){	
		return this->unitFactory;
	};

	//void Player::setRessources (Ressources _ressouces){
	//	this->ressources = _ressouces;
	//};


	
}
