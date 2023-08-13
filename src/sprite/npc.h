#ifndef NPC_H
#define NPC_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "../input/input_state.h"
#include "sprite.h"

class Game;

class Npc : public Sprite {
public:
    Npc(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Npc();
    // void render(Renderer* renderer);
    void update();
    SDL_bool isColliding(Sprite& obj);
    SDL_Rect GetRectangle();
    void bounds_detection();
private:
    
    
};

#endif