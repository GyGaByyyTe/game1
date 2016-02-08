#include "MainMenu.h"

CMainMenu::CMainMenu(SDL_Setup* passedSdlSetup)
{
    running = true;
    sdlSetup = passedSdlSetup;
    staticCamera = 0;

    playButton = new Button(sdlSetup,387,384,"               Play");
    editButton = new Button(sdlSetup,387,434,"               Edit");

    background = new CSprite(sdlSetup->GetRenderer(),"background.png",0,0,1024,768,&staticCamera,&staticCamera);
    title = new CSprite(sdlSetup->GetRenderer(),"title.png",232,0,560,113,&staticCamera,&staticCamera);
}

CMainMenu::~CMainMenu()
{
    delete background;
    delete title;
    delete playButton;
    delete editButton;
}

bool CMainMenu::Loop(bool& wholeProgramRunning)
{
    ResetTheLoop();
    while(running)
    {
        if(sdlSetup->GetMainEvent()->type == SDL_QUIT)
        {
            wholeProgramRunning = false;
            running = false;
        }

        sdlSetup->Begin();

        background->Draw(GM_GAMEPLAY);
        title->Draw(GM_GAMEPLAY);

        playButton->Update();
        editButton->Update();

        playButton->Draw(GM_GAMEPLAY);
        editButton->Draw(GM_GAMEPLAY);

        if(playButton->WasClicked() || sdlSetup->KeyWasPressed(SDL_SCANCODE_RETURN))
        {
            gameMode = GM_GAMEPLAY;
            running = false;
            return true;
        }
        if(editButton->WasClicked())
        {
            gameMode = GM_LEVELEDIT;
            running = false;
            return true;
        }

        sdlSetup->End();
    }
    return false;
}