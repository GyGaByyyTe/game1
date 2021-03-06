#include "Inventory.h"
#include <fstream>


const int INVENTORY_X = 0;
const int INVENTORY_Y = 0;


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

	currentItem = NUMBER_OF_ITEMS;

	sdlSetup = passedSdlSetup;

	itemFrame = new CSprite(sdlSetup->GetRenderer(),"itemFrame.png",INVENTORY_X,INVENTORY_Y,int(22*2.5),int(142*2.5),&staticCamera,&staticCamera);
	itemFrame->SetCropping(0,0,22,142);
	currentItemFrame = new CSprite(sdlSetup->GetRenderer(),"itemFrame.png",INVENTORY_X-3,INVENTORY_Y-3,int(25*2.5),int(24*2.5),&staticCamera,&staticCamera);
	currentItemFrame->SetCropping(22,0,25,24);

	newBlockPosX = sdlSetup->GetMainEvent()->button.x;
	newBlockPosY = sdlSetup->GetMainEvent()->button.y;
	drawNewBlockSelection = false;

	items[ITEM_STAGE] = new Item("empty",64,64,sdlSetup->GetRenderer(),1,INVENTORY_X,INVENTORY_Y);
	items[ITEM_DELETE] = new Item("delete",64,64,sdlSetup->GetRenderer(),2,INVENTORY_X,INVENTORY_Y);

	itemWidth = items[ITEM_STAGE]->GetDefaultW();
	itemHeight = items[ITEM_STAGE]->GetDefaultH();

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
	drag_icon =new CSprite(sdlSetup->GetRenderer(),items[currentItem]->GetTexturePath()+".png",newBlockPosX - *cameraX,newBlockPosY - *cameraY,
		items[currentItem]->GetDefaultW(),items[currentItem]->GetDefaultH(),cameraX,cameraY);
	drag_icon->Draw(GM_GAMEPLAY);
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
			if ((newBlockPosX >= 128) && (newBlockPosX <= 896)
				&& // ���� ���� ������� ���� � �������� ����������� �����
				(newBlockPosY >= 160) && (newBlockPosY <= 704))
			{
				switch (currentItem) {
				case ITEM_STAGE:
					PlaceNew(newBlockPosX,newBlockPosY, items[currentItem]->GetTexturePath() + ".png");
					break;
				case ITEM_DELETE:
					DeletePlace(newBlockPosX,newBlockPosY);
					break;
				default:
					break;
				}
			}
			else
			{
				drawNewBlockSelection = false;
				currentItem = NUMBER_OF_ITEMS;
			}
		}
	}
}

void Inventory::FindStage(const int * passedX, const int * passedY, int * isStage, int * isOnStage)
{
	if ((*passedX >= 128) && (*passedX <= 896)
		&& // ����, ���� ������� ���� � �������� ����������� �����
		(*passedY >= 160) && (*passedY <= 704))
	{
		if((*passedX % (32*size_modify)) <= 32 )
		{
			//�����
			*isOnStage = (*passedX - 128) / 64;
		}
		else
		{
			//������
			*isOnStage = (*passedX - 64) / 64;
		}
		if((*passedY % 96) <= 48 )
		{
			//�����
			*isStage = (*passedY - 128) / 96;
			*isStage = abs(5-*isStage);
		}
		else
		{
			//������
			*isStage = (*passedY - 96) / 96;
			*isStage = abs(5-*isStage);
		}	
		//std::cout << *isStage << ' ' << *isOnStage << std::endl;
	}
}

void Inventory::DeletePlace(int x, int y)
{
	int numberStage = 0, numberOnStage = 0;

	FindStage(&x,&y,&numberStage,&numberOnStage);
	//�������� �������� �� �������������, ���� �� ������� 100��� 
	delete Hallway[numberStage][numberOnStage];
	delete Stage[numberStage][numberOnStage];
	Hallway[numberStage][numberOnStage] = nullptr;
	Stage[numberStage][numberOnStage] = nullptr;
}

void Inventory::PlaceNew(int x, int y, std::string filePath)
{
	int numberStage = 0, numberOnStage = 0;

	FindStage(&x,&y,&numberStage,&numberOnStage);
		//�������� �������� �� ������������� �� ��� �� ����� ���� �� ID, ���� �� ��������������� 100��� ���� � �����
	Hallway[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(),"floor.png", (32*size_modify*( NUMBER_FENCE - NUMBER_FLOOR)/2)+32*size_modify*numberOnStage, 704-96*numberStage, 32*size_modify, 32*size_modify, cameraX, cameraX);
	Stage[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(), filePath, (32*size_modify*(NUMBER_FENCE-NUMBER_FLOOR)/2)+32*size_modify*numberOnStage, 640-96*numberStage, 32*size_modify, 32*size_modify, cameraX, cameraY);
}

void Inventory::PlaceNewStage(int numberStage, int numberOnStage)
{
	Hallway[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(), "floor.png", (32*size_modify*(NUMBER_FENCE-NUMBER_FLOOR)/2)+32*size_modify*numberOnStage, 704-96*numberStage, 32*size_modify, 32*size_modify, cameraX, cameraX);
	Stage[numberStage][numberOnStage] = new CSprite(sdlSetup->GetRenderer(), "empty.png", (32*size_modify*(NUMBER_FENCE-NUMBER_FLOOR)/2)+32*size_modify*numberOnStage, 640-96*numberStage, 32*size_modify, 32*size_modify, cameraX, cameraY);
}

void Inventory::UpdateNewBlockSelection()
{
	int mouseX = sdlSetup->GetMainEvent()->button.x + *cameraX;
	int mouseY = sdlSetup->GetMainEvent()->button.y + *cameraY;

	if (currentItem != NUMBER_OF_ITEMS )
	{
		if(sdlSetup->GetMainEvent()->type == SDL_MOUSEMOTION)
		{
			if((INVENTORY_X + *cameraX <= mouseX && mouseX <= INVENTORY_X+itemFrame->GetWidth() + *cameraX)
				&&
				(INVENTORY_Y + *cameraY <= mouseY && mouseY <= INVENTORY_Y+itemFrame->GetHeight() + *cameraY))
			{
				drawNewBlockSelection = false;
			}
			else
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
		}
		else if(sdlSetup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			drawNewBlockSelection = false;
			currentItem = NUMBER_OF_ITEMS;
		}
	}
}

void Inventory::ShowAvailablePlace()
{

	//available_places
	SDL_Rect tempRect;
	tempRect.x = newBlockPosX - *cameraX;
	tempRect.y = newBlockPosY - *cameraY;
	tempRect.w = items[currentItem]->GetDefaultW();
	tempRect.h = items[currentItem]->GetDefaultH();

	SDL_SetRenderDrawColor(sdlSetup->GetRenderer(),255,0,0,0);
	SDL_RenderDrawRect(sdlSetup->GetRenderer(),&tempRect);
	SDL_SetRenderDrawColor(sdlSetup->GetRenderer(),0,0,0,0);

}