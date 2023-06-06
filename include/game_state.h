#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "input_state.h"
#include "button.h"

typedef struct StartMenu {
    Button* startButton;
}StartMenu;

typedef struct Gameplay {
}Gameplay;

typedef struct Pause {
}Pause;

typedef struct RespawnMenu {
    Button* respawnButton;
    Button* newWorldButton;

}RespawnMenu;


enum class GameState {
    START_MENU,
    GAMEPLAY,
    RESPAWN,
    PAUSE
};

class StateData {
public:
    StateData();
    ~StateData();
    void updateState(InputState* input_state, int tempHealth);
    // void getState();

    InputState* input_state;

    // Start Menu  
    StartMenu* startMenu;

    // Respawn Menu
    RespawnMenu* respawnMenu; 
    Gameplay* gameplay;
    // Pause* Pause;

    GameState gameState;
private:
    
};

#endif