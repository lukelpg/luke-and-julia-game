#include "world.h"

World::World(){
    
}

void World::generateTileMap(int seed, SDL_Renderer* renderer){
    //get random number from seed
    srand(seed);

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

    //add blocks to spots function next
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            if(this->tilemap[x][y]){
                block = new Block(renderer, "res/grassBlock.png" , y, x, 50);
                blockGrid[x][y] = block;
            } 
        }
    }
} 

void World::update(InputState* input_state, GameState* gameState){
    // block = new Block(renderer, "res/grassBlock.png" , y, x, 50);
    // blockGrid[x][y] = block;
}

void World::render(SDL_Renderer* renderer){
    // render tile map
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            switch (this->tilemap[x][y]){
                case 1:
                    blockGrid[x][y]->render(renderer);
                    break;
            }
        }
    }   
}

World::~World(){
    
}