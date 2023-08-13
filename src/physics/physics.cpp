#include <SDL.h>
#include "physics.h"

CollisionResult rectangle_collision(const SDL_Rect& a, const SDL_Rect& b) {
    int hitbox_h_sum = a.h / 2 + b.h / 2;
    int hitbox_w_sum = a.w / 2 + b.w / 2;

    if ((a.y + hitbox_h_sum >= b.y)
        && (a.y <= b.y + hitbox_h_sum)
        && (a.x + hitbox_w_sum >= b.x)
        && (a.x <= b.x + hitbox_w_sum))
    {
        int dl = a.x + hitbox_w_sum - b.x;
        int dr = b.x + hitbox_w_sum - a.x;
        int dt = a.y + hitbox_h_sum - b.y;
        int db = b.y + hitbox_h_sum - a.y;

        if (dl < dt && dl < db) {
            return CollisionResult::Left;
        } else if (dr < dt && dr < db) {
            return CollisionResult::Right;
        } else if (dt < db) {
            return CollisionResult::Top;
        } else {
            return CollisionResult::Bottom;
        }
    }

    return CollisionResult::None;
}

void player_physics(Player* player, World* world) {
    std::vector<Block*> blocks = world->blocks;
     
 	for (const auto& block : blocks) {
		CollisionResult result = rectangle_collision(player->position, block->block->position);
		if (result == CollisionResult::Left) {
			player->position.x = block->block->position.x - player->position.w;
			player->speed_x = 0;
		} else if (result == CollisionResult::Right) {
			player->position.x = block->block->position.x + block->block->position.w;
			player->speed_x = 0;
		} else if (result == CollisionResult::Top) {
			// TODO: fix scuffed code
			player->position.y = block->block->position.y - player->position.h + 6;
			player->speed_y = 0;
			player->can_jump = true;
		} else if (result == CollisionResult::Bottom) {
			player->position.y = block->block->position.y + block->block->position.h + 6;
			player->speed_y = -player->speed_y;
		}
    }
}

void npc_physics(Npc* npc, World* world) {
    std::vector<Block*> blocks = world->blocks;
     
 	for (const auto& block : blocks) {
		CollisionResult result = rectangle_collision(npc->position, block->block->position);
		if (result == CollisionResult::Left) {
			npc->position.x = block->block->position.x - npc->position.w;
			npc->speed_x = -5;
		} else if (result == CollisionResult::Right) {
			npc->position.x = block->block->position.x + block->block->position.w;
			npc->speed_x = 5;
		} else if (result == CollisionResult::Top) {
			// TODO: fix scuffed code
			npc->position.y = block->block->position.y - npc->position.h + 6;
			npc->speed_y = -5;
		} else if (result == CollisionResult::Bottom) {
			npc->position.y = block->block->position.y + block->block->position.h;
			npc->speed_y = 5;
		}
    }
}
