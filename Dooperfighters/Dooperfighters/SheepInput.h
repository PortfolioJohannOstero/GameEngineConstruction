#ifndef SHEEP_INPUT
#define SHEEP_INPUT

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