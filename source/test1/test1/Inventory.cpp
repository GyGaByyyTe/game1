#include "Inventory.h"
#include <fstream>


const int INVENTORY_X = 585;
const int INVENTORY_Y = 10;

Inventory::Inventory(SDL_Setup *passedSdlSetup,
                     std::array< std::array<CSprite*, 12 >, 6 > & passedStage,
                     std::array< std::array<CSprite*, 12 >, 6 > & passedHallway,
                     int *passedCameraX, int *passedCameraY):
    Stage(passedStage),
    Hallway(passedHallway)

{
    cameraX = passedCameraX;
    cameraY = passedCameraY;
    staticCamera = 0;

    currentItem = 0;

    sdlSetup = passedSdlSetup;

    itemFrame = new CSprite(sdlSetup->GetRenderer(),"itemFrame.png",INVENTORY_X,INVENTORY_Y,22*2.5,142*2.5,&staticCamera,&staticCamera);
    itemFrame->SetCropping(0,0,22,142);
    currentItemFrame = new CSprite(sdlSetup->GetRenderer(),"itemFrame.png",INVENTORY_X-3,INVENTORY_Y-3,25*2.5,24*2.5,&staticCamera,&staticCamera);
    currentItemFrame->SetCropping(22,0,25,24);

    newBlockPosX = sdlSetup->GetMainEvent()->button.x;
    newBlockPosY = sdlSetup->GetMainEvent()->button.y;
    drawNewBlockSelection = false;

    items[ITEM_STAGE] = new Item("empty",64,64,sdlSetup->GetRenderer(),3,INVENTORY_X,INVENTORY_Y);
    items[ITEM_HALLWAY] = new Item("floor",64,64,sdlSetup->GetRenderer(),2,INVENTORY_X,INVENTORY_Y);

    itemWidth = items[ITEM_HALLWAY]->GetDefaultW();
    itemHeight = items[ITEM_HALLWAY]->GetDefaultH();

    tileMode = false;
}

Inventory::~Inventory()
{
    for(int i=0;i<NUMBER_OF_ITEMS;++i)
    {
        delete items[i];
    }
}

void Inventory::DrawFront()
{
    if(drawNewBlockSelection)
    {
        DrawNewBlockSelection();
    }

    itemFrame->Draw(GM_GAMEPLAY);
    for(int i=0; i<NUMBER_OF_ITEMS; ++i)
    {
        items[i]->DrawIcon();
    }
    currentItemFrame->Draw(GM_GAMEPLAY);
}

void Inventory::DrawBack()
{

}

void Inventory::DrawNewBlockSelection()
{
    SDL_Rect tempRect;
    tempRect.x = newBlockPosX - *cameraX;
    tempRect.y = newBlockPosY - *cameraY;
    tempRect.w = items[currentItem]->GetDefaultW();
    tempRect.h = items[currentItem]->GetDefaultH();

    SDL_SetRenderDrawColor(sdlSetup->GetRenderer(),255,0,0,0);
    SDL_RenderDrawRect(sdlSetup->GetRenderer(),&tempRect);
    SDL_SetRenderDrawColor(sdlSetup->GetRenderer(),0,0,0,0);
}

void Inventory::Update()
{
    UpdateNewBlockSelection();

    int mouseX = sdlSetup->GetMainEvent()->button.x + *cameraX;
    int mouseY = sdlSetup->GetMainEvent()->button.y + *cameraY;

    if(sdlSetup->KeyWasPressed(SDL_SCANCODE_LCTRL))
    {
        tileMode = !tileMode;
    }

    if(sdlSetup->MouseButtonLeftWasPressed())
    {
        if((INVENTORY_X + *cameraX <= mouseX && mouseX <= INVENTORY_X+itemFrame->GetWidth() + *cameraX)
                                                &&
            (INVENTORY_Y + *cameraY <= mouseY && mouseY <= INVENTORY_Y+itemFrame->GetHeight() + *cameraY))
        {
            for(int i=0;i<NUMBER_OF_ITEMS;++i)
            {
                if(INVENTORY_Y+50*i+5 + *cameraY <= mouseY && mouseY < INVENTORY_Y+50*i+5+60 + *cameraY)
                {
                    currentItem = i;
                    itemWidth = items[currentItem]->GetDefaultW();
                    itemHeight = items[currentItem]->GetDefaultH();
                    currentItemFrame->SetY(INVENTORY_Y+50*i-3);
                }
            }
        }
        else if(drawNewBlockSelection)
        {
            switch (currentItem) {
            case ITEM_STAGE:
                //PlaceNewStage(newBlockPosX,newBlockPosY,itemWidth,itemHeight, items[currentItem]->GetTexturePath() + ".png");
                break;
            case ITEM_HALLWAY:
                //PlaceNewHallway(newBlockPosX,newBlockPosY,itemWidth,itemHeight, items[currentItem]->GetTexturePath() + ".png");
                break;
            default:
                break;
            }
        }
    }

    /*if(sdlSetup->KeyWasPressed(SDL_SCANCODE_DELETE))
    {
        switch (currentItem)
        {
        case ITEM_STAGE:
            if(!Empty[2].empty())
            {
                delete Empty[2].back();
                Empty[2].pop_back();
            }
            break;
        case ITEM_FLOOR:
            if(!Floor[2].empty())
            {
                delete Floor[2].back();
                Floor[2].pop_back();
            }
            break;
        default:
            break;
        }
    }*/
}


void Inventory::PlaceNewStage(int numberStage, int numberOnStage)
{
    Stage[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(),"empty.png",64,64,64,64,cameraX,cameraY);
}

void Inventory::PlaceNewHallway(int numberStage, int numberOnStage)
{
    Hallway[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(),"floor.png",64,64,64,64,cameraX,cameraY);
}

void Inventory::UpdateNewBlockSelection()
{
    int mouseX = sdlSetup->GetMainEvent()->button.x + *cameraX;
    int mouseY = sdlSetup->GetMainEvent()->button.y + *cameraY;

    if(sdlSetup->GetMainEvent()->type == SDL_MOUSEMOTION)
    {
        if(tileMode)
        {
            newBlockPosX = mouseX - (mouseX%items[currentItem]->GetDefaultW());
            newBlockPosY = mouseY - (mouseY%items[currentItem]->GetDefaultH());
            if(mouseX<0)
            {
                newBlockPosX -= items[currentItem]->GetDefaultW();
            }
            if(mouseY<0)
            {
                newBlockPosY -= items[currentItem]->GetDefaultH();
            }
        }
        else
        {
            newBlockPosX = mouseX - items[currentItem]->GetDefaultW()/2;
            newBlockPosY = mouseY - items[currentItem]->GetDefaultH()/2;
        }
        drawNewBlockSelection = true;
    }
    else if(sdlSetup->GetMainEvent()->type == SDL_KEYDOWN)
    {
        drawNewBlockSelection = false;
    }
}
