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

    // gameState = GameState::START;

    //create characters and backgrounds(for now)
    background1 = new Background(renderer, "res/basicBackground.png", 0, 0, 650, 480);
    background2 = new Background(renderer, "res/basicBackground.png", 640, 0, 650, 480);
	character = new Player(renderer, "res/me.png", 288, 100 , 48, 64);
    bad_kat = new Npc(renderer, "res/AKITKIT.png", 200, 200 , 48, 64);
	input_state = new InputState();
    
    
    // Create tiles surface
    tile_map_surface = SDL_LoadBMP("res/grassBlock.bmp");
    tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
    SDL_FreeSurface(tile_map_surface);

    quit = false;
}

int Game::run(){
    //return error if constructor gives error
    if(error == 1){
        return error;
    }

    this->generateTileMap();

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

            // if(gameState == GameState::START){

            // }
            // if(gameState == GameState::PLAYING){
                
            // }

			this->update();
            this->collisionChecks();
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
        }
    }
}

void Game::collisionChecks(){
    // check for collisions
    if(bad_kat->isColliding(*character)){
        std::cout << character->health << std::endl;
        character->health--;
        if(character->health <= 0){
            this->quit = true;
        }
    }else{
        std::cout << character->health << std::endl;
    }
}

void Game::generateTileMap(){
    // Create tile map
	for(int x=0; x < 13; x++){
		this->heights[x] = rand() %10 +1;   // we can adjust this %9 value to make the hills either bigger or smaller. ie if you put in a bigger value, your hills will be smaller 
	}

    //RANDOM WALK ALGORITHM
	for (int x = 1; x < 13; x++) {
		int roll = rand() %2;  
		if( 0 == roll ){
			this->heights[x] = this->heights[x-1] + 1; 

		} else {
			this->heights [x] = this->heights[x-1]- 1; 
			if (this->heights[x] < 0 ){
				this->heights[x] = 0; 
            }
		}
		
	} 
    
    // 'SMOOTHEN OUT' ALGORITHM (take the average)
	for(int x = 0; x < 11; x++){
		this->heights[x] = ( this->heights[x] + this->heights[x+1] + this->heights[x+2])/3 ; 
	}

	for(int x = 0; x < 13; x++) {
        int stackHeight = this->heights[x];

        for(int y=0; y <15; y++){

            if(y > stackHeight){
                this->tilemap[x][y] = 1;

            }else{
                this->tilemap[x][y] = 0; 
            }
        }
    }

    //in function next
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            this->tile[x][y].x = x*50;
            this->tile[x][y].y = y*50;
            this->tile[x][y].w = 50;
            this->tile[x][y].h = 50;
        }
    }

    this->select_tile.x = 0;
    this->select_tile.y = 0;
    this->select_tile.w = 308;
    this->select_tile.h = 309;
} 


void Game::render(){
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // if(gameState == GameState::START){
    //     background2->render(renderer);
    // }
    // if(gameState == GameState::PLAYING){
    // }

    //render background
    background1->render(renderer);
    background2->render(renderer);
    
    // render tile map
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            switch (this->tilemap[x][y]){
                case 1:
                    SDL_RenderCopy(renderer, tile_texture, &this->select_tile, &this->tile[x][y]);
                    break;
            }
        }
    }   


    //render sprites
    character->render(renderer);
    bad_kat->render(renderer);
    
    
    // Update the renderer
	SDL_RenderPresent(renderer);
}

void Game::update(){
    //update
    character->update(input_state);
    background1->update(input_state);
    background2->update(input_state);
    bad_kat->update();
}

Game::~Game(){
    // Clean up resources
    delete character;
    SDL_DestroyTexture(tile_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
