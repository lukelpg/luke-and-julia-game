#include "sprite.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Sprite::Sprite(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
    SDL_Surface* surface = IMG_Load(file_path);
	 if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    speed_x = 0;
    speed_y = 0;
    can_jump = false;
    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
    SDL_FreeSurface(surface);
}

void Sprite::update(InputState* input_state) {
    applyInputState(input_state);
    speed_y+=GRAVITY;
    position.y+=speed_y;
    if (position.x < 0) {
        position.x = 0;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
    }
    if (position.y < 0) {
        position.y = 0;
        speed_y = 0;
    } else if (position.y > 480 - position.h) {
        position.y = 480 - position.h;
        can_jump = true;
        speed_y = 0;
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
        // position.y -= 3;
        if(can_jump){
            speed_y = -20;
            can_jump = false;
        } 
    }
    if (input_state->getDown()) {
        // position.y += 3;
    }
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}