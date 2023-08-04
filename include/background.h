#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game_info.h"
#include "input_state.h"
#include "textured_rectangle.h"

class Background {
public:
    Background(GameInfo* gameInfo, SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Background();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state, int gamePositionX, int gamePositionY);

private:
    TexturedRectangle* background;
    GameInfo* gameInfo;
};

#endif