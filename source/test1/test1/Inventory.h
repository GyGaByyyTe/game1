#pragma once


#include "sdl_setup.h"
#include "item.h"
#include <list>
#include <array>


enum ITEMS
{
	ITEM_STAGE,
	ITEM_DELETE,
	NUMBER_OF_ITEMS
};

class Inventory
{

public:
	Inventory(SDL_Setup* passedSdlSetup,
		std::array< std::array<CSprite*, 12 >, 6 > & passedStage,
		std::array< std::array<CSprite*, 12 >, 6 > & passedHallway,
		int* passedCameraX, int* passedCameraY);
	~Inventory();
	void Update();
	void DrawFront();
	void DrawBack();

	void DeletePlace(int x, int y);
	void PlaceNew(int x, int y, std::string filePath);
	void PlaceNewStage(int numberStage, int i);

	void ShowAvailablePlace();

private:

	void FindStage(const int * passedX, const int * passedY, int * isStage, int * isOnStage);
	void DrawNewBlockSelection();
	void UpdateNewBlockSelection();

	std::array< std::array<CSprite*, 12 >, 6 > & Stage;
	std::array< std::array<CSprite*, 12 >, 6 > & Hallway;

	Item* items[NUMBER_OF_ITEMS];
	int currentItem;

	bool tileMode;
	CSprite* itemFrame;
	CSprite* currentItemFrame;

	int itemWidth;
	int itemHeight;

	int newBlockPosX;
	int newBlockPosY;
	bool drawNewBlockSelection;
	CSprite * drag_icon;

	std::list<SDL_Rect *> available_places;

	int* cameraX;
	int* cameraY;
	SDL_Setup* sdlSetup;
	int staticCamera;
};

