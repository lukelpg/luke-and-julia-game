#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();
    
    void render();
    void copy(SDL_Texture*, SDL_Rect*);
    SDL_Texture* CreateTextureFromSurface(SDL_Surface*);

    void clear();
    void present();

    SDL_Renderer* sdl_renderer;


private:
    SDL_Window* window;
    // SDL_Surface* tile_map_surface;
    // SDL_Texture* tile_texture;
};

#endif