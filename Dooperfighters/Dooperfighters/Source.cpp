#include <HAPI_lib.h>

#include "SheepView.h"
#include "Vector2.h"
#include "SheepTransform2D.h"
#include "Rect.h"

#include "SheepWorld.h"
#include "SheepInput.h"

//#include "SheepObject.h"
#include "SheepObjectPlayer.h"

#include "SheepSprite.h"
#include "SheepAnimator.h"

//int random(int min, int max)
//{
//	return min + std::rand() % ((max + 1) - min);
//}

void HAPI_Main()
{
	WORLD.Create();
	if (WORLD.Initialise(800, 600))
	{
		VIEW.Debug_DisplayFPS(true, 8, 8);
		WORLD.LoadLevel(0);
		WORLD.SetFPS(25);

		Sheep::Input::SetupControllers();
		WORLD.ExecuteGameLoop();
	}

	Sheep::Input::CleanControllerSetup();
	WORLD.Destroy();
}