#include "GameInstanceManager.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "UnitInstance.h"
using namespace std;
using namespace sf;

state::GameInstance *state::GameInstanceManager::_objectiveSelected = NULL;
state::GameInstance *state::GameInstanceManager::_sourceSelected = NULL;

state::GameInstanceManager::GameInstanceManager(std::string name, int id, std::string path)
{
    _name = name;
    _id = id;
    _GameManagers.push_back(this);
}

state::GameInstanceManager::GameInstanceManager(std::string name, int id)
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
    //std::vector<state::GameInstance *> *v = &_GameInstances;
    _GameInstances.push_back(gameInstance);
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



void state::GameInstanceManager::getArrayFromElementsIP(int *res, int sizeMap)
{
    // assume map is a square
    int dimMap = (int)sqrt(sizeMap);
    int map[dimMap][dimMap];
    // int res[sizeMap] = {0}; // or whatever is the default value
    int indice = 0;
    std::vector<int> positionElement;
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
        map[positionElement[0]][positionElement[1]] = gameInstance->getTypeID();
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

void state::GameInstanceManager::selectObjective(std::vector<int> unitPos)
{
    for(auto gi : _GameInstances)
    {
        if(gi->getPosition() == unitPos)
        {
            _objectiveSelected = gi;
            gi->select();
            break;
        }
    }
}

void state::GameInstanceManager::selectSource(std::vector<int> unitPos)
{
    for(auto gi : _GameInstances)
    {
        if(gi->getPosition() == unitPos)
        {
            _sourceSelected = gi;
            gi->select();
            break;
        }
    }
}

state::GameInstance *state::GameInstanceManager::getSource()
{
    return _sourceSelected;
}

state::GameInstance *state::GameInstanceManager::getObjective()
{
    return _objectiveSelected;
}

void state::GameInstanceManager::erase(state::GameInstance* gi)
{
    std::vector<state::GameInstance*>::iterator iter = _GameInstances.begin();
    while (iter != _GameInstances.end())
    {
        if (*iter == gi)
        {
            iter = _GameInstances.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}
    
void state::GameInstanceManager:: deleteIfDead (state::GameInstance* gi){
    state::UnitInstance* gi_target =(state::UnitInstance*) gi;
    if(gi_target->isDead()){erase(gi_target);}
}
