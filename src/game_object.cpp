#include "game_object.h"
#include <iostream>

GameEntiy::GameEntiy(){
    character = nullptr;
}

GameEntiy::GameEntiy(SDL_Renderer renderer, std::string spritepath){
    character = new Sprite(renderer, spritepath, 288, 100 , 48, 64); 
}

GameEntiy::~GameEntiy(){
    
}

void GameEntiy::render(SDL_Renderer* renderer){
    Sprite::render(SDL_Renderer* renderer);
}

void GameEntiy::update(InputState* input_state){
    if(nullptr == character){
        character->Render(character);
    }

    Sprite::update(InputState* input_state);
}


