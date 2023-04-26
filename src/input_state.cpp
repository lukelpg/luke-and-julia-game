#include "input_state.h"
#include <SDL2/SDL.h>

InputState::InputState() {
    up = false;
	down = false;
	left = false;
	right = false;
}

void InputState::applyKeyDown(SDL_Keycode key) {
	applyKey(key, true);
}

void InputState::applyKeyUp(SDL_Keycode key) {
	applyKey(key, false);
}

void InputState::applyKey(SDL_Keycode key, bool value) {
	switch (key) {
		case SDLK_UP:
		case SDLK_w:
			up = value;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			down = value;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			left = value;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			right = value;
			break;
	}
}

int InputState::getRight() {
	return this->right;
}
int InputState::getLeft() {
	return this->left;
}
int InputState::getUp() {
	return this->up;
}
int InputState::getDown() {
	return this->down;
}

InputState::~InputState() {
    
}