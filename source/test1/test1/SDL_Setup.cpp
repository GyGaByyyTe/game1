#include "SDL_Setup.h"

SDL_Setup::SDL_Setup()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    SDL_StartTextInput();
    window = NULL;
    window = SDL_CreateWindow("Mall",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768, SDL_WINDOW_SHOWN );
    if(window == NULL)
    {
        std::cout << "Can't create the Window" << std::endl;
    }

    renderer = NULL;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::cout << "Can't create the Renderer" << std::endl;
    }

    mainEvent = new SDL_Event();

    newEventHappened = false;
}

SDL_Setup::~SDL_Setup()
{

    SDL_StopTextInput();

    delete mainEvent;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}

SDL_Renderer* SDL_Setup::GetRenderer()
{
    return renderer;
}

SDL_Event* SDL_Setup::GetMainEvent()
{
    return mainEvent;
}

void SDL_Setup::Begin()
{
    if(SDL_PollEvent(this->GetMainEvent()) == 1)
    {
        newEventHappened = true;
    }
    else
    {
        newEventHappened = false;
    }

    SDL_RenderClear(this->GetRenderer());

}

void SDL_Setup::End()
{

    SDL_RenderPresent(GetRenderer());
    SDL_Delay(10);
}

SDL_Rect SDL_Setup::GetWindowRect()
{
    SDL_Rect windowRect;
    windowRect.x=0;
    windowRect.y=0;
    windowRect.w=0;
    windowRect.h=0;
    SDL_GetWindowSize(window,&windowRect.w,&windowRect.h);
    SDL_GetWindowPosition(window,&windowRect.x,&windowRect.y);

    return windowRect;
}

bool SDL_Setup::KeyWasPressed(int key)
{
    if(newEventHappened)
    {
        if(GetMainEvent()->type == SDL_KEYDOWN)
        {
            if(GetMainEvent()->key.keysym.scancode == key)
            {
                return true;
            }
        }
    }

    return false;
}

bool SDL_Setup::MouseButtonLeftWasPressed()
{
    if(newEventHappened)
    {
        if(GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
        {
            if(GetMainEvent()->button.button == SDL_BUTTON_LEFT)
            {
                return true;
            }
        }
    }

    return false;
}

