#include "textured_rectangle.h"
#include "game.h"

TexturedRectangle::TexturedRectangle(Renderer* renderer, const char* file_path, Game* game): game(game) {
    SDL_Surface* surface = IMG_Load(file_path);
	if (surface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}


void TexturedRectangle::setRectangleProperties(int x, int y, int w, int h){
    position.x = x;
    position.y = y;
	position.w = w;
	position.h = h;
}
    
bool TexturedRectangle::isClicked(int mouseX, int mouseY) {
    return (mouseX >= position.x && mouseX <= position.x + position.w &&
            mouseY >= position.y && mouseY <= position.y + position.h);
}


void TexturedRectangle::update(InputState* input_state) {

}


void TexturedRectangle::render(Renderer* renderer) {
    SDL_Rect screenPosition = position;
    
    
    // THE ISSUE IS HERE
    position.x += game->gamePositionX; 
    position.y += game->gamePositionY;

    SDL_RenderCopy(renderer, texture, NULL, &screenPosition);
}


TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(texture);
}


