#include <iostream>
#include "stdio.h"
#include <state.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        if(!m_tileset.loadFromFile(tileset)){
            return false;
        }

        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width*height*4);

        for(unsigned int i=0; i < width; ++i){
            for(unsigned int j=0; j < height; ++j){
 
                int tileNumber = tiles[i + j * width];

                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                sf::Vertex* quad = &m_vertices[(i+j*width)*4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
        return true;
    }

    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

};

int main(int argc,char* argv[]) {

    
    // tests state::GameInstance(std::string name, int id)
    state::GameInstance* warrior1 = new state::GameInstance("warrior1",1);
    cout << "Resource loaded" << endl;  

    sf::Vector2i pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;

    // test void state::GameInstance::setPosition(sf::Vector2i v)
    warrior1->setPosition(sf::Vector2i(0,1));
    pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;
    
    // tests void state::GameInstance::setPosition(int x, int y)
    warrior1->setPosition(1,1);
    pos = warrior1->getPosition();
    cout << "x:" <<pos.x << " y:" <<pos.y << endl;


    // tests state::GameInstanceManager::GameInstanceManager (std::string name, int id)
    state::GameInstanceManager* gim = new state::GameInstanceManager("GIM_0", 0);
    
    // tests int* state::GameInstanceManager::getArrayFromElements(int sizeMap)
    gim.add()

    return 0;
}