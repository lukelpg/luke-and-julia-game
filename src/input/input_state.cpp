#include "input_state.h"
#include "../game/button.h"
#include <SDL.h>
#include <iostream>

InputState::InputState() {
    up = false;
	down = false;
	left = false;
	right = false;

	mouseData.left = false;
	mouseData.right = false;
	mouseData.middle = false;
}

void InputState::handleMouseDown(SDL_MouseButtonEvent& mouseEvent) {
	mouseData.x = mouseEvent.x;
	mouseData.y = mouseEvent.y;
	std::cout << mouseData.x << ", " << mouseData.y << std::endl;


	// auto currentTime = std::chrono::steady_clock::now();
	// auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - mouseData.lastClickTime).count();

	// Check if enough time has passed since the last click
	// if (elapsedTime > 200) { // Set the desired cooldown period (in milliseconds)
		if (mouseEvent.button == SDL_BUTTON_LEFT) {
			handleLeftClick();
		} else if (mouseEvent.button == SDL_BUTTON_RIGHT) {
			handleRightClick();
		} else if (mouseEvent.button == SDL_BUTTON_MIDDLE) {
			handleMiddleClick();
		}

		// mouseData.lastClickTime = currentTime;
	// }


	
}

void InputState::handleMouseUp(){
	mouseData.left = false;
	mouseData.right = false;
	mouseData.middle = false;
};


void InputState::handleLeftClick() {
	mouseData.left = true;
}

void InputState::handleRightClick() {
	mouseData.right = true;
}

void InputState::handleMiddleClick() {
	mouseData.middle = true;
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

// struct InputState::getMouseData(){
// 	return this->mouseData;
// }

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