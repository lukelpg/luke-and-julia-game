#include "grass_block.h"
#include <iostream>

GrassBlock::GrassBlock(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
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

void GrassBlock::update(InputState* input_state) {
    
}

GrassBlock::~GrassBlock() {
    SDL_DestroyTexture(texture);
}

void GrassBlock::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}