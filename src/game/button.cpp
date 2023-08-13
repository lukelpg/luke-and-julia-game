#include <SDL.h>
#include <SDL_image.h>
#include "button.h"
#include "../input/input_state.h"
#include <iostream>

// start button 
Button::Button(Renderer* renderer, const char* file_path, int x, int y, int w, int h){
    surface = IMG_Load(file_path);
	if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = renderer->CreateTextureFromSurface(surface);

    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
    SDL_FreeSurface(surface);
};

bool Button::isClicked(int mouseX, int mouseY) {
    // std::cout << "burn after" << position.x << "reading" << std::endl;
    return (mouseX >= position.x && mouseX <= position.x + position.w &&
            mouseY >= position.y && mouseY <= position.y + position.h);
}

// void Button::update(InputState* input_state){
// }

void Button::render(Renderer* renderer) {
    renderer->copy(texture, &position);
}


