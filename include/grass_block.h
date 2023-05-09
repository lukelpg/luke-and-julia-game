#ifndef GRASS_BLOCK_H
#define GRASS_BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "input_state.h"

class GrassBlock {
public:
    GrassBlock(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~GrassBlock();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

private:
    SDL_Texture* texture;
    SDL_Rect position;
};

#endif