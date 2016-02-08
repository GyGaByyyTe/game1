#pragma once

#include "Sprite.h"

enum ButtonState
{
    BS_UNCLICKED,
    BS_MOUSE_OVER,
    BS_CLICKED
};

class Button
{

public:
    Button(SDL_Setup* passedSdlSetup, int x, int y, std::string buttonText);
    ~Button();
    void Update();
    void Draw(GameMode gameMode);
    bool WasClicked(){return wasClicked;}

private:
    ButtonState buttonState;
    CSprite* buttonTextureClicked;
    CSprite* buttonTextureUnclicked;
    CSprite* buttonTextureMouseOver;

    bool wasClicked;

    std::string text;
    CSprite* textSprite;

    SDL_Setup* sdlSetup;
    int staticCamera;
};

