#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "button.h"
#include "game_state.h"
#include "../input/input_state.h"
#include "../sprite/player.h"
#include "../sprite/npc.h"
#include "../render/renderer.h"
#include "../world/background.h"
#include "../world/block.h"
#include "../world/world.h"

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

    // saving and loading world function 

    void loadWorld();
    void saveWorld();

    int count;
    int gamePositionX;
    int gamePositionY;

private:
    Renderer* renderer;
    int error;
    int respawnSeed;
    Background* background1;
    Background* background2;
	Player* character;
    Npc* bad_kat;
	InputState* input_state;
  
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