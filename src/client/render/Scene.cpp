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

    int Scene::render(int *warriors_arr)
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "MLB");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            for (render::Layer l : _Layers)
            {
                window.draw(l);
                window.display();
            }
        }
    }

    int Scene::render2()
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), "MLB");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            for (render::Layer l : _Layers)
            {
                printf("[RENDER] for (render::Layer l : _Layers)\n");
                l.load();
                window.draw(l);
                window.display();
            }

            sleep(1); // put macro here for frame rate
                        window.clear();


            while (!_Layers.empty())
            {
                _Layers.pop_back();
                printf("[RENDER] _Layers.pop_back();\n");
            }

            int array[32 * 32] = {0};
            for (auto element : _sceneInfo._GImanagers)
            {
                printf("[RENDER] for (auto element : _sceneInfo._GImanagers);\n");
                printf("GIM ID : %d\n", element.second->getID());
                // "res/Tileset/png/Unit_Map_(32).png"
                add(render::Layer((int)element.second->getID(), element.second->getRes(), sf::Vector2u(32, 32), array, 16, 16));
            }
        }
    }

    // int Scene::render(int* warriors_arr) // take input as GIMs
    // {
    // sf::RenderWindow window(sf::VideoMode(512, 512), "MLB");
    // render::Layer warriors(render::MOVABLE, "res/Tileset/png/Unit_Map_(32).png", sf::Vector2u(32, 32), warriors_arr, 16, 16);
    // if (!warriors.load())
    //     return -1;

    // /*while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if(event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //     window.clear();
    //     window.draw(warriors);
    //     window.display();
    // }*/

    // }
}