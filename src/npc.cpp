#include "npc.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Npc::Npc(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
    SDL_Surface* surface = IMG_Load(file_path);
	 if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    speed_x = 1;
    speed_y = 0;
    can_jump = false;
    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
    SDL_FreeSurface(surface);
}

void Npc::update() {
    speed_y+=GRAVITY;
    position.y+=speed_y;

    position.x += speed_x;

    if (position.x < 0) {
        position.x = 0;
        speed_x = 1;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
        speed_x = -1;
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

Npc::~Npc() {
    SDL_DestroyTexture(texture);
}

void Npc::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}