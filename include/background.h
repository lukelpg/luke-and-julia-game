#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input_state.h"
#include "texutred_rectangle.h"

class Background {
public:
    Background(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Background();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

private:
    TexturedRectangle* background;

    // SDL_Texture* texture;
    // SDL_Rect position;
    void applyInputState(InputState* input_state);
};

#endif