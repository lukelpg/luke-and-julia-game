#include "background.h"
#include <iostream>
#include "input_state.h"

Background::Background(SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h) {
    background = new TexturedRectangle(renderer, file_path);
    background->setRectangleProperties(x, y, w, h);
}

void Background::update(InputState* input_state, int gamePositionX, int gamePositionY) {
    background->update(input_state);

    int screenPosX = background->position.x - gamePositionX;
    int screenPosY = background->position.y - gamePositionY;
    background->setScreenPosition(screenPosX, screenPosY);
}

Background::~Background() {
    background->~TexturedRectangle();
}

void Background::render(SDL_Renderer* renderer) {
    background->render(renderer);
}