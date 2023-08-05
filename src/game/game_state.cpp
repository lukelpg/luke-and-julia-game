#include "game_state.h"
#include <iostream>


StateData::StateData(){
    gameState = GameState::START_MENU;
};

void StateData::updateState(InputState* input_state, int tempHealth){
    switch (this->gameState) {
        case GameState::START_MENU:
                if(this->startMenu->startButton->isClicked(input_state->mouseData.x, input_state->mouseData.y)){
                    this->gameState = GameState::MY_WORLD_MENU;
                }else{
                    this->gameState = GameState::START_MENU;
                }
            break;
        case GameState::MY_WORLD_MENU:

                // when new world button is clicked 
                if(this->myWorldMenu->myWorldButton->isClicked(input_state->mouseData.x, input_state->mouseData.y)){
                    this->gameState = GameState::GAMEPLAY;
                }
                // // when button 1 is clicked 
                // else if(this->myWorldMenu->worldOne->isClicked(input_state->mouseData.x, input_state->mouseData.y)){  
                //     // loadWorld(*world, "");
                //     this->worldState = WorldState::WORLD_1;
                //     this->gameState = GameState::GAMEPLAY;
                // }
                // // when button 2 is clicked 
                // else if(this->myWorldMenu->worldTwo->isClicked(input_state->mouseData.x, input_state->mouseData.y)){  
                //         //loadWorld(*world, "world2.dat");
                //     this->worldState = WorldState::WORLD_2;
                //     this->gameState = GameState::GAMEPLAY;
                // }
                // // when button 3 is clicked 
                // else if(this->myWorldMenu->worldThree->isClicked(input_state->mouseData.x, input_state->mouseData.y)){  
                //     // loadWorld(*world, "world3.dat");
                //     this->worldState = WorldState::WORLD_3;
                //     this->gameState = GameState::GAMEPLAY;
                // }
                // when no buttons are clicked 
                else{
                    this->gameState = GameState::MY_WORLD_MENU;
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
                if(input_state->mouseData.right){
                    this->gameState = GameState::GAMEPLAY;
                }
            break;
        case GameState::RESPAWN:
                if(this->respawnMenu->respawnButton->isClicked(input_state->mouseData.x, input_state->mouseData.y) && input_state->mouseData.left){
                    
                    this->gameState = GameState::GAMEPLAY;
                }
                if(this->respawnMenu->newWorldButton->isClicked(input_state->mouseData.x, input_state->mouseData.y) && input_state->mouseData.left){  

                    this->gameState = GameState::MY_WORLD_MENU;
                }
                else{
                    this->gameState = GameState::RESPAWN; 
                     }
            break;
    }
};

// GameState StateData::getState(){
//     return this->gameState;
// };

StateData::~StateData(){
};