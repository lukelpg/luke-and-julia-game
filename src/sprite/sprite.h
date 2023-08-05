#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../input/input_state.h"
#include "../render/renderer.h"

class Game;

class Sprite {
public:
    Sprite(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Sprite();
    void render(Renderer* renderer);
    void update(InputState* input_state);
    SDL_bool isColliding(Sprite& obj);
    SDL_Rect GetRectangle();
    SDL_Rect position;
    int speed_x;
    int speed_y;
    bool can_jump;
protected:
    SDL_Texture* texture;
    
    Game* game;
    
    void applyInputState(InputState* input_state);
    void simple_physics();
    void bounds_detection();
};

#endif
