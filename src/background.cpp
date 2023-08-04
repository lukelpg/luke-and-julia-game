#include "background.h"
#include <iostream>
#include "input_state.h"
#include "game_info.h"

Background::Background(GameInfo* gameInfo, SDL_Renderer* renderer, const char* file_path, int x, int y, int w, int h): gameInfo(gameInfo) {
    background = new TexturedRectangle(renderer, file_path, gameInfo);
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

void Background::render(SDL_Renderer* renderer) {
    background->render(renderer);
}