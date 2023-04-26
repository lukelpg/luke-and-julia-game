#include "sprite.h"
#include "input_state.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
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

void Sprite::update(InputState* input_state) {
    applyInputState(input_state);
    if (position.x < 0) {
        position.x = 0;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
    }
    if (position.y < 0) {
        position.y = 0;
    } else if (position.y > 480 - position.h) {
        position.y = 480 - position.h;
    }
}

void Sprite::applyInputState(InputState* input_state) {
    if (input_state->getLeft()) {
        position.x -= 3;
    }
    if (input_state->getRight()) {
        position.x += 3;
    }
    if (input_state->getUp()) {
        position.y -= 3;
    }
    if (input_state->getDown()) {
        position.y += 3;
    }
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}