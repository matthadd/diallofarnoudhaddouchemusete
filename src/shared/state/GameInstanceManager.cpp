#include "GameInstanceManager.h"
#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;
using namespace sf;

state::GameInstanceManager::GameInstanceManager(std::string name, int id, std::string path)
{
    _name = name;
    _id = id;
    _GameManagers.push_back(this);
}

int state::GameInstanceManager::getID()
{
    return _id;
}

std::string state::GameInstanceManager::getRes()
{
    return _path;
}

void state::GameInstanceManager::add(state::GameInstance *gameInstance)
{
    std::vector<state::GameInstance *> *v = &_GameInstances;
    v->push_back(gameInstance);
}
void state::GameInstanceManager::remove(state::GameInstance *gameInstance)
{
    std::vector<state::GameInstance *> *v = &_GameInstances;
    int i = 0;
    for (state::GameInstance *_gameInstance : _GameInstances)
    {
        if (gameInstance == _gameInstance)
            _GameInstances.erase(_GameInstances.begin() + i);
        i++;
    }
}

int state::GameInstanceManager::getSize()
{
    int i = 0;
    for (state::GameInstance *gameInstance : _GameInstances)
    {
        i++;
    }
    return i;
}

int *state::GameInstanceManager::getArrayFromElements(int *res, int sizeMap)
{
    // assume map is a square
    int dimMap = (int)sqrt(sizeMap);
    int map[dimMap][dimMap];
    // int res[sizeMap] = {0}; // or whatever is the default value
    int indice = 0;
    sf::Vector2i positionElement;
    for (state::GameInstance *gameInstance : _GameInstances)
    {
        positionElement = gameInstance->getPosition();
        map[positionElement.y][positionElement.x] = gameInstance->getTypeID();
    }
    for (int i = 0; i < dimMap; i++)
    {
        for (int j = 0; j < dimMap; j++)
        {
            res[indice] = map[i][j];
            indice++;
        }
    }

    return res;
}

void state::GameInstanceManager::getArrayFromElementsIP(int *res, int sizeMap)
{
    // assume map is a square
    int dimMap = (int)sqrt(sizeMap);
    int map[dimMap][dimMap];
    // int res[sizeMap] = {0}; // or whatever is the default value
    int indice = 0;
    sf::Vector2i positionElement;
    // ini map
    for (int i = 0; i < dimMap; i++)
    {
        for (int j = 0; j < dimMap; j++)
        {
            map[i][j] = 4 * 16;
        }
    }
    // ini res
    for (int i = 0; i < dimMap * dimMap; i++)
    {
        res[i] = 0;
    }
    for (state::GameInstance *gameInstance : _GameInstances)
    {
        positionElement = gameInstance->getPosition();
        map[positionElement.y][positionElement.x] = gameInstance->getTypeID();
    }
    for (int i = 0; i < dimMap; i++)
    {
        for (int j = 0; j < dimMap; j++)
        {
            res[indice] = map[i][j];
            indice++;
        }
    }
}

std::vector<state::GameInstance *> state::GameInstanceManager::getGameInstances()
{
    return _GameInstances;
}