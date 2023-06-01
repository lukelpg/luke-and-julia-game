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

typedef struct Respawn {
}Respawn;


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
    
    StartMenu* startMenu;
    Gameplay* gameplay;
    // Respawn* Respawn;
    // Pause* Pause;

    GameState gameState;
private:
    
};

#endif