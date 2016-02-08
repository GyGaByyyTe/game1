#pragma once

#include "Sprite.h"

class Item
{
public:
    Item(std::string defaultTexturePath, int DefaultW, int DefaultH, SDL_Renderer* renderer, int iconCrop, const int passed_INVENTORY_X, const int passed_INVENTORY_Y);
    ~Item();
    void DrawIcon();
    int GetDefaultW(){return defaultW;}
    int GetDefaultH(){return defaultH;}
    std::string GetTexturePath(){return texturePath;}
    void SetTexturePath(std::string newTexturePath);

private:
    CSprite* icon;
    int defaultW;
    int defaultH;
    static int count;

    std::string texturePath;

    const int INVENTORY_X;
    const int INVENTORY_Y;

    int staticCamera;
};

