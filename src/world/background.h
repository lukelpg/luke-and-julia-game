#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../render/renderer.h"
#include "../input/input_state.h"
#include "../game/textured_rectangle.h"

class Game;

class Background {
public:
    Background(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Background();
    void render(Renderer* renderer);
    void update(InputState* input_state, int gamePositionX, int gamePositionY);

private:
    TexturedRectangle* background;
    Game* game;
};

#endif