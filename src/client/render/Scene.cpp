#include "Scene.h"
#include <unistd.h>

using namespace sf;
namespace render
{
    Scene::Scene(SceneID id, state::State &state, int windowWidth, int windowHeight, std::string title) : _sceneInfo(state)
    {
        _id = id;
        /*sf::RenderWindow _window(sf::VideoMode(windowWidth, windowHeight), title);
    
        // on gère les évènements
        while(_window.isOpen()){
            sf::Event event;
            while (_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    _window.close();
            }
        
        }*/
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

    void Scene::setSceneInfo(state::State &state)
    {
        _sceneInfo = state;
    }

    int Scene::render2()
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "MLB");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                int xCellSize = 32;
                int yCellSize = 32;
                int xNbCells = 10;
                int yNbCells = 10;

                bool selection = false;
                std::vector<int> pos;
                // pos[0] = 0;
                // pos[1] = 0;

                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        pos = {event.mouseButton.x / xCellSize, event.mouseButton.y / yCellSize};
                        printf("x:%3d\ny:%3d \n", pos[0], pos[1]);
                        selection = !selection;
                    }
                    break;

                // do not handle other event types
                default:
                    break;
                }
            }

            // render on time
            if (updateLayout)
            {

                for (render::Layer l : _Layers)
                {
                    printf("[RENDER] for (render::Layer l : _Layers)\n");
                    l.load();
                    window.draw(l);
                    window.display();
                }

                window.clear();

                while (!_Layers.empty())
                    _Layers.pop_back();
                printf("[RENDER] OUT OF EMPTY LOOP\n");
                sleep(1); // put macro here for frame rate

                int array[32 * 32] = {0};
                for (auto element : _sceneInfo._GImanagers)
                {
                    printf("[RENDER] for (auto element : _sceneInfo._GImanagers);\n");
                    printf("GIM ID : %d\n", element.second->getID());
                    add(render::Layer((int)element.second->getID(), element.second->getRes(), sf::Vector2u(32, 32), array, 16, 16));
                }
                // updateLayout = false;
            }
        }
    }
}