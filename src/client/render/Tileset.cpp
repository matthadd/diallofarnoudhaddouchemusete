#include "Tileset.h"

namespace render{

    Tileset::Tileset () : _fileLocation(""){}
    Tileset::~Tileset (){}
    Tileset::Tileset (std::string fileLocation){
        _fileLocation = fileLocation;
    }
}