#include "MainMenu.h"
#include "Game.h"
#undef main

int main(int argc, char * argv[])
{
    bool wholeProgramRunning = true;
    SDL_Setup sdlSetup;

    CMainMenu mainMenu(&sdlSetup);
    Game game(&sdlSetup);	

    while(wholeProgramRunning)
    {
		std::cout << " Menu loaded " << std::endl;
        if(mainMenu.Loop(wholeProgramRunning))
        {
            if(game.LoadMap(mainMenu.GetGameMode()))
            {
				game.GameLoop(wholeProgramRunning);
			}

        }
    }
	
	return 0;
}
