#include "Scene.h"
using namespace sf;
namespace render{
    Scene::Scene(SceneID id, state::State& state,int windowWidth, int windowHeight, std::string title) : _sceneInfo(state){
    _id = id;
    sf::RenderWindow _window(sf::VideoMode(windowWidth, windowHeight), title);
    
        // on gère les évènements
        while(_window.isOpen()){
            sf::Event event;
            while (_window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    _window.close();
            }
        
        }
    }

    Scene::~Scene(){};

    void Scene::addLayer (Layer* layer){
        _layers.push_back(layer);
    }

    std::vector<Layer*> Scene::getComponent (){
        return _layers;
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

    void Scene::setSceneInfo(state::State& state){
        _sceneInfo = state;
    }
}