#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <SDL.h>
#include <chrono>
#include <thread>

typedef struct MouseData {
    bool left;
    bool middle;
    bool right;

    int x;
    int y;

    std::chrono::steady_clock::time_point lastClickTime = std::chrono::steady_clock::now();
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

    void handleMouseDown(SDL_MouseButtonEvent& mouseEvent);
	void handleLeftClick();
	void handleRightClick();
	void handleMiddleClick();

    void handleMouseUp();
    MouseData mouseData;

    // struct getMouseData();

private:
    bool up;
    bool down;
    bool left;
    bool right;

    void applyKey(SDL_Keycode key, bool value);
};

#endif
