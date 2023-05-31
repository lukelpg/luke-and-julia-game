#include "game_state.h"


StateData::StateData(){
    gameState = GameState::START_MENU;
};

void StateData::updateState(){
    switch (this->gameState) {
        case GameState::START_MENU:
            break;

        case GameState::GAMEPLAY:
            break;
        
        case GameState::PAUSE:
            break;
    }
};

void StateData::getState(){

};

StateData::~StateData(){
};