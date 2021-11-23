#include "Tileset.h"

namespace render{

    Tileset::Tileset () : _fileLocation(""){}
    Tileset::~Tileset (){}
    Tileset::Tileset (std::string fileLocation, std::string name){
        _fileLocation = fileLocation;
        _name = name;
    }
}