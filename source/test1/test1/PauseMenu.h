#pragma once

#include "Button.h"

class PauseMenu
{
public:
    PauseMenu(SDL_Setup* sdlSetup, bool& passedGamePaused, bool& passedRunning);
    ~PauseMenu();
    void Update();
    void Draw(GameMode gameMode);

private:
    CSprite* label;
    CSprite* background;
    Button* resumeButton;
    Button* exitButton;
    bool& gamePaused;
    bool& gameLoopRunning;

    int staticCamera;
};