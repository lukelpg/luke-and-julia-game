#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "../sprite/sprite.h"
#include "../input/input_state.h"
#include <vector>

typedef struct Item {
    std::string name;
    std::string description;
    int quantity;
} Item;

class Inventory {
public:
    std::vector<Item> items;
    
    void addItem(const Item& item);
    void removeItem(const Item& item);
    Item* getItem(const std::string& itemName);
private:
    
};

class Game;

class Player : public Sprite {
public:
	Player(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h);
	~Player();
    void render(Renderer* renderer);
    void update(InputState* input_state);
    void findPlayerPosition();
    int playerRow;
    int playerCol;
    int health;
    void healthBar(); 
    void waterBar(); 
    int heartNum;

private:

    // heart stuff 

    SDL_Texture* heartTexture;
    SDL_Rect heartPosition;
    SDL_Rect arrayHeart[10]; 

    SDL_Surface* heartSurface;
    // void applyInputState(InputState* input_state);

    // water stuff 

    SDL_Texture* waterTexture;
    SDL_Rect waterPosition;
    SDL_Rect arrayWater[10]; 

    SDL_Surface* waterSurface;
};

#endif