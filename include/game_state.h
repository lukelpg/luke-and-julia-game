#include "button.h"

#ifndef GAME_STATE_H
#define GAME_STATE_H

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
    void updateState();
    void getState();
    
    StartMenu* startMenu;
    Gameplay* gameplay;
    Pause* pause;
    GameState gameState;
private:
    
};

#endif
