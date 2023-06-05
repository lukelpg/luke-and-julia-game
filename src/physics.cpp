#include <SDL2/SDL.h>
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