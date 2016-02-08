#pragma once

#include "base.h"

class SDL_Setup
{
public:
    SDL_Setup();
    ~SDL_Setup();

    SDL_Renderer* GetRenderer();
    SDL_Event* GetMainEvent();
    SDL_Rect GetWindowRect();

    bool KeyWasPressed(int key);
    bool MouseButtonLeftWasPressed();

    void Begin();
    void End();

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* mainEvent;

    bool newEventHappened;

};

