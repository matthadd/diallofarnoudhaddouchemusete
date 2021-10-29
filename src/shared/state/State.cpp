#include "State.h"
#include <iostream>
namespace state{
    //Constructeurs et destructeur
    State::State(){
        turn = 0;
        playing = NO_PLAYER;
        player_1 = Player();
        player_2 = Player();
    }
    State::~State(){}

    //méthodes
    void State::init(){
        turn = 0;
        playing = PLAYER_1;
        player_1 = Player();
        player_2 = Player();
    }
    void State::initPlayer1(){  /*rien pour le moment*/  }
    void State::initPlayer2(){  /*rien pour le moment*/  }
    void State::IncrementTurn(){
        turn+=1;
    }
    void State::ChangePlaying(){
        //On change simplement le joueur qui joue
        switch (playing)
        {
        case PLAYER_1:
            playing = PLAYER_2;
            break;
        case PLAYER_2:
            playing = PLAYER_1;
        
        default:
            break;
        }
    }    

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
    void State::setPlayer (Player newPlayer, int playerID){
        switch (playerID)
        {
        case 1:
            player_1 = newPlayer;
            break;
        case 2:
            player_2 = newPlayer;
        
        default:
            break;
        }
    }

}