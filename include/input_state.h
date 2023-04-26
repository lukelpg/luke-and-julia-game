#ifndef INPUT_STATE_H
#define INPUT_STATE_H
#include <SDL2/SDL.h>

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

private:
    bool up;
    bool down;
    bool left;
    bool right;
    void applyKey(SDL_Keycode key, bool value);
};

#endif
