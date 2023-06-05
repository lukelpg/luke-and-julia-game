#include "game_state.h"


StateData::StateData(){
    gameState = GameState::START_MENU;
};

void StateData::updateState(InputState* input_state, int tempHealth){
    switch (this->gameState) {
        case GameState::START_MENU:
                if(this->startMenu->startButton->isClicked(input_state->mouseData.x, input_state->mouseData.y)){
                    this->gameState = GameState::GAMEPLAY;
                }else{
                    this->gameState = GameState::START_MENU;
                }
            break;
        case GameState::GAMEPLAY:
                if(tempHealth > 0){
                    this->gameState = GameState::GAMEPLAY;
                }else{
                    this->gameState = GameState::RESPAWN;
                }
            break;
        case GameState::PAUSE:
                
            break;
        case GameState::RESPAWN:
                if(input_state->mouseData.right == true){
                    this->gameState = GameState::GAMEPLAY;
                }
            break;
    }
};

// GameState StateData::getState(){
//     return this->gameState;
// };

StateData::~StateData(){
};