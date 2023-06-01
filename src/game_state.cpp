#include "game_state.h"


StateData::StateData(){
    gameState = GameState::START_MENU;
};

void StateData::updateState(InputState* input_state){
    switch (this->gameState) {
        case GameState::START_MENU:
                if(this->startMenu->startButton->isClicked(input_state->mouseData.x, input_state->mouseData.y)){
                    this->gameState = GameState::GAMEPLAY;
                }else{
                    this->gameState = GameState::START_MENU;
                }
            break;

        case GameState::GAMEPLAY:
            break;
        
        case GameState::PAUSE:
            break;
    }
};

// GameState StateData::getState(){
//     return this->gameState;
// };

StateData::~StateData(){
};