#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"

class GameEntiy {
public:
    GameEntiy(){}
    GameEntiy(SDL_Renderer* renderer, std::string spritepath){}
    ~GameEntiy(){}
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

private:
    Sprite* character;
    SDL_Renderer* renderer;

};

#endif