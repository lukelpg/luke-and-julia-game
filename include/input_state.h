#ifndef INPUT_STATE_H
#define INPUT_STATE_H
#include <SDL2/SDL.h>
#include "button.h"
#include "game_state.h"

typedef struct MouseData {
    bool left;
    bool middle;
    bool right;

    int x;
    int y;
}MouseData;

class InputState {
public:
    InputState();
    ~InputState();
    void applyKeyDown(SDL_Keycode key);
    void applyKeyUp(SDL_Keycode key);
    int getRight();
    int getLeft();
    int getUp();
    int getDown();

    void handleMouseDown(SDL_MouseButtonEvent& mouseEvent, Button* button, GameState gameState);
	void handleLeftClick(Button* button, GameState gameState);
	void handleRightClick(Button* button, GameState gameState);
	void handleMiddleClick(Button* button, GameState gameState);

    void handleMouseUp();

    GameState getGameState();

private:
    bool up;
    bool down;
    bool left;
    bool right;

    GameState gameState;

    MouseData mouseData;
    
    void applyKey(SDL_Keycode key, bool value);
};

#endif
