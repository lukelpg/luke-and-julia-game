#ifndef INPUT_STATE_H
#define INPUT_STATE_H
#include <SDL2/SDL.h>
#include "button.h"
#include "game_state.h"

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

    void handleMouseClick(int x, int y, SDL_MouseButtonEvent& mouseEvent, Button* button, GameState gameState);
	void handleLeftClick(int x, int y, Button* button, GameState gameState);
	void handleRightClick(int x, int y, Button* button, GameState gameState);
	void handleMiddleClick(int x, int y, Button* button, GameState gameState);

    GameState getGameState();

private:
    bool up;
    bool down;
    bool left;
    bool right;

    GameState gameState;
    
    void applyKey(SDL_Keycode key, bool value);
};

#endif
