#include "Scene.h"
#include <unistd.h>
#include <iostream>

#include "engine.h"
#include "state/GameInstance.h"
#include <mutex>

#include "macro.hpp"

using namespace std;
using namespace sf;
namespace render
{
    Scene::Scene(SceneID id, state::State *state, int windowWidth, int windowHeight)
    {
        _state = state;
        _id = id;
    }
    Scene::~Scene(){};

    void Scene::add(render::Layer l)
    {
        _Layers.push_back(l);
    }

    void Scene::setSceneInfo(state::State *state)
    {
        _state = state;
    }

    int Scene::render2()
    {
        sf::RenderWindow window(sf::VideoMode(512, 512), GAME_NAME);
        int xCellSize = 32;
        int yCellSize = 32;
        int xNbCells = 10;
        int yNbCells = 10;

        std::vector<int> pos;
        bool selection = false;

        engine::Engine engine(_state);

        while (window.isOpen())
        {
            window.clear();

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
                        std::cout << "x:  " << pos[0] << "  y:  " << pos[1] << std::endl;
                        _state->setPrevSelect(pos);

                        _state->updateRender = true;
                    }

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        // TURN END
                        _state->turn++;

                        _state->updateRender = true;
                    }
                    break;

                // do not handle other event types
                default:
                    break;
                }
            }

            // render on time
            if (_state->updateRender)
            {
                while (!_Layers.empty())
                    _Layers.pop_back();

                int array[SIZE_MAP] = {0};
                render::Layer l(0, PATH_BACKGROUND, sf::Vector2u(32, 32), array, 16, 16);

                _Layers.push_back(l);

                for (auto element : _state->_GImanagers)
                {
                    element.second->getArrayFromElementsIP(array, SIZE_MAP);
                    render::Layer l((int)element.second->getID(), PATH_UNITS, sf::Vector2u(32, 32), array, 16, 16);
                    _Layers.push_back(l);
                }

                for (render::Layer l : _Layers)
                {
                    l.load();
                    window.draw(l);
                    window.display();
                }

                _state->updateRender = false;
            }
        }
    }
}