#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "grass_block.h"
#include "background.h"
#include "input_state.h"
#include "npc.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window with Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Background* background = new Background(renderer, "res/basicBackground.png", 0, 0, 640, 480);
    // Background* background = new Background(renderer, "res/basicBackground.png", 0, 770, 640, 480);
	Sprite* character = new Sprite(renderer, "res/me.png", 288, 100 , 48, 64);
    Npc* bad_kat = new Npc(renderer, "res/AKITKIT.png", 200, 200 , 48, 64);
    GrassBlock* block1 = new GrassBlock(renderer, "res/grassBlock.png", 590, 430, 50, 50);
	InputState* input_state = new InputState();

    // Wait for a key press
    bool quit = false;
	Uint32 last_time = SDL_GetTicks();
	const Uint32 ticks_per_frame = 1000 / 60; // 60 FPS

    //game loop
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE) {
					quit = true;
				} else {
					input_state->applyKeyDown(key);
				}
			} else if (event.type == SDL_KEYUP) {
				SDL_Keycode key = event.key.keysym.sym;
				input_state->applyKeyUp(key);
			}
        }

		// Get the elapsed time since the last frame
		Uint32 current_time = SDL_GetTicks();
		Uint32 elapsed_time = current_time - last_time;

		// Check if it's time to render the next frame
		if (elapsed_time >= ticks_per_frame) {
			// Update the last time
			last_time = current_time;

			//update
			character->update(input_state);
            background->update(input_state);
            bad_kat->update(input_state);

			// Clear the renderer
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);

			//render
            background->render(renderer);
			block1->render(renderer);
            character->render(renderer);
            bad_kat->render(renderer);
            
			// Update the renderer
			SDL_RenderPresent(renderer);
		}
    }

    // Clean up resources
    delete character;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}