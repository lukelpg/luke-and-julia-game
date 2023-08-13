#ifndef TEXTURED_RECTANGLE_H
#define TEXTURED_RECTANGLE_H

#include <SDL.h>
#include <SDL_image.h>
#include "../input/input_state.h"
#include "../render/renderer.h"

class Game;

class TexturedRectangle {
public:
    TexturedRectangle(Renderer* renderer, const char* file_path, Game* game);
    ~TexturedRectangle();
    void setRectangleProperties(int x, int y, int w, int h);
    void render(Renderer* renderer);
    void update(InputState* input_state);

    bool isClicked(int mouseX, int mouseY);


    //added this for seg falut
    Game* game;

    SDL_Rect position;
    // SDL_Rect screenPosition;
private:
    SDL_Texture* texture;
    
};

#endif