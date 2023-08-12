#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "../physics/physics.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480; 

Game::Game(){
    renderer = new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    //create new World called world
    world = new World(this);

    //create characters and backgrounds(for now)
    background1 = new Background(this, renderer, "res/basicBackground.png", 0, 0, 650, 480);
    background2 = new Background(this, renderer, "res/basicBackground.png", 640, 0, 650, 480);
	character = new Player(this, renderer, "res/me.png", 288, 100 , 48, 64);
    bad_kat = new Npc(this, renderer, "res/AKITKIT.png", 200, 200 , 48, 64);
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
    // TODO
    // tile_map_surface = SDL_LoadBMP("res/grassBlock.bmp");
    // tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
    // SDL_FreeSurface(tile_map_surface);

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
    count = 0;


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
                // if((gameStateData->myWorldMenu->myWorldButton->isClicked(input_state->mouseData.x, input_state->mouseData.y) && input_state->mouseData.left)){  

                //     // //generate a new value for the respawn seed 
                //     // respawnSeed = std::rand(); 

                //     // //update the world with the new seed 
                //     // worlds[count()] = new World();
                //     // worlds[count()]->generateTileMap(respawnSeed, renderer);

                //     // world = worlds[count()];  


                //     // std::cout << "hi count is: " << count() << std::endl;

                //     // //increment count by 1 
                //     // count++;
                // }

            }

            if(gameStateData->gameState == GameState::GAMEPLAY){
                this->collisionChecks();
            }

			this->update();
            this->render();
			
		}
    }
    return 0;
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
    renderer->clear();

    if(gameStateData->gameState == GameState::START_MENU){
        background1->render(renderer);

        gameStateData->startMenu->startButton->render(renderer);
    }
    if(gameStateData->gameState == GameState::MY_WORLD_MENU){
        background1->render(renderer);

        
    
        
        gameStateData->myWorldMenu->myWorldButton->render(renderer);
        
        // // if(){
        //     gameStateData->myWorldMenu->worldOne->render(renderer);
        // // }

        // // if(){
        //     gameStateData->myWorldMenu->worldTwo->render(renderer);
        // // }

        // // if(){
        //     gameStateData->myWorldMenu->worldThree->render(renderer);
        // }

    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        //render background
        background1->render(renderer);
        // background2->render(renderer);

        //ISSUE IS IN HERE
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
	renderer->present();
}

void Game::update(){
    //update state
   
    

    if(gameStateData->gameState == GameState::START_MENU){ 
        gamePositionX = 0;
        gamePositionY = 0;
    }
    if(gameStateData->gameState == GameState::GAMEPLAY){
        
        gamePositionX = character->position.x-SCREEN_WIDTH/2;
        gamePositionY = character->position.y-SCREEN_HEIGHT/2;

        world->update(input_state, renderer, gamePositionX, gamePositionY);
        character->update(input_state);
        player_physics(character, world);
        background1->update(input_state, gamePositionX, gamePositionY);
        // background2->update(input_state, gamePositionX);
        bad_kat->update();
        npc_physics(bad_kat, world);
        
        // updateCamera();
    } 


    // if(gameStateData->worldState == WorldState::WORLD_1){
    //     world = worlds[0];
    // }else if(gameStateData->worldState == WorldState::WORLD_2){
    //     world = worlds[1];
    // }else if(gameStateData->worldState == WorldState::WORLD_3){
    //     world = worlds[2];
    // }
    

    gameStateData->updateState(input_state, character->health);

}

Game::~Game(){
    // Clean up resources
    delete character;
    delete background1;
    delete background2;
    delete bad_kat;
    // SDL_DestroyTexture(tile_texture);
    delete renderer;
    SDL_Quit();
}
