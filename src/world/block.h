#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../input/input_state.h"
#include "../game/game_state.h"
#include "../render/renderer.h"
#include "../game/textured_rectangle.h"

class Game;

class Block {
public:
    Block(Renderer* renderer, Game* game, const char* file_path, int col, int row, int size);
    ~Block();
    void render(Renderer* renderer);
    void update(int gamePositionX, int gamePositionY);

    bool isClicked(int mouseX, int mouseY);

    TexturedRectangle* block;

private:
    SDL_Texture* texture;
    
};

#endif