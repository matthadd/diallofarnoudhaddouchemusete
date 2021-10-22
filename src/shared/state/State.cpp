#include "State.h"
#include <iostream>
namespace state{
    //Constructeurs et destructeur
    State::State(){}
    State::~State(){}

    //méthodes
    void State::init(){}
    void State::initPlayer1(){}
    void State::initPlayer2(){}
    void State::IncrementTurn(){
        this->turn+=1;
    }
    void State::ChangePlaying(){}    

	//Getter et Setter
    void State::setTurn (int _turn){
        this->turn = _turn;
    }
    int State::getTurn (){
        return this->turn;
    }
    Playing State::getPlaying (){
        return this->playing;
    }
    void State::setPlaying (Playing playing){
        this->playing = playing;
    };
    Player State::getPlayer (int playerID){
        try{
            if(playerID == 1){
                return this->player_1;
            }
            else if(playerID == 2){
                return this->player_2;
            }
            else{
                throw std::string("Veuillez rentrer un id valide pour player");
            }
        }
        catch(std::string const& chaine){
            std::cerr << chaine << std::endl;
        }
    };
}