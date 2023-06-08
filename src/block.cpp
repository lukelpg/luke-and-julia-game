#include "block.h"
#include <iostream>

Block::Block(SDL_Renderer* renderer, const char* file_path, int col, int row, int size) {
    SDL_Surface* surface = IMG_Load(file_path);
	if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    position.x = col*size;
    position.y = row*size;
	position.w = size;
	position.h = size;
    
    speed_x = 0;
    speed_y = 0;
    SDL_FreeSurface(surface);
}

bool Block::isClicked(int mouseX, int mouseY) {
    return (mouseX >= position.x && mouseX <= position.x + position.w &&
            mouseY >= position.y && mouseY <= position.y + position.h);
}

void Block::update(InputState* input_state) {
}

Block::~Block() {
    SDL_DestroyTexture(texture);
}

void Block::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}