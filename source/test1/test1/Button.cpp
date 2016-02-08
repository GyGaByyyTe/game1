#include "Button.h"

Button::Button(SDL_Setup* passedSdlSetup, int x, int y, std::string buttonText)
{
    sdlSetup = passedSdlSetup;
    staticCamera = 0;

    text = buttonText;
    textSprite = new CSprite(sdlSetup->GetRenderer(),"error.png",x+10,y+7,250,40,&staticCamera,&staticCamera);
    textSprite->SetFontSize(20);
    textSprite->LoadFromText(text);

    buttonState = BS_UNCLICKED;

    buttonTextureClicked = new CSprite(sdlSetup->GetRenderer(),"button.png",x,y,250,40,&staticCamera,&staticCamera);
    buttonTextureClicked->SetCropping(0,20*0,117,20);
    buttonTextureUnclicked = new CSprite(sdlSetup->GetRenderer(),"button.png",x,y,250,40,&staticCamera,&staticCamera);
    buttonTextureUnclicked->SetCropping(0,20*1,117,20);
    buttonTextureMouseOver = new CSprite(sdlSetup->GetRenderer(),"button.png",x,y,250,40,&staticCamera,&staticCamera);
    buttonTextureMouseOver->SetCropping(0,20*2,117,20);

    wasClicked = false;
}

Button::~Button()
{

    delete buttonTextureClicked;
    delete buttonTextureMouseOver;
    delete buttonTextureUnclicked;
}

void Button::Update()
{
    int mouseX = sdlSetup->GetMainEvent()->button.x;
    int mouseY = sdlSetup->GetMainEvent()->button.y;

    if((buttonTextureClicked->GetX() <= mouseX && mouseX <= buttonTextureClicked->GetX() + buttonTextureClicked->GetWidth())
                                                 &&
    (buttonTextureClicked->GetY() <= mouseY && mouseY <= buttonTextureClicked->GetY() + buttonTextureClicked->GetHeight()))
    {
        if(sdlSetup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN)
        {
            if(sdlSetup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
            {
                buttonState = BS_CLICKED;
            }
        }
        else
        {
            if(buttonState == BS_CLICKED)
            {
                wasClicked = true;
            }
            if(buttonState == BS_MOUSE_OVER)
            {
                wasClicked = false;
            }
            buttonState = BS_MOUSE_OVER;
        }
    }
    else
    {
        buttonState = BS_UNCLICKED;
        wasClicked = false;
    }
}

void Button::Draw(GameMode gameMode)
{
    switch(buttonState)
    {
    case BS_CLICKED:
        textSprite->SetTextColor(100,100,100,0);//gray
        textSprite->LoadFromText(text);
        buttonTextureClicked->Draw(gameMode);
        break;
    case BS_MOUSE_OVER:
        buttonTextureMouseOver->Draw(gameMode);
        break;
    case BS_UNCLICKED:
        buttonTextureUnclicked->Draw(gameMode);
        break;
    default:
        break;
    }
    textSprite->Draw(gameMode);
    textSprite->SetTextColor(240,240,240,0);
    textSprite->LoadFromText(text);
}