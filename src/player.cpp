#include "sprite.h"
#include "player.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Player::Player(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(renderer, file_path, x, y, w, h) {}


// void Player::update(InputState* input_state) {
// 	Sprite::update(input_state);
// }

// void Player::applyInputState(InputState* input_state) {
// 	Sprite::applyInputState(input_state);
// }

// void Player::render(SDL_Renderer* renderer) {
// 	Sprite::render(renderer);
// }

Player::~Player() {}