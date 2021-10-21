#include "Ressources.h"

namespace state {

	//Constructeurs et destructeur
	Ressources::Ressources(int initMana) : mana(initMana){}

	Ressources::~Ressources(){}

	//Getter et Setter
	void Ressources::setMana(int newMana){
		this->mana = newMana;
	}
	int Ressources::getMana(){
		return this->mana;
	};
	
}
