#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480; 

Game::Game(){
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        error = 1;
    }

    // Create a window
    window = SDL_CreateWindow("SDL2 Window with Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        error = 1;
    }

    // Create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        error = 1;
    }

    //create new World called world
    world = new World();

    //create characters and backgrounds(for now)
    background1 = new Background(renderer, "res/basicBackground.png", 0, 0, 650, 480);
    background2 = new Background(renderer, "res/basicBackground.png", 640, 0, 650, 480);
	character = new Player(this, renderer, "res/me.png", 288, 100 , 48, 64);
    bad_kat = new Npc(this, renderer, "res/AKITKIT.png", 200, 200 , 48, 64);
	input_state = new InputState();
    
    //create all state data
    gameStateData = new StateData();
    gameStateData->startMenu = new StartMenu();
    gameStateData->startMenu->startButton = new Button(renderer, 120, 300, 200, 75);

    // Create tiles surface
    tile_map_surface = SDL_LoadBMP("res/grassBlock.bmp");
    tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
    SDL_FreeSurface(tile_map_surface);

    quit = false;
}


int Game::run(){
    //return error if constructor gives error
    if(error == 1){
        return 1;
    }

    //make world
    int seed = 6;
    world->generateTileMap(seed, renderer);


    //temporary for testing inventory
    Inventory playerInventory;

    // Add items to the inventory
    Item sword = { "Sword", "A powerful weapon", 1 };
    playerInventory.addItem(sword);

    Item potion = { "Potion", "Restores health", 5 };
    playerInventory.addItem(potion);

    // Remove items from the inventory
    Item usedPotion = { "Potion", "", 2 };
    playerInventory.removeItem(usedPotion);

    // Access an item in the inventory
    Item* foundItem = playerInventory.getItem("Potion");
    if (foundItem) {
        std::cout << "Found item: " << foundItem->quantity << std::endl;
    } else {
        std::cout << "Item not found." << std::endl;
    }


    // Wait for a key press
	Uint32 last_time = SDL_GetTicks();
	const Uint32 ticks_per_frame = 1000 / 60; // 60 FPS

    //game loop
    while (!quit) {
        this->getInput();

		// Get the elapsed time since the last frame
		Uint32 current_time = SDL_GetTicks();
		Uint32 elapsed_time = current_time - last_time;

		// Check if it's time to render the next frame
		if (elapsed_time >= ticks_per_frame) {
			// Update the last time
			last_time = current_time;

            if(gameStateData->gameState == GameState::RESPAWN){
                character->health = 100;
            }
            if(gameStateData->gameState == GameState::GAMEPLAY){
                this->collisionChecks();
            }
            
			this->update();
            this->render();
			
		}
    }
}


void Game::start(){

}

void Game::endGame(){
}

void Game::getInput(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            if (key == SDLK_ESCAPE) {
                quit = true;
            } else {
                input_state->applyKeyDown(key);
            }

        } else if (event.type == SDL_KEYUP) { 
            SDL_Keycode key = event.key.keysym.sym;
            input_state->applyKeyUp(key);

        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            input_state->handleMouseDown(event.button); 

        } else if (event.type == SDL_MOUSEBUTTONUP){
            input_state->handleMouseUp();
        }
    }
}

void Game::collisionChecks(){
    // check for collisions
    if(bad_kat->isColliding(*character)){
        std::cout << character->health << std::endl;
        character->health--;
        
        // checkCollisionDirection(character->position, bad_kat->position, character->speed_x, character->speed_y, bad_kat->speed_x, bad_kat->speed_y);
    }else{
        // std::cout << character->health << std::endl;
    }

    //check for collisions with blocks
    // character->findPlayerPosition();
    // checkCollisionDirection(character, blockGrid[character->playerCol][character->playerRow-1]);

    // for(int x=0; x < 13; x++){
    //     for(int y=0; y < 10; y++){
    //         switch (this->tilemap[x][y]){
    //             case 1:
    //                 checkCollisionDirection(character, blockGrid[x][y]);
    //                 break;
    //         }
    //     }
    // }   
}

void Game::checkCollisionDirection(SDL_Rect objectA, SDL_Rect objectB, int Vax, int Vay, int Vbx, int Vby) {
   
    // Previous positions
    int prevAX = objectA.x - Vax;
    int prevAY = objectA.y - Vay;
    int prevBX = objectB.x - Vbx;
    int prevBY = objectB.y - Vby;

    // Check x-axis collision
    bool collisionX = (prevAX + objectA.w >= prevBX) && (prevAX <= prevBX + objectB.w);

    // Check y-axis collision
    bool collisionY = (prevAY + objectA.h >= prevBY) && (prevAY <= prevBY + objectB.h);

    // Determine collision direction
    if (collisionX && collisionY) {
        // std::cout << "here" << std::endl;
        if (prevAX + objectA.w < prevBX + objectB.w) {
            // Collision from the left
            objectA.x = prevBX - objectA.w;
            std::cout << "from left" << std::endl;
          
        } else if (prevAX > prevBX) {
            // Collision from the right
            objectA.x = prevBX + objectB.w;

            std::cout << "from right" << std::endl;
        }

        if (prevAY + objectA.h < prevBY + objectB.h) {
            // Collision from above
            objectA.y = prevBY - objectA.h;

            std::cout << "from above" << std::endl;
        } else if (prevAY > prevBY) {
            // Collision from below
            objectA.y = prevBY + objectB.h;

            std::cout << "from below" << std::endl;
        }
    }
}


void Game::render(){
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    if(gameStateData->gameState == GameState::START_MENU){
        background1->render(renderer);
        gameStateData->startMenu->startButton->render(renderer);
    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        //render background
        background1->render(renderer);
        background2->render(renderer);

        world->render(renderer);

        //render sprites
        character->render(renderer);
        bad_kat->render(renderer);
    }

    // Update the renderer
	SDL_RenderPresent(renderer);
}

void Game::update(){
    //update state
   
    gameStateData->updateState(input_state, character->health);

    if(gameStateData->gameState == GameState::START_MENU){ 
        
    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        world->update(input_state, renderer);
        character->update(input_state);
        background1->update(input_state);
        background2->update(input_state);
        bad_kat->update();
    } 
}

Game::~Game(){
    // Clean up resources
    delete character;
    delete background1;
    delete background2;
    delete bad_kat;
    SDL_DestroyTexture(tile_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
