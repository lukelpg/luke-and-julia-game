#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "block.h"
#include <vector>

class World {
public:
    World();
    ~World();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state, SDL_Renderer* renderer);

    void generateTileMap(int seed, SDL_Renderer* renderer);
    bool isBesideBlock(int x, int y);
    
    std::vector<Block*> blocks;
};

#endif