#pragma once
#include "base.h"
#include "Inventory.h"
#include <fstream>
#include <array>
#include <vector>

class CEnvironment
{

public:
	CEnvironment(SDL_Setup* sdlSetup, int * passed_CameraX, int * passed_CameraY);
	~CEnvironment(void);
	void DrawInvetory();
	void DrawBack(GameMode gameMode);
	void Update();

	void SaveToFile();
	bool LoadFromFile(GameMode passedGameMode);



private:

	void DeleteEnvironment();

	int * CameraX;
	int * CameraY;

	CSprite * fence[16]; 
	CSprite * grass[16]; 

	CSprite * entrance[2]; 

	std::array< std::array<CSprite*, 12 >, 6 > Stage;  // тут будут магазины
	std::array< std::array<CSprite*, 12 >, 6 > Hallway; // тут будет пол

	Inventory * inventory;

	GameMode gameMode;
};

