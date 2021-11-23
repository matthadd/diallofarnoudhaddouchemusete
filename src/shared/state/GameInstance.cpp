#include "GameInstance.h"
#include <SFML/Graphics.hpp>

using namespace sf;

state::GameInstance::GameInstance (std::string name, int id)
{
    _name = name;
    _id = id;
    _position = sf::Vector2i(0,0);
}

sf::Vector2i state::GameInstance::getPosition()
{
    return _position;
}

void state::GameInstance::setPosition(sf::Vector2i v)
{
    _position = sf::Vector2i(v);
}

void state::GameInstance::setPosition(int x, int y)
{
    _position = sf::Vector2i(x,y);
}

int state::GameInstance::getId()
{
    return _id;
}