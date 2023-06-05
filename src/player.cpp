#include "sprite.h"
#include "player.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Player::Player(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(renderer, file_path, x, y, w, h) {

    health = 100;
    heartNum = health/10;

    heartSurface = IMG_Load("res/cheeseyweazy.png");
	if (heartSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }

    heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);

    heartPosition.x = 10;
    heartPosition.y = 10;
	heartPosition.w = 30;
	heartPosition.h = 30;

    arrayHeart[0] = heartPosition;
    
    SDL_FreeSurface(heartSurface);
    healthBar();




    waterSurface = IMG_Load("res/woobiegoobie.png");
    	if (waterSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }

    waterTexture = SDL_CreateTextureFromSurface(renderer, waterSurface);

    waterPosition.x = 10;
    waterPosition.y = 50;
	waterPosition.w = 30;
	waterPosition.h = 30;

    arrayWater[0] = waterPosition;
    
    SDL_FreeSurface(waterSurface);
    waterBar(); 
    
}

// Function to find the player's position in the grid
void Player::findPlayerPosition() {
    // Calculate the row and column indices
    int cellWidth = 50;
    int cellHeight = 50;
    
    // playerRow = position.y / cellHeight;
    // playerCol = position.x / cellWidth;
}

void Player::update(InputState* input_state) {
	Sprite::update(input_state);
    heartNum = health/10;
     
}

// void Player::applyInputState(InputState* input_state) {
// 	Sprite::applyInputState(input_state);
// }

void Player::healthBar(){    

    // Update heart position 
    for(int i = 0; i < heartNum; i++) {
        arrayHeart[i] = heartPosition;
        heartPosition.x = heartPosition.x + heartPosition.w + 20;
    }

}

void Player::waterBar(){    

    // Update water position 
    for(int i = 0; i < heartNum; i++) {
        arrayWater[i] = waterPosition;
        waterPosition.x = waterPosition.x + waterPosition.w + 20;
    }

}

void Player::render(SDL_Renderer* renderer) {
	Sprite::render(renderer);

    // render heart stuff

    
    for(int i = 0; i < heartNum; i++) {
        SDL_RenderCopy(renderer, heartTexture, NULL, &arrayHeart[i]);
    }

    // render water stuff

    for(int i = 0; i < heartNum; i++) {
        SDL_RenderCopy(renderer, waterTexture, NULL, &arrayWater[i]);
    }




}

Player::~Player() {
    SDL_DestroyTexture(heartTexture);
    SDL_DestroyTexture(waterTexture);
}