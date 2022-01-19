#include "Scene.h"
#include <unistd.h>

#include "engine.h"
#include "state/GameInstance.h"
#include <mutex>
#include <iostream>

using namespace std;
using namespace sf;
namespace render
{
    Scene::Scene(SceneID id, state::State *state, int windowWidth, int windowHeight, std::string title)
    {
        _sceneInfo = state;
        id = _id;
    }

    Scene::~Scene(){};

    // std::vector<Layer*> _Layers;

    void Scene::add(render::Layer l)
    {
        // std::vector<render::Layer> v = _Layers;
        _Layers.push_back(l);
    }

    /*void Scene::drawScene (){
        std::vector<state::GameInstanceManager*> GIMlist;
        GIMlist = _sceneInfo._GImaganagers;

        // on dessine le state
        _window.clear();
        for(std::size_t i=0; i<GIMlist.size(); i++){
            if(GIMlist[i]->getID() == _layers[i]->get_layerID())
            {
                _layers[i]->getArray(GIMlist[i]->getGameInstances());
                _window.draw(*_layers[i]);
            }
        }
        _window.display();
    }*/

    void Scene::setSceneInfo(state::State *state)
    {
        _sceneInfo = state;
    }

    int Scene::render2()
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "Tactical Wars");
        int xCellSize = 32;
        int yCellSize = 32;
        int xNbCells = 10;
        int yNbCells = 10;

        std::vector<int> pos;
        bool selection = false;

        engine::Engine engine(_sceneInfo);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {

                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        pos = {event.mouseButton.x / xCellSize, event.mouseButton.y / yCellSize};
                        printf("x:%3d\ny:%3d \nsel: %d\n", pos[0], pos[1], selection);
                        // engine.addCommand(std::make_shared<engine::SelectionCommand>(pos[0], pos[1]));
                        // engine.addCommand(std::make_shared<engine::MoveCommand>(pos[0] + 1, pos[1]));
                        // engine.processCommands();
                    }
                    break;

                // do not handle other event types
                default:
                    break;
                }
            }
            int sizeMap = 16*16;

            // render on time
            if (updateLayout)
            {
                while (!_Layers.empty())
                    _Layers.pop_back();
                printf("[RENDER] OUT OF EMPTY LOOP\n");

                int array[sizeMap] = {0};
                for (int i = 0; i < sizeMap; i++)
                    array[i] = 0;
                render::Layer l(0, "res/Tileset/png/Static_Global_Tileset_(32).png", sf::Vector2u(32, 32), array, 16, 16);

                _Layers.push_back(l);

                for (auto element : _sceneInfo->_GImanagers)
                {
                    printf("[RENDER] for (auto element : _sceneInfo._GImanagers);\n");
                    // std::cout << " id :" << element.second->getID() << " res : " << element.second->getRes() << std::endl;
                    element.second->getArrayFromElementsIP(array, sizeMap);
                    // for (int i = 0; i < sizeMap; i++)
                    //     std::cout <<  i << "-" << array[i]<< " ";
                    render::Layer l((int)element.second->getID(), "res/Tileset/png/Static_Global_Tileset_2_(32).png", sf::Vector2u(32, 32), array, 16, 16);
                    _Layers.push_back(l);
                }

                for (render::Layer l : _Layers)
                {
                    printf("[RENDER] for (render::Layer l : _Layers)\n");
                    l.load();
                    window.draw(l);
                    window.display();
                }

                sleep(2);

                window.clear();
            }
        }
    }
}