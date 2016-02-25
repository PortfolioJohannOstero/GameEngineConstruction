#ifndef SHEEP_INPUT
#define SHEEP_INPUT

/*
+=============================================+
+==============================================+
Sheep Input.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is a static class that allows for the user to check for keyboard and xbox controller inputs.
This class is a build on HAPI's already setup Input handler.
This one is more of an extension of it.

It automatically handles hot-pluggeable xbox controllers, and handles the deadzone on the xbox analogues behind the scenes,
cleaning up other code. It also makes sure that any input will all be collected from one central location, making updating inputs much easier and cleaner.
+==============================================+
+============================================+
*/

#include <HAPI_lib.h>
#include <vector>

namespace Sheep
{
	enum ANALOGUE_DIRECTION
	{
		LEFT, RIGHT, UP, DOWN
	};

	struct Controller
	{
		HAPI_TControllerData Data;
		bool isPluggedIn = false;
	};

	class Input
	{
	public:
		static int Key_isPressed(unsigned int key);
		static int Controller_isPressed(unsigned int controllerId, unsigned int button);
		static bool Controller_LeftAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir);
		static bool Controller_RightAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir);

		static void CheckInput();

		static void SetupControllers();
		static void CleanControllerSetup();

	private:
		static HAPI_TKeyboardData mKeyData;
		static std::vector<Controller*> mControllerData;
	};
}


#endif