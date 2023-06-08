#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "input_state.h"
#include "game_state.h"
#include "texutred_rectangle.h"

class Block {
public:
    Block(SDL_Renderer* renderer, const char* file_path, int col, int row, int size);
    ~Block();
    void render(SDL_Renderer* renderer);
    void update(int gamePositionX, int gamePositionY);

    bool isClicked(int mouseX, int mouseY);

    TexturedRectangle* block;

private:
    SDL_Texture* texture;
    
};

#endif