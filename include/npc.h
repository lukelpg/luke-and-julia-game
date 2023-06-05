#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "input_state.h"
#include "sprite.h"

class Npc : public Sprite {
public:
    Npc(Game* game, SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
    ~Npc();
    // void render(SDL_Renderer* renderer);
    void update();
    SDL_bool isColliding(Sprite& obj);
    SDL_Rect GetRectangle();
private:
    
    
};

#endif