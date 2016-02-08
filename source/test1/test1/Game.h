#pragma once

#include "pausemenu.h"
#include "Environment.h"

class Game
{
public:
    Game(SDL_Setup* passedSdlSetup);
    ~Game();
    void GameLoop(bool& wholeProgramRunning);
	void SetGameMode(GameMode passedGameMode);
    bool LoadMap(GameMode passedGameMode);

private:
    void ResetTheGameLoop();

    bool running;
    bool paused;

    SDL_Setup* sdlSetup;

    GameMode gameMode;

    PauseMenu* pauseMenu;

    int cameraX;
    int cameraY;

    int staticCamera;

    CEnvironment* environment;

    CSprite* shade;

};