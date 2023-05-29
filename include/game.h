#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "grass_block.h"
#include "background.h"
#include "input_state.h"
#include "npc.h"
#include "game.h"

class Game {
public:
    Game();
    ~Game();
    void run();
    void endGame();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Background* background1;
    Background* background2;
	Player* character;
    Npc* bad_kat;
    GrassBlock* block1;
	InputState* input_state;
    SDL_Surface* tile_map_surface;
    SDL_Texture* tile_texture;
};

#endif