#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

int main(int argc, char* argv[])
{
    Game* game = new Game();

    if(game->run() == 1){
        return 1;
    }

    return 0;
};