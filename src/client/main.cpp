#include <iostream>
#include "stdio.h"
#include <state.h>
#include <render.h>
#include "SFML/Graphics.hpp"
#include <unistd.h>
#include "SFML/Window.hpp"
#include <thread>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{

    // tests state::GameInstance(std::string name, int id)
    state::GameInstance *warrior1 = new state::GameInstance("warrior1", (state::GameInstanceTypeID)129);
    cout << "Resource loaded" << endl;

    std::vector<int> pos = warrior1->getPosition();
    cout << "x:" << pos[0] << " y:" << pos[1] << endl;

    // test void state::GameInstance::setPosition(sf::Vector2i v)
    warrior1->assignPosition(0, 1);
    pos = warrior1->getPosition();
    cout << "x:" << pos[0] << " y:" << pos[1] << endl;

    // tests void state::GameInstance::setPosition(int x, int y)
    warrior1->assignPosition(15, 0);
    pos = warrior1->getPosition();
    cout << "x:" << pos[0] << " y:" << pos[1] << endl;

    // tests state::GameInstanceManager::GameInstanceManager (std::string name, int id)
    state::GameInstanceManager *gim = new state::GameInstanceManager("GIM_1", 3, "res/Tileset/png/Unit_Map_(32).png"); // unit

    // test void state::GameInstanceManager::add(state::GameInstance* gameInstance)
    gim->add(warrior1);

    // tests void state::GameInstanceManager::getArrayFromElements(int* array, int sizeMap)
    int sizeMap = 16 * 16;
    int array[sizeMap] = {0}; // or whatever is the default value
    for (int k = 0; k < 50; k++)
    {
        // cout << "array[" << k <<"] = "<< array[k] << endl;
    }
    gim->getArrayFromElementsIP(array, sizeMap);
    for (int k = 0; k < 50; k++)
    {
        // cout << "array[" << k <<"] = "<< array[k] << endl;
    }

    // Process to create Unit and add it to GIM
    state::GameInstance *warrior2 = new state::GameInstance("warrior2", (state::GameInstanceTypeID)129);
    warrior2->assignPosition(2, 2);
    gim->add(warrior2);

    // Process to add GIM to Layer
    int warriors_arr[sizeMap] = {0};
    // for (int i = 0; i < sizeMap; i++){ warriors_arr[i] = 0;}
    gim->getArrayFromElementsIP(warriors_arr, sizeMap);

    // tests render::Layer construct
    render::Layer l;

    // tests render::Layer(args) construct
    render::Layer warrior_layer(0, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16);

    // test instance state
    state::State state;

    // test instance state with args
    render::Scene s(render::MENU, state, 32, 32, "title");

    // tests int Scene::render(int* warriors_arr)
    // s.render(warriors_arr);

    // tests int Scene::render2(int* arr)
    int background_arr[32 * 32] = {0};
    render::Layer background_l(0, "res/Tileset/png/Static_Global_Tileset_(32).png", sf::Vector2u(32, 32), background_arr, 16, 16);
    render::Layer warrior_l(1, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16);
    s.add(background_l);
    s.add(warrior_l);

    std::thread t(&render::Scene::render2, &s);
    printf("------------------------------\n");
    int i = 0;
    while (1)
    {
        printf("[MAIN] add start\n");

        // update new positions with engine
        warrior1->assignPosition(i % 16, i % 16);
        i += 1;
        gim->getArrayFromElementsIP(warriors_arr, sizeMap);

        // add map and other layers
        s.add(background_l);
        s.add(render::Layer(1, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16));

        printf("[MAIN] add end\n");
        sleep(1);
        warriors_arr[0] = 0;
    }
    // test state::GameInstanceManager::GameInstanceManager (std::string name, int id)
    // test reference to own GIM
    state::GameInstanceManager *gim2 = new state::GameInstanceManager("GIM_0", 3, ""); //unit

    for (state::GameInstanceManager *g : gim->_GameManagers)
    {
        cout << g->getSize() << endl;
    }
    t.join();
    return 0;
}