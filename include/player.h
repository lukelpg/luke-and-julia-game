#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "input_state.h"

class Player : public Sprite {
public:
	Player(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h);
	~Player();
    // void render(SDL_Renderer* renderer);
    void update(InputState* input_state);

private:
    // void applyInputState(InputState* input_state);
};

#endif