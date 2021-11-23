#include "GameInstance.h"
#include <SFML/Graphics.hpp>

using namespace sf;
namespace state{
    GameInstance::GameInstance (std::string name, int id)
    {
        _name = name;
        _id = id;
        _position = sf::Vector2i(0,0);
    }

    sf::Vector2i GameInstance::getPosition()
    {
        return _position;
    }

    void GameInstance::setPosition(sf::Vector2i v)
    {
        _position = sf::Vector2i(v);
    }

    void GameInstance::setPosition(int x, int y)
    {
        _position = sf::Vector2i(x,y);
    }

    int GameInstance::getId()
    {
        return _id;
    }

    std::string GameInstance::getName(){
        return _name;
    }

    GameInstance::~GameInstance(){}
    GameInstance::GameInstance(){}
}
