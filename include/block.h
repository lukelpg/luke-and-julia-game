#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input_state.h"
#include "game_state.h"

class Block {
public:
    Block(SDL_Renderer* renderer, const char* file_path, int row, int col, int size);
    ~Block();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);
    SDL_Rect position;
    int speed_x;
    int speed_y;

    // void addBlock(int row, int col, int size);
private:
    SDL_Texture* texture;
    
};

#endif