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

    //what is the best way to achive something like this
    imageList[0] = "res/grassBlock.png";
    imageList[1] = "res/dirtBlock.jpg";
    imageList[2] = "res/stoneBlock.jpg";

    gameInfo = new GameInfo();

    //create characters and backgrounds(for now)
    background1 = new Background(gameInfo, renderer, "res/basicBackground.png", 0, 0, 650, 480);
    background2 = new Background(gameInfo, renderer, "res/basicBackground.png", 640, 0, 650, 480);
	character = new Player(gameInfo, renderer, "res/me.png", 288, 100 , 48, 64);
    bad_kat = new Npc(gameInfo, renderer, "res/AKITKIT.png", 200, 200 , 48, 64);
	input_state = new InputState();
    
    //create all state data
    gameStateData = new StateData();

    //start menu
    gameStateData->startMenu = new StartMenu();
    gameStateData->startMenu->startButton = new Button(renderer, "res/myWorlds.png", 120, 300, 200, 75);

    //my Worlds Menu
    gameStateData->myWorldMenu = new MyWorldMenu();
    gameStateData->myWorldMenu->myWorldButton = new Button(renderer, "res/yogabagaba.png", 200, 100, 200, 75);
    gameStateData->myWorldMenu->worldOne = new Button(renderer, "res/one.png", 200, 150, 200, 75);
    gameStateData->myWorldMenu->worldTwo = new Button(renderer, "res/two.png", 200, 200, 200, 75);
    gameStateData->myWorldMenu->worldThree = new Button(renderer, "res/three.png", 200, 250, 200, 75);

    //respawn menu 
    gameStateData->respawnMenu = new RespawnMenu();
    gameStateData->respawnMenu->respawnButton = new Button(renderer, "res/diarrhea.png", 250, 200, 200, 75);   
    gameStateData->respawnMenu->newWorldButton = new Button(renderer, "res/myWorlds.png", 250, 300, 200, 75); 

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
    gameInfo->count = 0;

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
                // code to set character's position to starting point once it has respawned 
                character->position.x = 0; 
                character->position.y = 0;
                //code to set cat's position to starting point once it has respawned 
                bad_kat->position.x = 600;
                bad_kat->position.y= 0;
            }
            // initialzing count variable 
            

            if(gameStateData->gameState == GameState::MY_WORLD_MENU){

                // generating a new world when user clicks new world 
                if(count()<3 && (gameStateData->myWorldMenu->myWorldButton->isClicked(input_state->mouseData.x, input_state->mouseData.y) && input_state->mouseData.left)){  

                    //generate a new value for the respawn seed 
                    respawnSeed = std::rand(); 

                    //update the world with the new seed 
                    worlds[count()] = new World();
                    worlds[count()]->generateTileMap(respawnSeed, renderer);

                    world = worlds[count()];  


                    std::cout << "count is: " << count() << std::endl;

                    //increment count by 1 
                    gameInfo->count++;
                }

            }

            if(gameStateData->gameState == GameState::GAMEPLAY){
                this->collisionChecks();
            }

			this->update();
            this->render();
			
		}
    }
}

void Game::updateCamera() {
    // Calculate screen center
    int screenCenterX = SCREEN_WIDTH / 2;
    int screenCenterY = SCREEN_HEIGHT / 2;

    // Calculate the offset
    int offsetX = character->position.x - screenCenterX;
    int offsetY = character->position.y - screenCenterY;

    // Apply the offset to the camera or rendering position
    int cameraX = character->position.x - offsetX;
    int cameraY = character->position.y - offsetY;

    // std::cout << offsetX  << ", " << offsetY << std::endl;

    // entiyPos-playerPos+halfScreen

    // Use the camera position to render the game or update the camera in your engine
    // ...
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
    if(gameStateData->gameState == GameState::MY_WORLD_MENU){
        background1->render(renderer);

        gameStateData->myWorldMenu->myWorldButton->render(renderer);

        // if(){
            gameStateData->myWorldMenu->worldOne->render(renderer);
        // }

        // if(){
            gameStateData->myWorldMenu->worldTwo->render(renderer);
        // }

        // if(){
            gameStateData->myWorldMenu->worldThree->render(renderer);
        // }

    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        //render background
        background1->render(renderer);
        // background2->render(renderer);

        world->render(renderer);

        //render sprites
        character->render(renderer);
        bad_kat->render(renderer);
    }
    if(gameStateData->gameState == GameState::RESPAWN){
        background1->render(renderer);
        gameStateData->respawnMenu->respawnButton->render(renderer);
        gameStateData->respawnMenu->newWorldButton->render(renderer);
    }

    // Update the renderer
	SDL_RenderPresent(renderer);
}

void Game::update(){
    //update state
   
    

    if(gameStateData->gameState == GameState::START_MENU){ 
        gameInfo->gamePositionX = 0;
        gameInfo->gamePositionY = 0;
    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        
        gameInfo->gamePositionX = character->position.x-SCREEN_WIDTH/2;
        gameInfo->gamePositionY = character->position.y-SCREEN_HEIGHT/2;

        world->update(input_state, renderer, gamePositionX(), gamePositionY());
        character->update(input_state);
        background1->update(input_state, gamePositionX(), gamePositionY());
        // background2->update(input_state, gamePositionX);
        bad_kat->update();
        
        updateCamera();
    } 


    if(gameStateData->worldState == WorldState::WORLD_1){
        world = worlds[0];
    }else if(gameStateData->worldState == WorldState::WORLD_2){
        world = worlds[1];
    }else if(gameStateData->worldState == WorldState::WORLD_3){
        world = worlds[2];
    }
    
    gameStateData->updateState(input_state, character->health);

}

int Game::count() {
    return gameInfo->count;
}

int Game::gamePositionX() {
    return gameInfo->gamePositionX;
}

int Game::gamePositionY() {
    return gameInfo->gamePositionY;
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
