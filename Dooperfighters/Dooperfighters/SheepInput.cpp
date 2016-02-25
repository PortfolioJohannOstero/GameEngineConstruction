#include "SheepInput.h"
#include "SheepDebugMessage.h"

using namespace Sheep;

HAPI_TKeyboardData Input::mKeyData;
std::vector<Controller*> Input::mControllerData;

void Input::SetupControllers()
{
	mControllerData.resize(HAPI->GetMaxControllers());
	for (unsigned int i = 0; i < mControllerData.size(); i++)
		mControllerData[i] = new Controller;
}

void Input::CleanControllerSetup()
{
	for (auto& cd : mControllerData)
	{
		delete cd;
		cd = nullptr;
	}
	mControllerData.clear();
}


int Input::Key_isPressed(unsigned int key)
{
	return mKeyData.scanCode[key];
}

int Input::Controller_isPressed(unsigned int controllerId, unsigned int button)
{
	if (controllerId > mControllerData.size() - 1)
		controllerId = mControllerData.size() - 1;


	return mControllerData[controllerId]->Data.digitalButtons[button];
}

bool Input::Controller_LeftAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir)
{
	if (controllerId > mControllerData.size() - 1)
		controllerId = mControllerData.size() - 1;

	if (!mControllerData[controllerId]->isPluggedIn)
		return false;

	switch (dir)
	{
	case LEFT:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case RIGHT:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case UP:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case DOWN:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	default:
		return false;
	}
}

bool Input::Controller_RightAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir)
{
	if (controllerId > mControllerData.size() - 1)
		controllerId = mControllerData.size() - 1;

	if (!mControllerData[controllerId]->isPluggedIn)
		return false;

	switch (dir)
	{
	case LEFT:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case RIGHT:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case UP:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case DOWN:
		return mControllerData[controllerId]->Data.analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	default:
		return false;
	}
}

void Input::CheckInput()
{
	HAPI->GetKeyboardData(&mKeyData);

	int i = 0;
	for (auto cd : mControllerData)
	{
		const bool prevState = cd->isPluggedIn;
		cd->isPluggedIn = HAPI->GetControllerData(i, &cd->Data);

		if (prevState == false && cd->isPluggedIn == true)
			DEBUG_MESSAGE.PushMessage("Controller " + std::to_string(i) + " plugged in", MESSAGE_TYPE::WARNING);
		else if (prevState == true && cd->isPluggedIn == false)
			DEBUG_MESSAGE.PushMessage("Controller " + std::to_string(i) + " plugged out", MESSAGE_TYPE::WARNING);

		i++;
	}
}