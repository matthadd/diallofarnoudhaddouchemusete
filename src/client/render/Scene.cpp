#include "Scene.h"

namespace render{
    Scene::Scene(SceneID id, const state::State& state){
    _id = id;
    _state = state;
    };
    Scene::~Scene(){};

    void Scene::addLayer (Layer* layer){
        _layers.push_back(layer);
    }

    std::vector<Layer*> Scene::getComponent (){
        return _layers;
    }

    void Scene::update (const state::State& state){
        
    }
}