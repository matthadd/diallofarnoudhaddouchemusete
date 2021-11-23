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
    // doesnt work
    _position = v;
}

void state::GameInstance::setPosition(int x, int y)
{
    // doesnt work
    _position.x = x;
    _position.y = y;
}