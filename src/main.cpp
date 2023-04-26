#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window with Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
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

    // Load the image
    SDL_Surface* imageSurface = IMG_Load("res/character.png");
    if (imageSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the image surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (texture == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Update the renderer
    SDL_RenderPresent(renderer);

    // Wait for a key press
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				} else if (event.key.keysym.sym == SDLK_SPACE) {
					std::cout << "Space key pressed" << std::endl;
				}
			}
        }
    }

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}