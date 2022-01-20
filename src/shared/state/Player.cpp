#include "Player.h"

namespace state
{
    Player::Player(int id) : _id(id) {}

    Player::Player(std::string name, std::string color, int mana)
    {
        _name = name;
        _mana = mana;
    }

    Player::~Player() {}
    
    void Player::setName(std::string name)
    {
        _name = name;
    }

    std::string const Player::getName()
    {
        return _name;
    }

    int Player::getID()
    {
        return _id;
    }

    void Player::setID(int id)
    {
        _id = id;
    }

    int Player::balance() const
    {
        return _mana;
    }

    void Player::credit(int val)
    {
        _mana += val;
    }

    void Player::debit(int val)
    {
        _mana -= val;
    }

}