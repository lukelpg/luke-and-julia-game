#include "npc.h"
#include "sprite.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Npc::Npc(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(renderer, file_path, x, y, w, h) {
    speed_x = 1;
    speed_y = 1;
}

SDL_bool Npc::isColliding(Sprite& obj){
    const SDL_Rect temp = obj.GetRectangle();
    return SDL_HasIntersection(&position, &temp);
}

SDL_Rect Npc::GetRectangle() {
    return position;
}

void Npc::update() {
	// speed_y+=GRAVITY;
    // position.y+=speed_y;

    position.x += speed_x;
    position.y += speed_y;

    if (position.x < 0) {
        position.x = 0;
        speed_x = 1;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
        speed_x = -1;
    }
    if (position.y <= 0) {
        position.y = 0;
        speed_y = 1;
    } else if (position.y > 480 - position.h) {
        position.y = 480 - position.h;
        can_jump = true;
        speed_y = -1;
    }
}

Npc::~Npc() {}