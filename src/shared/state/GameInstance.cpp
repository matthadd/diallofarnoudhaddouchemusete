#include "GameInstance.h"
#include <SFML/Graphics.hpp>

using namespace sf;
namespace state
{
    int GameInstance::_idCounter = 0;

    GameInstance::GameInstance(std::string name, GameInstanceTypeID typeID)
    {
        _name = name;
        _id = ++_idCounter;
        _typeID = typeID;
        _position = sf::Vector2i(0, 0);
    }

    GameInstance::GameInstance(GameInstanceTypeID gameInstanceTypeID)
    {
        _typeID = gameInstanceTypeID;
        _id = ++_idCounter;
    }

    void GameInstance::initIDCounter()
    {
        _idCounter = 0;
        _id = _idCounter;
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
        _position = sf::Vector2i(x, y);
    }

    int GameInstance::getID()
    {
        return _id;
    }
    GameInstanceTypeID GameInstance::getTypeID()
    {
        return _typeID;
    }

    std::string GameInstance::getName()
    {
        return _name;
    }

    int GameInstance::getPlayerID()
    {
        return _playerID;
    }
    void GameInstance::setPlayerID(int playerID)
    {
        _playerID = playerID;
    }

    bool GameInstance::isSelected()
    {
        return _selected;
    }

    void GameInstance::select()
    {
        _selected = true;
    }

    void GameInstance::unselect()
    {
        _selected = false;
    }

    GameInstance::~GameInstance() {}
    GameInstance::GameInstance() {}
}
