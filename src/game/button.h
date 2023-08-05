#ifndef BUTTON_H
#define BUTTON_H

#include "../render/renderer.h"

class Button {
public:
    Button(Renderer* renderer, const char* file_path, int x, int y, int width, int height);

    bool isClicked(int mouseX, int mouseY);
    void render(Renderer* renderer);

private:
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect position;
};

#endif