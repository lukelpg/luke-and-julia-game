#include "world.h"

World::World(){
    
}

void World::generateTileMap(int seed, SDL_Renderer* renderer){
    //get random number from seed
    srand(seed);

    // SDL_Rect tile[13][10];
    // SDL_Rect select_tile;
    // int tilemap[13][10];
    // int heights[13];

    // Generate randome height numbers
	for(int x=0; x < 13; x++){
		heights[x] = rand() %10 +1;   // we can adjust this %9 value to make the hills either bigger or smaller. ie if you put in a bigger value, your hills will be smaller 
	}

    //RANDOM WALK ALGORITHM
	for (int x = 1; x < 13; x++) {
		int roll = rand() %2;  
		if( 0 == roll ){
			heights[x] = heights[x-1] + 1; 

		} else {
			heights [x] = heights[x-1]- 1; 
			if (heights[x] < 0 ){
				heights[x] = 0; 
            }
		}
		
	} 
    
    // 'SMOOTHEN OUT' ALGORITHM (take the average)
	for(int x = 0; x < 11; x++){
		heights[x] = ( heights[x] + heights[x+1] + heights[x+2])/3 ; 
	}

	for(int x = 0; x < 13; x++) {
        int stackHeight = heights[x];
        for(int y=0; y <15; y++){
            if(y > stackHeight){
                tilemap[x][y] = 1;
            }else{
                tilemap[x][y] = 0; 
            }
        }
    }

    //add blocks to spots function next
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            if(tilemap[x][y]){
                Block* block = new Block(renderer, "res/grassBlock.png" , x, y, 50);
                blocks.push_back(block);
            }
        }
    }
    
} 

void World::update(InputState* input_state, SDL_Renderer* renderer){
    

    if(input_state->mouseData.left){
        int x = std::floor((input_state->mouseData.x)/50);
        int y = std::floor((input_state->mouseData.y)/50);

        if(!tilemap[x][y] && isBesideBlock(x, y)){
            Block* block = new Block(renderer, "res/grassBlock.png" , x, y, 50);
            blocks.push_back(block);
            tilemap[x][y] = 1;
            std::cout << "Placed block at "<< x << ", " << y <<std::endl;
        }
        
    } else if(input_state->mouseData.right){
        int x = std::floor((input_state->mouseData.x)/50);
        int y = std::floor((input_state->mouseData.y)/50);
        
        if(tilemap[x][y]){
            for (int i = 0; i < blocks.size(); ++i) {
                if((x == std::floor((blocks[i]->position.x)/50)) && (y == std::floor((blocks[i]->position.y)/50))){
                    blocks.erase(blocks.begin() + i);
                }
            }
            tilemap[x][y] = 0;
            std::cout << "Removed block at "<< x << ", " << y <<std::endl;
        }
    }
}

bool World::isBesideBlock(int x, int y){
    int startX = -1;
    int startY = -1;
    int endX = startX+3;
    int endY = startY+3;
    if(x == 0){startX = 0;}
    if(x == 12){endX = startX+2;}
    if(y == 0){startY = 0;}
    if(y == 9){endY = startY+2;}
    
    for(int i = startX; i<endX; i++){
        for(int j = startY; j<endY; j++){
            if(tilemap[x+i][y+j]){
                return true;
            }
        }
    }
    return false;
}

void World::render(SDL_Renderer* renderer){
    for (const auto& block : blocks) {
        block->render(renderer);
    }
}

World::~World(){
    
}