#include "GameInstance.h"
#include <SFML/Graphics.hpp>

using namespace sf;
namespace state{
    GameInstance::GameInstance (std::string name, int id, GameInstanceTypeID typeID)
    {
        _name = name;
        _id = id;
        _typeID = typeID;
        _position = sf::Vector2i(0,0);
    }

    GameInstance::GameInstance (GameInstanceTypeID gameInstanceTypeID, int id)
    {
        _typeID = gameInstanceTypeID;
        _id = id;
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

    int GameInstance::getID()
    {
        return _id;
    }
    GameInstanceTypeID GameInstance::getTypeID()
    {
        return _typeID;
    }

    std::string GameInstance::getName(){
        return _name;
    }

    int GameInstance::getPlayerID (){
        return _playerID;
    }
    void GameInstance::setPlayerID (int playerID){
        _playerID = playerID;
    }

    bool GameInstance::isSelected()
    {
        return _selected;
    }

    GameInstance::~GameInstance(){}
    GameInstance::GameInstance(){}
}
