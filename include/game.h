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
#include "world.h"
#include "game_info.h"

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

    void collisionChecks();   
    void checkCollisionDirection(SDL_Rect objectA, SDL_Rect objectB, int Vax, int Vay, int Vbx, int Vby);

    World* world;
    Block* blockList[3];
    std::string imageList[3];
    SDL_Renderer* renderer;

    // saving and loading world function 

    void loadWorld();
    void saveWorld();

    // int count;
    // int gamePositionX;
    // int gamePositionY;
    GameInfo* gameInfo;
    int count();
    int gamePositionX();
    int gamePositionY();

private:
    int error;
    int respawnSeed;
    SDL_Window* window;
    Background* background1;
    Background* background2;
	Player* character;
    Npc* bad_kat;
	InputState* input_state;
    SDL_Surface* tile_map_surface;
    SDL_Texture* tile_texture;
  
    World* worlds[3];

    // GameState gameState;
    StateData* gameStateData;

    // start menu

    StartMenu* startMenu;
    Button* startButton;

    // new world menu 

    MyWorldMenu* myWorldMenu; 
    Button* myWorldButton; 

    // respawn menu 
    
    RespawnMenu* respawnMenu; 
    Button* respawnButton;
    Button* newWorldButton;

    void updateCamera();

    bool quit;
};

#endif