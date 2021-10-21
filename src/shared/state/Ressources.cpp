#include "Ressources.h"

namespace state {

	Ressources::Ressources(int initMana) : mana(initMana){}

	void Ressources::setMana(int newMana){
		this->mana = newMana;
	}
}
