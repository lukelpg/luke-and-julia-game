#include "world.h"

World::World(){
    positionX = 0;
    positionY = 0;
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
			heights [x] = heights[x-1] - 1; 
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
        int stackHeight = heights[x]+1;
        int diff = rand()%3+1;
        int stoneHeight = stackHeight+diff;

        for(int y=0; y <15; y++){
            if(y == stackHeight){
                tilemap[x][y] = 1;
            }else if(stoneHeight >= y && y > stackHeight){
                tilemap[x][y] = 2;
            }else if(y > stoneHeight){
                tilemap[x][y] = 3;
            }else{
                tilemap[x][y] = 0;
            }
        }
    }

    //add blocks to spots function next
    for(int x=0; x < 13; x++){
        for(int y=0; y < 10; y++){
            //potential bug here
            if(tilemap[x][y] == 2){
                Block* block = new Block(renderer, "res/dirtBlock.jpg" , x, y, 50);
                blocks.push_back(block);
            }else if(tilemap[x][y] == 3){
                Block* block = new Block(renderer, "res/stoneBlock.jpg" , x, y, 50);
                blocks.push_back(block);
            }else if(tilemap[x][y]){
                Block* block = new Block(renderer, "res/grassBlock.png" , x, y, 50);
                blocks.push_back(block);
            }
        }
    }
    
} 

void World::update(InputState* input_state, SDL_Renderer* renderer, int gamePosX, int gamePosY){
    updateBlocks(gamePosX, gamePosY);

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
        

        for (int i = 0; i < blocks.size(); ++i) {
            if(blocks[i]->isClicked(input_state->mouseData.x, input_state->mouseData.y)){
                blocks.erase(blocks.begin() + i);
                std::cout << "Removed block at "<< input_state->mouseData.x/50 << ", " << input_state->mouseData.y/50 << " on the screen." << std::endl;

                tilemap[x][y] = 0;
            }
        }
    }
}

void World::updateBlocks(int cameraPosX, int cameraPosY){
    for (const auto& block : blocks) {
        block->update(cameraPosX, cameraPosY);
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
    std::cout << "rub the bub 1" << std::endl;

    for (const auto& block : blocks) {
        std::cout << "mhm" << std::endl;
    }

    for (const auto& block : blocks) {
        std::cout << "rub the bub 2" << std::endl;

        block->render(renderer, gameInfo);
        std::cout << "rub the bub 3" << std::endl;
    }
}

World::~World(){
    
}