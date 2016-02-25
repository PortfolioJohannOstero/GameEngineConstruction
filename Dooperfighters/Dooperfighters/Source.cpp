//#include <HAPI_lib.h>

#include "SheepView.h"
#include "SheepWorld.h"
#include "SheepInput.h"

#include "SheepDebug.h"
#include "SheepDebugMessage.h"
#include "Vector2.h"

void HAPI_Main()
{
	WORLD.Create();
	if (WORLD.Initialise(1080, 800))
	{
		DEBUG_MESSAGE.Create();
		DEBUG_MESSAGE.Initialise(Sheep::Vector2(8, 20), 10, 10);
		DEBUG_MESSAGE.DisplayTimeStamp(false);

		Sheep::Debug::DisplayFPS(true, 8, 8);		
		WORLD.LoadLevel(0);
		WORLD.SetFPS(25);

		Sheep::Input::SetupControllers();
		WORLD.ExecuteGameLoop();
	}

	Sheep::Input::CleanControllerSetup();
	WORLD.Destroy();
	DEBUG_MESSAGE.Destroy();
}