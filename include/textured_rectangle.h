#ifndef TEXTURED_RECTANGLE_H
#define TEXTURED_RECTANGLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "input_state.h"
#include "game_info.h"

class TexturedRectangle {
public:
    TexturedRectangle(SDL_Renderer* renderer, const char* file_path, GameInfo* gameInfo);
    ~TexturedRectangle();
    void setRectangleProperties(int x, int y, int w, int h);
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

    bool isClicked(int mouseX, int mouseY);


    //added this for seg falut
    GameInfo* gameInfo;


    SDL_Rect position;
    // SDL_Rect screenPosition;
private:
    SDL_Texture* texture;
    
};

#endif