#include "background.h"
#include <iostream>
#include "../game/game.h"

Background::Background(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h): game(game) {
    background = new TexturedRectangle(renderer, file_path, game);
    background->setRectangleProperties(x, y, w, h);
}

void Background::update(InputState* input_state, int gamePositionX, int gamePositionY) {
    //background->update(input_state);

    background->position.y -= gamePositionY;
    background->position.x -= gamePositionX;
}

Background::~Background() {
    background->~TexturedRectangle();
}

void Background::render(Renderer* renderer) {
    background->render(renderer);
}