#include "input_state.h"
#include "button.h"
#include <SDL2/SDL.h>
#include <iostream>

InputState::InputState() {
    up = false;
	down = false;
	left = false;
	right = false;

	gameState = GameState::START;
}

void InputState::handleMouseClick(int x, int y, SDL_MouseButtonEvent& mouseEvent, Button* button, GameState gameState) {
	if (mouseEvent.button == SDL_BUTTON_LEFT) {
		handleLeftClick(x, y, button, gameState);
	} else if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		handleRightClick(x, y, button, gameState);		
	} else if (mouseEvent.button == SDL_BUTTON_MIDDLE) {
		handleMiddleClick(x, y, button, gameState);		
	}
}

void InputState::handleLeftClick(int x, int y, Button* button, GameState gameState) {
	if(gameState == GameState::START){
		if(button->isClicked(x, y)){
			this->gameState = GameState::PLAYING;
		}else{
			this->gameState = GameState::START;
		}
	}
}

void InputState::handleRightClick(int x, int y, Button* button, GameState gameState) {
	this->gameState = gameState;
}

void InputState::handleMiddleClick(int x, int y, Button* button, GameState gameState) {
	this->gameState = gameState;
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

GameState InputState::getGameState(){
	return this->gameState;
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