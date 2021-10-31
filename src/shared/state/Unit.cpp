#include "Unit.h"

namespace state{
    //Constructeurs et destructeur
	// classe abstraite
    //méthodes
    void init ();
    /// incrémente les attributs par les paramètres 
    /// @param i		(???) 
    /// @param j		(???) 
    bool move (int i, int j);
    /// change les attributs i,j du joeur par les paramètres
    /// @param i		(???) 
    /// @param j		(???) 
    bool place (int i, int j){
        return this->positions;
    }
    int attack (Position position);
    Position getPosition ();
    void setPosition (int x, int y);
    int getSize ();
    void setSize (int newSize = 0);
    int getSingleUnitHP ();
    void setSingleUnitHP (int newSingleUnitHP = 0);
    int getGlobalUnitHP ();
    void setGlobalUnitHP (int newGlobalUnitHP = 0);
    int getSightRange ();
    void setSightRange (int newSightRange);
    int getAttackRange ();
    void setAttackRange (int newAttackRange);
    int getSingleUnitDamage ();
    void setSingleUnitDamage (int newSingleUnitDamage);
    int getGlobalUnitDamage ();
    void setGlobalUnitDamage (int newGlobalUnitDamage);
    int getMoveRange ();
    void setMoveRange (int newMoveRange);
    int getUnitID ();
    void setUnitID (int newUnitID);
    int getTypeID ();
    void setTypeID (int newTypeID);
    // Setters and Getters
    const Position& getPositions() const;
    void setPositions(const Position& positions);
    int getSingleUnitHp() const;
    void setSingleUnitHp(int singleUnitHp);
    int getGlobalHp() const;
    void setGlobalHp(int globalHp);
    int getAttackrange() const;
    void setAttackrange(int attackrange);
    int getGlobalDamage() const;
    void setGlobalDamage(int globalDamage);
    const std::string& getTypeUnit() const;
    void setTypeUnit(const std::string& typeUnit);

}