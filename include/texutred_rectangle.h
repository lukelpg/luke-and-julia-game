#ifndef TEXTURED_RECTANGLE_H
#define TEXTURED_RECTANGLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "input_state.h"

class TexturedRectangle {
public:
    TexturedRectangle(SDL_Renderer* renderer, const char* file_path);
    ~TexturedRectangle();
    void setRectangleProperties(int x, int y, int w, int h);
    void setScreenPosition(int x, int y);
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

    bool isClicked(int mouseX, int mouseY);

    SDL_Rect position;
    SDL_Rect screenPosition;
private:
    SDL_Texture* texture;
    
};

#endif