#include "input_state.h"
#include "button.h"
#include <SDL2/SDL.h>
#include <iostream>

InputState::InputState() {
    up = false;
	down = false;
	left = false;
	right = false;

	mouseData.left = false;
	mouseData.right = false;
	mouseData.middle = false;

	gameState = GameState::START_MENU;
}

void InputState::handleMouseDown(SDL_MouseButtonEvent& mouseEvent, Button* button, StateData* gameStateData) {
	mouseData.x = mouseEvent.x;
	mouseData.y = mouseEvent.y;
	std::cout << mouseData.x << ", " << mouseData.y << std::endl;

	if (mouseEvent.button == SDL_BUTTON_LEFT) {
		handleLeftClick(button, gameStateData);
		mouseData.left = true;
	} else if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		handleRightClick(button, gameStateData);
		mouseData.right = true;
	} else if (mouseEvent.button == SDL_BUTTON_MIDDLE) {
		handleMiddleClick(button, gameStateData);
		mouseData.middle = true;	
	}
}

void InputState::handleMouseUp(){
	mouseData.left = false;
	mouseData.right = false;
	mouseData.middle = false;
};


void InputState::handleLeftClick(Button* button, StateData* gameStateData) {
	if(gameStateData->gameState == GameState::START_MENU){
		if(button->isClicked(mouseData.x, mouseData.y)){
			this->gameState = GameState::GAMEPLAY;
		}else{
			this->gameState = GameState::START_MENU;
		}
	}
}

void InputState::handleRightClick(Button* button, StateData* gameStateData) {
	this->gameState;
}

void InputState::handleMiddleClick(Button* button, StateData* gameStateData) {
	this->gameState;
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