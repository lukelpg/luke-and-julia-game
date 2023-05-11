#include "background.h"
#include <iostream>
#include "input_state.h"

Background::Background(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
    SDL_Surface* surface = IMG_Load(file_path);
	 if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
    SDL_FreeSurface(surface);
}

void Background::update(InputState* input_state) {

    applyInputState(input_state);
    
    if (position.x < 0 - position.w) {
         position.x = 1280 - position.w;
    }    
}

void Background::applyInputState(InputState* input_state) {
    if (input_state->getLeft()) {
        position.x += 6;
    }
    if (input_state->getRight()) {
        position.x -= 6;
    }
}

Background::~Background() {
    SDL_DestroyTexture(texture);
}

void Background::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}