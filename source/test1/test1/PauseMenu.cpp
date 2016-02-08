#include "PauseMenu.h"

PauseMenu::PauseMenu(SDL_Setup* sdlSetup, bool& passedGamePaused, bool& passedRunning) : gamePaused(passedGamePaused), gameLoopRunning(passedRunning)
{
    staticCamera = 0;
    label = new CSprite(sdlSetup->GetRenderer(),"error.png",400,50,4000,200,&staticCamera,&staticCamera);
    label->SetFontSize(70);
    label->SetTextColor(220,220,220,0);
    label->LoadFromText("PAUSED");

    background = new CSprite(sdlSetup->GetRenderer(),"layer.png",0,0,1024,768,&staticCamera,&staticCamera);

    resumeButton = new Button(sdlSetup,387,384,"              Resume");
    exitButton = new Button(sdlSetup,387,434,"                 Exit");
}

PauseMenu::~PauseMenu()
{
    delete label;
    delete exitButton;
    delete resumeButton;
    delete background;
}

void PauseMenu::Update()
{
    resumeButton->Update();
    exitButton->Update();

    if(resumeButton->WasClicked())
    {
        gamePaused = false;
    }

    if(exitButton->WasClicked())
    {
        gameLoopRunning = false;
    }
}

void PauseMenu::Draw(GameMode gameMode )
{
    background->Draw(gameMode);
    label->Draw(gameMode);
    resumeButton->Draw(gameMode);
    exitButton->Draw(gameMode);
}