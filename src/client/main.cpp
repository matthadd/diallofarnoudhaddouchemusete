#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    if (argc == 2){
        if(argv[1] == string("hello")){
            cout<<"Hello World"<<endl;
        }
        else if(argv[1] == "state"){
            cout<<"Utilisez la commande 'make test' pour lancer les tests"<<endl;
        }
        else if(argv[1] == "render"){
            printf("ok");
        }
    return 0;
}
}
