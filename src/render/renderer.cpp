#include "renderer.h"

Renderer::Renderer(int width, int height) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    // Create a window
    window = SDL_CreateWindow("SDL2 Window with Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    
    // Create a renderer for the window
    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (sdl_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

}

Renderer::~Renderer() {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::present() {
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::render() {

}

void Renderer::copy(SDL_Texture* texture, SDL_Rect* position){
    SDL_RenderCopy(sdl_renderer, texture, NULL, position);
}

SDL_Texture* Renderer::CreateTextureFromSurface(SDL_Surface* surface) {
    return SDL_CreateTextureFromSurface(sdl_renderer, surface);
}