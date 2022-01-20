#include "GameInstance.h"
#include <SFML/Graphics.hpp>

using namespace sf;
namespace state
{
    int GameInstance::_idCounter = -1;
    GameInstance::GameInstance(std::string name, GameInstanceTypeID typeID)
    {
        _name = name;
        _id = ++_idCounter; 
        _typeID = typeID;
        _position = std::vector<int> {0, 0};
    }

    GameInstance::GameInstance(GameInstanceTypeID gameInstanceTypeID)
    {
        _typeID = gameInstanceTypeID;
        _id = ++_idCounter;
    }

    std::vector<int> GameInstance::getPosition()
    {
        return _position;
    }

    void GameInstance::assignPosition (std::vector<int> newPos)
    {
        _position = newPos;
    }

    void GameInstance::assignPosition(int x, int y)
    {
        _position = std::vector<int> {x, y};
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

    bool GameInstance::select()
    {
        _selected = true;
        return true;
    }

    void GameInstance::unselect()
    {
        _selected = false;
    }

    int GameInstance::getX() const
    {
        return _position[0];
    }

    int GameInstance::getY() const
    {
        return _position[1];
    }

    GameInstance::~GameInstance() {}
    GameInstance::GameInstance() {}
}
