#include "background.h"
#include <iostream>
#include "input_state.h"

Background::Background(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
    background = new TexturedRectangle(renderer, file_path);
    background->setRectangleProperties(x, y, w, h);
    
}

void Background::update(InputState* input_state) {
    background->update(input_state);

    // applyInputState(input_state);
    
    // if (position.x < 0 - position.w) {
    //      position.x = 1280 - position.w;
    // }    
}

void Background::applyInputState(InputState* input_state) {
    // if (input_state->getLeft()) {
    //     position.x += 6;
    // }
    // if (input_state->getRight()) {
    //     position.x -= 6;
    // }
}

Background::~Background() {
    background->~TexturedRectangle();
}

void Background::render(SDL_Renderer* renderer) {
    background->render(renderer);
}