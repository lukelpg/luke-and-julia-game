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


enum class GameState {
    START_MENU,
    GAMEPLAY,
    PAUSE
};

class StateData {
public:
    StateData();
    ~StateData();
    void updateState(InputState* input_state);
    // void getState();

    InputState* input_state;
    
    StartMenu* startMenu;
    Gameplay* gameplay;
    Pause* pause;
    GameState gameState;
private:
    
};

#endif