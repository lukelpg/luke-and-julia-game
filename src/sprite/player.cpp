#include <SDL.h>
#include "sprite.h"
#include "player.h"
#include "../input/input_state.h"
#include "../world/block.h"
#include "../game/game.h"

const int GRAVITY = 1;

Player::Player(Game* game, Renderer* renderer, const char* file_path, int x, int y, int w, int h): Sprite(game, renderer, file_path, x, y, w, h) {


    // health code 

    health = 100;
    heartNum = health/10;

    heartSurface = IMG_Load("res/cheeseyweazy.png");
	if (heartSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }

    heartTexture = renderer->CreateTextureFromSurface(heartSurface);

    heartPosition.x = 10;
    heartPosition.y = 10;
	heartPosition.w = 30;
	heartPosition.h = 30;

    arrayHeart[0] = heartPosition;
    
    SDL_FreeSurface(heartSurface);
    healthBar();

    // thirst code 

    waterSurface = IMG_Load("res/woobiegoobie.png");
    	if (waterSurface == nullptr) {
        std::cerr << "IMG_Load error: " << IMG_GetError() << std::endl;
    }

    waterTexture = renderer->CreateTextureFromSurface(waterSurface);

    waterPosition.x = 10;
    waterPosition.y = 50;
	waterPosition.w = 30;
	waterPosition.h = 30;

    arrayWater[0] = waterPosition;
    
    SDL_FreeSurface(waterSurface);
    waterBar(); 
    
}

// Function to find the player's position in the grid
void Player::findPlayerPosition() {
    // Calculate the row and column indices
    int cellWidth = 50;
    int cellHeight = 50;
    
    // playerRow = position.y / cellHeight;
    // playerCol = position.x / cellWidth;
}

void Player::update(InputState* input_state) {
    Sprite::update(input_state);
    applyInputState(input_state);
    simple_physics();
  
    // updating the number of hearts 
    heartNum = health/10;

    bounds_detection();
}

// void Player::applyInputState(InputState* input_state) {
// 	Sprite::applyInputState(input_state);
// }

void Player::healthBar(){    

    // Update heart position 
    for(int i = 0; i < heartNum; i++) {
        arrayHeart[i] = heartPosition;
        heartPosition.x = heartPosition.x + heartPosition.w + 20;
    }

}

void Player::waterBar(){    

    // Update water position 
    for(int i = 0; i < heartNum; i++) {
        arrayWater[i] = waterPosition;
        waterPosition.x = waterPosition.x + waterPosition.w + 20;
    }

}



void Inventory::addItem(const Item& item) {
    // Check if the item already exists in the inventory
    Item* existingItem = getItem(item.name);
    if (existingItem) {
        existingItem->quantity += item.quantity;
    } else {
        items.push_back(item);
    }
}

void Inventory::removeItem(const Item& item) {
    // Find the item in the inventory
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == item.name) {
            // Decrease the quantity or remove the item if necessary
            if (it->quantity > item.quantity) {
                it->quantity -= item.quantity;
            } else {
                items.erase(it);
            }
            break;
        }
    }
}

Item* Inventory::getItem(const std::string& itemName) {
    for (auto& item : items) {
        if (item.name == itemName) {
            return &item;
        }
    }
    return nullptr;
}



void Player::render(Renderer* renderer) {
	Sprite::render(renderer);

    // render heart stuff

    
    for(int i = 0; i < heartNum; i++) {
        renderer->copy(heartTexture, &arrayHeart[i]);
    }

    // render water stuff

    for(int i = 0; i < heartNum; i++) {
        renderer->copy(waterTexture, &arrayWater[i]);
    }




}

Player::~Player() {
    SDL_DestroyTexture(heartTexture);
    SDL_DestroyTexture(waterTexture);
}