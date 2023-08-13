#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "block.h"
#include <vector>

class Game;

class World {
public:
    World(Game* game);
    ~World();
    void render(Renderer* renderer);
    void update(InputState* input_state, Renderer* renderer, int playerPosX, int playerPosY);

    void generateTileMap(int seed, Renderer* renderer);
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
    Game* game;
};

#endif