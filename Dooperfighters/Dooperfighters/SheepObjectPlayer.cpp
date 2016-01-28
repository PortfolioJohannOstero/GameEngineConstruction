#include "SheepObjectPlayer.h"
#include "SheepTransform2D.h"
#include "Rect.h"

using namespace Sheep;

ObjectPlayer::ObjectPlayer(unsigned int spriteId, eTAG tag) : Object(spriteId, tag)
{}

ObjectPlayer::ObjectPlayer(unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, position, spriteId, collisionBox, tag)
{}

ObjectPlayer::ObjectPlayer(unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, x, y, spriteId, collisionBox, tag)
{}

void ObjectPlayer::Update()
{
	HAPI->GetKeyboardData(&mKeyData);
	HAPI->GetControllerData(0, &mControllerData);

	mPreviousTransform = transform;

	if (mKeyData.scanCode[HK_LEFT])
		transform->Translate(-1 * mSpeed, 0);
	else if (mKeyData.scanCode[HK_RIGHT])
		transform->Translate(mSpeed, 0);

	if (mKeyData.scanCode[HK_UP])
		transform->Translate(0, -1 * mSpeed);
	else if (mKeyData.scanCode[HK_DOWN])
		transform->Translate(0, mSpeed);

	///* x - axis */
	//if (keyData.scanCode[HK_LEFT] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE))
	//	transform->Translate(-mSpeed, 0);
	//else if (keyData.scanCode[HK_RIGHT] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE))
	//	transform->Translate(mSpeed, 0);

	///* y - axis */
	//if (keyData.scanCode[HK_UP] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE))
	//	transform->Translate(0, -mSpeed);
	//else if (keyData.scanCode[HK_DOWN] || (controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_RIGHT_THUMB_DEADZONE))
	//	transform->Translate(0, mSpeed);

}


void ObjectPlayer::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == PICKUP)
		otherObject->SetActive(false);

}

void ObjectPlayer::OnCollisionExit(Object* otherObject)
{
	if (otherObject->GetTag() == PICKUP)
		otherObject->SetActive(true);
}