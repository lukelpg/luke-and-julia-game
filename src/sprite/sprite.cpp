#include "sprite.h"
#include "npc.h"
#include "../input/input_state.h"
#include <iostream>
#include "../game/game.h"

const int GRAVITY = 1;

Sprite::Sprite(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h) : game(game) {
    SDL_Surface* surface = IMG_Load(file_path);
	if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
        throw std::runtime_error("IMG_Load error");
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

SDL_bool Sprite::isColliding(Sprite& obj){
    const SDL_Rect temp = obj.GetRectangle();
    return SDL_HasIntersection(&position, &temp);
}

SDL_Rect Sprite::GetRectangle() {
    return position;
}

void Sprite::update(InputState* input_state) {
    applyInputState(input_state);
    simple_physics();
    bounds_detection();
}

void Sprite::simple_physics() {
    speed_y+=GRAVITY;
    position.y+=speed_y;
}

void Sprite::bounds_detection() {
    if (position.x < 0) {
        position.x = 0;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
    }
    if (position.y < 0) {
        // position.y = 0;
        // speed_y = 0;
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
        position.y -= 2;
        if(can_jump){
            speed_y = -15;
            can_jump = false;
        } 
    }
    if (input_state->getDown()) {
        position.y += 2;
    }
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

void Sprite::render(Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}