#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "block.h"
#include "game_info.h"
#include <vector>

class World {
public:
    World(GameInfo* gameInfo);
    ~World();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state, SDL_Renderer* renderer, int playerPosX, int playerPosY);

    void generateTileMap(int seed, SDL_Renderer* renderer);
    bool isBesideBlock(int x, int y);

    void updateBlocks(int cameraPosX, int cameraPosY);
    
    std::vector<Block*> blocks;

    SDL_Rect tile[13][10];
    SDL_Rect select_tile;
    int tilemap[13][10];
    int heights[13];

    int positionX;
    int positionY;
private:
    GameInfo* gameInfo;
};

#endif