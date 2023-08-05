#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL2/SDL.h>
#include "physics.h"
#include "../sprite/player.h"
#include "../world/world.h"
#include "../sprite/npc.h"

enum class CollisionResult {
	None,
	Left,
	Right,
	Top,
	Bottom
};

CollisionResult rectangle_collision(const SDL_Rect& a, const SDL_Rect& b);



void player_physics(Player* player, World* world);
void npc_physics(Npc* npc, World* world);


#endif