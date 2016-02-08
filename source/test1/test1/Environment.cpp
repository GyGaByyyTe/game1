#include "Environment.h"

const int NUMBER_FENCE = 16;
const int NUMBER_FLOOR = 12;
int size_modify = 2;

CEnvironment::CEnvironment(SDL_Setup* sdlSetup, int * passed_CameraX, int * passed_CameraY)
{
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			Stage[i][j] = nullptr;
		}
	}

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			Hallway[i][j] = nullptr;
		}
	}
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;
	// дорога
	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		fence[i] = new CSprite(sdlSetup->GetRenderer(), "zabor.png", 32*size_modify*i, 640, 32*size_modify, 32*size_modify, CameraX, CameraY);
	}
	// трава
	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		grass[i] = new CSprite(sdlSetup->GetRenderer(), "grass.png", 32*size_modify*i, 704, 32*size_modify, 32*size_modify, CameraX, CameraY);
	}

	//пустые слоты
	for (size_t i = 0; i < NUMBER_FLOOR; i++)
	{
		Stage[0][i] = new CSprite(sdlSetup->GetRenderer(), "empty.png", (32*size_modify*(NUMBER_FENCE-NUMBER_FLOOR)/2)+32*size_modify*i, 640, 32*size_modify, 32*size_modify, CameraX, CameraY);
	}
	// пол
	for (size_t i = 0; i < NUMBER_FLOOR; i++)
	{
		Hallway[0][i] = new CSprite(sdlSetup->GetRenderer(), "floor.png", (32*size_modify*(NUMBER_FENCE-NUMBER_FLOOR)/2)+32*size_modify*i, 704, 32*size_modify, 32*size_modify, CameraX, CameraY);
	}
	//входы в ТЦ смещены на 28 чтоб не перекрывали пол, а стыковались
	entrance[0] = new CSprite(sdlSetup->GetRenderer(), "e1.png", (32*(NUMBER_FENCE-NUMBER_FLOOR)/2 + 28), 640, 32*size_modify, 64*size_modify, CameraX, CameraY);
	entrance[1] = new CSprite(sdlSetup->GetRenderer(), "e2.png", (32*size_modify*(NUMBER_FENCE - (NUMBER_FENCE-NUMBER_FLOOR)/2) - 28), 640, 32*size_modify, 64*size_modify, CameraX, CameraY);

	inventory = new Inventory(sdlSetup,Stage,Hallway,CameraX,CameraY);
}


CEnvironment::~CEnvironment(void)
{
	SaveToFile();

	DeleteEnvironment();

    delete inventory;
}

void CEnvironment::DrawInvetory()
{
    inventory->DrawFront();
}

void CEnvironment::DrawBack(GameMode gameMode)
{
	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		fence[i]->Draw(gameMode);
	}
	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		grass[i]->Draw(gameMode);
	}

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if ( dynamic_cast<CSprite*>(Stage[i][j]) )
				(Stage[i][j])->Draw(gameMode);
		}
	}

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if ( dynamic_cast<CSprite*>(Hallway[i][j]) )
				(Hallway[i][j])->Draw(gameMode);
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		entrance[i]->Draw(gameMode);
	}

}

void CEnvironment::Update()
{
    if(gameMode == GM_LEVELEDIT)
    {
        inventory->Update();
    }
}

void CEnvironment::SaveToFile()
{
    std::string levelPath = "assets/save.txt";
    std::ofstream levelFile(levelPath.c_str());

    levelFile << "STAGE: " << std::endl;
	for (size_t i = 0; i < 6; i++)
	{
		levelFile << "stage " << i << ' ';

		for (size_t j = 0; j < 12; j++)
		{
				levelFile << "0 ";
		}

		levelFile <<';' << std::endl;
	}
    levelFile << ';' << std::endl;

    levelFile << "END";
    levelFile.close();

    std::cout << "level  saved!" << std::endl;
}

bool CEnvironment::LoadFromFile( GameMode passedGameMode)
{
    gameMode = passedGameMode;

    std::string levelPath = "assets/save.txt";
    std::ifstream levelFile(levelPath.c_str());
    if(levelFile.is_open())
    {
        DeleteEnvironment();

        int numberStage, numberOnStage;
        std::string type, textureFileName;
        char semicolon;

        while (levelFile.good())
        {
            levelFile >> type;
            if(type == "END")
            {
                std::cout << "level loaded!" << std::endl;
                return true;
            }
          
			while(true)
            {
				levelFile >> textureFileName >> numberStage;
				numberOnStage = 0;

				while(true)
				{
					levelFile >> semicolon;
					if(semicolon != ';')
					{

						inventory->PlaceNewStage(numberStage, numberOnStage);
						numberOnStage++;

					}
					else
					{
						break;
					}
				}

				levelFile >> semicolon;
				if(semicolon == ';')
				{
					break;
				}
			}
        }
    }
    else
    {
        std::cout << "Can't open level !" << std::cout;
    }
    return false;
}

void CEnvironment::DeleteEnvironment()
{

	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		delete fence[i];
	}
	for (size_t i = 0; i < NUMBER_FENCE; i++)
	{
		delete grass[i];
	}

	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if(dynamic_cast<CSprite*>(Stage[i][j]))
				delete Stage[i][j];
		}
	}
	for (size_t i = 0; i < 6; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			if(dynamic_cast<CSprite*>(Hallway[i][j]))
				delete Hallway[i][j];
		}
	}

	for (size_t i = 0; i < 2; i++)
	{
		delete entrance[i];
	}

}