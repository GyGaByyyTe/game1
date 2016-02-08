#pragma once
#include "base.h"
#include "SDL_Setup.h"

class CSprite
{
public:
	
	CSprite(SDL_Renderer* renderer, std::string filePath, int x, int y, int w, int h, int * passed_CameraX, int * passed_CameraY);
	~CSprite(void);

	void Draw(GameMode passedGameMode);

    void SetX(int x){rect.x = x;}
    void SetY(int y){rect.y = y;}
    void SetWidth(int w){rect.w = w;}
    void SetCropping(int x, int y, int w, int h);
    void Rotate(int angle){rotationAngle = angle;}
    const int& GetX() const{return rect.x;}
    const int& GetY() const{return rect.y;}
    int GetDownY(){return (rect.y + rect.h);}
    int GetWidth(){return rect.w;}
    int GetHeight(){return rect.h;}
    SDL_Rect GetRect(){return rect;}

    void LoadFromText(std::string text);
    void SetFontSize(int fontSize);
    void SetTextColor(int r,int g,int b,int a){textColor.r = r; textColor.g = g; textColor.b = b; textColor.a = a;}
    std::string GetTextureFileName(){return textureFileName;}

    int GetImgSizeW(){return imgSizeW;}
    int GetImgSizeH(){return imgSizeH;}
    void PlayAnimation(unsigned int beginFrame, unsigned int endFrame, unsigned int row, unsigned int delay);
    void SetUpAnimation(int AmountFramesX, int AmountFramesY);

private:

    SDL_Texture* texture;

    int* cameraX;
    int* cameraY;

    SDL_Rect rect;
    SDL_Rect crop;

    int imgSizeW;
    int imgSizeH;

    int rotationAngle;

    SDL_Renderer* renderer;

    unsigned int currentFrame;
    unsigned int animationTimeCheck;

    unsigned int amountFramesX;
    unsigned int amountFramesY;

    std::string textureFileName;
    TTF_Font* font;
    SDL_Color textColor;

    static const std::string SPRITE_FOLDER_PATH;

};

