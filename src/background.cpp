#include "background.h"
#include <iostream>

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
    
}

Background::~Background() {
    SDL_DestroyTexture(texture);
}

void Background::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}