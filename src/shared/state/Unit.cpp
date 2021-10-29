#include "Unit.h"

namespace state{
    //Constructeurs et destructeur
	// classe abstraite
    //méthodes
    void init ();
    bool move (int x, int y);
    bool place (int i, int j);
    int attack (int globalDamage, int globalHp);

}