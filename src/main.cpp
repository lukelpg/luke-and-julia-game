#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "./game/game.h"

int main(int argc, char* argv[])
{
    Game* game = new Game();

    if(game->run() == 1){
        return 1;
    }

    return 0;
};