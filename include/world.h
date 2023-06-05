#ifndef WORLD_H
#define WORLD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "block.h"

class World {
public:
    World();
    ~World();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state, GameState* gameState);

    void generateTileMap(int seed, SDL_Renderer* renderer);
    
protected:
    SDL_Rect tile[13][10];
    SDL_Rect select_tile;
    int tilemap[13][10];
    int heights[13];

    Block* blockGrid[13][10];
    Block* block;
};

#endif