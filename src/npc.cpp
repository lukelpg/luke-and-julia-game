#include "npc.h"
#include "sprite.h"
#include "input_state.h"
#include "physics.h"
#include "block.h"
#include "game.h"
#include <iostream>

const int GRAVITY = 1;

Npc::Npc(Game* game, SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(game, renderer, file_path, x, y, w, h) {
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


    // simple_physics();

	std::vector<Block*> blocks = game->world->blocks;
     
 	for (const auto& block : blocks) {
		CollisionResult result = rectangle_collision(position, block->block->position);
		if (result == CollisionResult::Left) {
			position.x = block->block->position.x - position.w;
			speed_x = -5;
		} else if (result == CollisionResult::Right) {
			position.x = block->block->position.x + block->block->position.w;
			speed_x = 5;
		} else if (result == CollisionResult::Top) {
			// TODO: fix scuffed code
			position.y = block->block->position.y - position.h + 6;
			speed_y = -5;
		} else if (result == CollisionResult::Bottom) {
			position.y = block->block->position.y + block->block->position.h;
			speed_y = 5;
		}
    }
    bounds_detection();
}

void Npc::bounds_detection() {
    if (position.x < 0) {
        position.x = 0;
        speed_x = 5;
    } else if (position.x > 640 - position.w) {
        position.x = 640 - position.w;
        speed_x = -5;
    }
    if (position.y <= 0) {
        position.y = 0;
        speed_y = 5;
    } else if (position.y > 480 - position.h) {
        position.y = 480 - position.h;
        can_jump = true;
        speed_y = -5;
    }
}

Npc::~Npc() {}