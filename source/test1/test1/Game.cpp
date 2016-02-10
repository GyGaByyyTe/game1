#include "Game.h"

Game::Game(SDL_Setup* passedSdlSetup)
{
	running = true;
	paused = false;

	cameraX = 0;
	cameraY = 0;

	staticCamera = 0;

	sdlSetup = passedSdlSetup;

	pauseMenu = new PauseMenu(sdlSetup,paused,running);

	environment = new CEnvironment(sdlSetup, &cameraX, &cameraY);

	shade = new CSprite(sdlSetup->GetRenderer(),std::string("layer.png"),0,0,768,640, &staticCamera, &staticCamera);

}

Game::~Game()
{

	delete pauseMenu;
	delete environment;
	delete shade;
}

void Game::GameLoop(bool& wholeProgramRunning)
{
	ResetTheGameLoop();

	while(running)
	{
		sdlSetup->Begin();

		if(sdlSetup->GetMainEvent()->type == SDL_QUIT)
		{
			wholeProgramRunning = false;
			running = false;
		}

		if(sdlSetup->KeyWasPressed(SDL_SCANCODE_ESCAPE))
		{
			paused = !paused;
		}
		if(paused)
		{
			pauseMenu->Update();
		}
		else
		{
			environment->Update();
		}


		environment->DrawBack(gameMode);

		if(paused)
		{
			pauseMenu->Draw(GM_GAMEPLAY);
		}
		else if(gameMode == GM_LEVELEDIT)
		{
			environment->DrawInvetory();
		}

		sdlSetup->End();
	}

	environment->SaveToFile();

}

bool Game::LoadMap(GameMode passedGameMode)
{
	std::cout << "map loaded"<< std::endl;
	gameMode = passedGameMode;
	if(environment->LoadFromFile(gameMode))
	{
		return true;
	}
	return false;
}

void Game::ResetTheGameLoop()
{
	running = true;
	paused = false;
}
