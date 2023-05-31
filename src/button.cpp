#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "input_state.h"
#include <iostream>

Button::Button(SDL_Renderer* renderer, int x, int y, int w, int h){
    surface = IMG_Load("res/startButton.png");
	if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
    SDL_FreeSurface(surface);
};

bool Button::isClicked(int mouseX, int mouseY) {
    return (mouseX >= position.x && mouseX <= position.x + position.w &&
            mouseY >= position.y && mouseY <= position.y + position.h);
}

// void Button::update(InputState* input_state){
// }

void Button::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &position);
}


