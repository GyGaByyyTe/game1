#include "Sprite.h"
#include <string>

const std::string CSprite::SPRITE_FOLDER_PATH = "assets/";

CSprite::CSprite(SDL_Renderer * passed_renderer, std::string filePath, int x, int y, int w, int h, int * passed_CameraX, int * passed_CameraY)
{
	//sprite
	renderer = passed_renderer;
	texture = NULL;
	textureFileName = filePath;
    filePath = SPRITE_FOLDER_PATH + filePath;
	texture = IMG_LoadTexture(renderer,filePath.c_str());

	if (texture == NULL)
	{
		std::cout << "can't load image "<< filePath.c_str() << std::endl;
	}

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(texture,NULL,NULL,&imgSizeW,&imgSizeH);

	//animation
	crop.x = 0;
	crop.y = 0;
	crop.w = imgSizeW;
	crop.h = imgSizeH;

    currentFrame = -1;
    animationTimeCheck = SDL_GetTicks();

    rotationAngle = 0;

	//camera
	cameraX = passed_CameraX;
	cameraY = passed_CameraY;


    font = TTF_OpenFont("fonts/agency fb.ttf",14);
    if(font == NULL)
    {
        std::cout << "Can't load data/agency fb.ttf" << std::endl;
    }
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);

    textColor.r = 240;
    textColor.g = 240;
    textColor.b = 240;
    textColor.a = 0;
}


CSprite::~CSprite(void)
{
	SDL_DestroyTexture(texture);
}

void CSprite::Draw(GameMode passedGameMode)
{

    SDL_Rect tempRect;
    tempRect = rect;
    tempRect.x -= *cameraX;
    tempRect.y -= *cameraY;
    SDL_RenderCopyEx(renderer,texture,&crop,&tempRect,rotationAngle,NULL,SDL_FLIP_NONE);

	if(passedGameMode == GM_LEVELEDIT)
	{
        SDL_SetRenderDrawColor(renderer,0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect position;
        position.x = tempRect.x;
        position.y = tempRect.y;
        position.w = rect.w;
        position.h = rect.h;
        SDL_RenderDrawRect(renderer,&position);
        SDL_SetRenderDrawColor(renderer,0x00, 0x00, 0x00, 0x00);
	}
}

void CSprite::SetUpAnimation(int AmountFramesX, int AmountFramesY)
{
    amountFramesX = AmountFramesX;
    amountFramesY = AmountFramesY;
    crop.x = 0;
    crop.y = 0;
    crop.w = imgSizeW/amountFramesX;
    crop.h = imgSizeH/amountFramesY;
}

void CSprite::PlayAnimation(unsigned int beginFrame, unsigned int endFrame, unsigned int row, unsigned int delay)
{
    if(!((beginFrame == endFrame) && (endFrame == currentFrame)))//the same frame
    {
        if((animationTimeCheck + delay) < SDL_GetTicks())
        {
            if(currentFrame > endFrame)
                currentFrame = beginFrame;

            crop.x = imgSizeW/amountFramesX * currentFrame;
            crop.y = imgSizeH/amountFramesY * row;
            crop.w = imgSizeW/amountFramesX;
            crop.h = imgSizeH/amountFramesY;

            currentFrame++;
            animationTimeCheck = SDL_GetTicks();
        }
    }
}

void CSprite::SetCropping(int x, int y, int w, int h)
{
    crop.x = x;
    crop.y = y;
    crop.w = w;
    crop.h = h;
}

void CSprite::LoadFromText(std::string text)
{
    SDL_DestroyTexture(texture);

    text += " ";

    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
    if( textSurface == NULL )
    {
        std::cout << "Can't render text: " + text + SDL_GetError() << std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            std::cout << "Can't create texture from rendered text: " + text << std::endl;
        }
        else
        {
            rect.w = textSurface->w;
            rect.h = textSurface->h;
            SDL_QueryTexture(texture,NULL,NULL,&imgSizeW,&imgSizeH);
            crop.w = imgSizeW;
            crop.h = imgSizeH;
        }

        SDL_FreeSurface( textSurface );
    }
}

void CSprite::SetFontSize(int fontSize)
{
    TTF_CloseFont(font);
    font = TTF_OpenFont("fonts/agency fb.ttf",fontSize);
    if(font == NULL)
    {
         std::cout << "Can't load fonts/agency fb.ttf. Font size: " + to_string<int>(fontSize) << std::endl;
    }
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);
}