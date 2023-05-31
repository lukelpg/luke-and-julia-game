#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "background.h"
#include "input_state.h"
#include "npc.h"
#include "button.h"
#include "game_state.h"
#include "block.h"

class Game {
public:
    Game();
    ~Game();
    
    void render();
    void update();

    int run();
    void start();
    void getInput();
    void endGame();

    void generateTileMap();
    void collisionChecks();   
    void checkCollisionDirection(SDL_Rect objectA, SDL_Rect objectB, int Vax, int Vay, int Vbx, int Vby);

private:
    int error;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Background* background1;
    Background* background2;
	Player* character;
    Npc* bad_kat;
	InputState* input_state;
    SDL_Surface* tile_map_surface;
    SDL_Texture* tile_texture;
    Button* button;
    Block* blockGrid[13][10];
    Block* block;

    GameState gameState;

    SDL_Rect tile[13][10];
    SDL_Rect select_tile;
    int tilemap[13][10];
    int heights[13];

    bool quit;
};

#endif