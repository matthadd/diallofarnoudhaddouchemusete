#include "Layer.h"
#include <SFML/Graphics.hpp>

using namespace sf;
namespace render{
    Layer::Layer(int layerID, const std::string& tilesetPath, sf::Vector2u tileSize, const int* tiles, unsigned width, unsigned height){
        _layerID = layerID;
        _tilesetPath = tilesetPath;
        _tileSize = tileSize;   
        _tiles = tiles;     
        _width = width;
        _height = height;
        _layers.push_back(*this);
    }


    Layer::~Layer(){};
    Layer::Layer(){};

    bool Layer::load()
    {
        if(!_tileset.loadFromFile(_tilesetPath)){
            return false;
        }

        _vertices.setPrimitiveType(sf::Quads);
        _vertices.resize(_width*_height*4);

        for(unsigned int i=0; i < _width; ++i){
            for(unsigned int j=0; j < _height; ++j){

                int tileNumber = _tiles[i + j * _width];

                int tu = tileNumber % (_tileset.getSize().x / _tileSize.x);
                int tv = tileNumber / (_tileset.getSize().x / _tileSize.x);

                sf::Vertex* quad = &_vertices[(i+j*_width)*4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
                quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
            }
        }
        return true;
    }

    void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(_vertices, states);
    }
}