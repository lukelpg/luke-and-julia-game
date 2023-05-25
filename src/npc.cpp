#include "npc.h"
#include "sprite.h"
#include "input_state.h"
#include <iostream>

const int GRAVITY = 1;

Npc::Npc(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(renderer, file_path, x, y, w, h) {}


// void Npc::update() {
    
//     Sprite::update();

//     position.x += speed_x;

//     if (position.x < 0) {
//         position.x = 0;
//         speed_x = 1;
//     } else if (position.x > 640 - position.w) {
//         position.x = 640 - position.w;
//         speed_x = -1;
//     }
// }

Npc::~Npc() {}