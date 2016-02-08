#pragma once

#include "Button.h"

class CMainMenu
{

public:
    CMainMenu(SDL_Setup* passedSdlSetup);
    ~CMainMenu();

    bool Loop(bool& wholeProgramRunning);

    GameMode GetGameMode(){return gameMode;}

private:
    void ResetTheLoop(){running = true; }

    CSprite* background;
    CSprite* title;

    Button* playButton;
    Button* editButton;
    Button* newButton;

    SDL_Setup* sdlSetup;
    bool running;
    int staticCamera;

    GameMode gameMode;

};

