#include <client/Exemple.h>  // Included from library shared_static
#include "Exemple.h"

namespace client {

void Exemple::setX (int x) {
    // Create an object from "shared" library
    client::Exemple y {};
    y.setX(x);

    this->x = x;
}

}

