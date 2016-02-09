#include "SheepInput.h"

using namespace Sheep;

HAPI_TKeyboardData Input::mKeyData;
std::vector<HAPI_TControllerData*> Input::mControllerData;

void Input::SetupControllers()
{
	mControllerData.resize(HAPI->GetMaxControllers());
	for (int i = 0; i < mControllerData.size(); i++)
		mControllerData[i] = new HAPI_TControllerData;
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


	return mControllerData[controllerId]->digitalButtons[button];
}

bool Input::Controller_LeftAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir)
{
	if (controllerId > mControllerData.size() - 1)
		controllerId = mControllerData.size() - 1;

	switch (dir)
	{
	case LEFT:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case RIGHT:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case UP:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	case DOWN:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	default:
		return false;
	}
}

bool Input::Controller_RightAnalogueMoved(unsigned int controllerId, ANALOGUE_DIRECTION dir)
{
	if (controllerId > mControllerData.size() - 1)
		controllerId = mControllerData.size() - 1;

	switch (dir)
	{
	case LEFT:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case RIGHT:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_X] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case UP:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] < -HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
	case DOWN:
		return mControllerData[controllerId]->analogueButtons[HK_ANALOGUE_RIGHT_THUMB_Y] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE;
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
		HAPI->GetControllerData(i, cd);
		i++;
	}
}