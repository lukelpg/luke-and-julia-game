#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "input_state.h"
#include "game_info.h"

class Sprite {
public:
    Sprite(GameInfo* gameInfo, SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Sprite();
    void render(SDL_Renderer* renderer);
    void update(InputState* input_state);
    SDL_bool isColliding(Sprite& obj);
    SDL_Rect GetRectangle();
    SDL_Rect position;
    int speed_x;
    int speed_y;
protected:
    SDL_Texture* texture;
    
    GameInfo* gameInfo;
    
    bool can_jump;
    void applyInputState(InputState* input_state);
    void simple_physics();
    void bounds_detection();
};

#endif
