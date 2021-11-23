#include "GameInstanceManager.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

state::GameInstanceManager::GameInstanceManager (std::string name, int id)
{
    _name = name;
    _id = id;
}

void state::GameInstanceManager::add(state::GameInstance* gameInstance)
{
    std::vector<state::GameInstance*>* v = &_GameInstances;
    v->push_back(gameInstance);
}
void state::GameInstanceManager::remove(state::GameInstance* gameInstance)
{
    std::vector<state::GameInstance*>* v = &_GameInstances;
    int i = 0;
    for(state::GameInstance* _gameInstance : _GameInstances)
    {
        if(gameInstance == _gameInstance)
            _GameInstances.erase(_GameInstances.begin() + i);
        i++;
    }
}

int state::GameInstanceManager::getSize(){
    int i =0;
    for(state::GameInstance* gameInstance : _GameInstances)
    {
        i++;
    }
    return i;
}


int* state::GameInstanceManager::getArrayFromElements(int sizeMap)
{
    // assume map is a square
    int array[sizeMap];
    for(state::GameInstance* gameInstance : _GameInstances)
    {
        
    }

    return array;
}