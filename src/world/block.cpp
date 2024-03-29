#include "block.h"
#include <iostream>
#include "../game/game.h"

Block::Block(Renderer* renderer, Game* game, const char* file_path, int col, int row, int size) {
    block = new TexturedRectangle(renderer, file_path, game);
    block->setRectangleProperties(col*size, row*size, size, size);

    // SDL_Surface* surface = IMG_Load(file_path);
	// if (surface == nullptr) {
    //     std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    // }
    // texture = SDL_CreateTextureFromSurface(renderer, surface);
    // position.x = col*size;
    // position.y = row*size;
	// position.w = size;
	// position.h = size;
    
    // SDL_FreeSurface(surface);
}

bool Block::isClicked(int mouseX, int mouseY) {
    return block->isClicked(mouseX, mouseY);

    // return (mouseX >= position.x && mouseX <= position.x + position.w &&
    //         mouseY >= position.y && mouseY <= position.y + position.h);
}

void Block::update(int gamePositionX, int gamePositionY) {
    // int screenPosX = block->position.x - gamePositionX;
    // int screenPosY = block->position.y - gamePositionY;
    // block->setScreenPosition(screenPosX, screenPosY);
}

Block::~Block() {
    block->~TexturedRectangle();

    // SDL_DestroyTexture(texture);
}

void Block::render(Renderer* renderer) {
    
    block->render(renderer);

    // SDL_RenderCopy(renderer, texture, NULL, &position);
}