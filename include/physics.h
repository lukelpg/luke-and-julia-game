#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL2/SDL.h>
#include "physics.h"

enum class CollisionResult {
	None,
	Left,
	Right,
	Top,
	Bottom
};

CollisionResult rectangle_collision(const SDL_Rect& a, const SDL_Rect& b);

#endif