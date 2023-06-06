#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Button {
public:
    Button(SDL_Renderer* renderer, const char* file_path, int x, int y, int width, int height);

    bool isClicked(int mouseX, int mouseY);
    void render(SDL_Renderer* renderer);

private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect position;
};

#endif