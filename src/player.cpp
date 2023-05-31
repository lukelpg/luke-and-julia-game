#include "sprite.h"
#include "player.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Player::Player(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(renderer, file_path, x, y, w, h) {
    health = 100;

    heartSurface = IMG_Load("res/poop.png");
	if (heartSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
    heartPosition.x = 10;
    heartPosition.y = 10;
	heartPosition.w = 50;
	heartPosition.h = 50;
    SDL_FreeSurface(heartSurface);
}

// Function to find the player's position in the grid
void Player::findPlayerPosition() {
    // Calculate the row and column indices
    int cellWidth = 50;
    int cellHeight = 50;
    
    // playerRow = position.y / cellHeight;
    // playerCol = position.x / cellWidth;
}

// void Player::update(InputState* input_state) {
// 	Sprite::update(input_state);
// }

// void Player::applyInputState(InputState* input_state) {
// 	Sprite::applyInputState(input_state);
// }

void Player::render(SDL_Renderer* renderer) {
	Sprite::render(renderer);

    // render heart stuff
    SDL_RenderCopy(renderer, heartTexture, NULL, &heartPosition);
}

Player::~Player() {
    SDL_DestroyTexture(heartTexture);
}