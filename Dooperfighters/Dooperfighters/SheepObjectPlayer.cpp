#include "SheepObjectPlayer.h"
#include "SheepTransform2D.h"
#include "Rect.h"

#include "SheepInput.h"

using namespace Sheep;

ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{}

ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, tag)
{}

ObjectPlayer::ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, tag)
{}

void ObjectPlayer::Update()
{
	mPreviousTransform = transform;

	if (Input::Key_isPressed(HK_LEFT) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::LEFT))
		transform->Translate(-1 * mSpeed, 0);
	else if (Input::Key_isPressed(HK_RIGHT) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::RIGHT))
		transform->Translate(mSpeed, 0);

	if (Input::Key_isPressed(HK_UP) || Input::Controller_LeftAnalogueMoved(0, Sheep::ANALOGUE_DIRECTION::UP))
		transform->Translate(0, -1 * mSpeed);
	else if (Input::Key_isPressed(HK_DOWN) || Input::Controller_LeftAnalogueMoved(0,Sheep::ANALOGUE_DIRECTION::DOWN))
		transform->Translate(0, mSpeed);
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