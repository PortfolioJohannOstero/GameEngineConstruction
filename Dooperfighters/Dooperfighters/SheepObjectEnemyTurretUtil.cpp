#include "SheepObjectEnemyTurretUtil.h"
#include "SheepTransform2D.h"
#include "Vector2.h"
#include "Rect.h"

#include "SheepWorld.h"
#include "SheepWorldMessages.h"

using namespace Sheep;

ObjectEnemyTurretUtil::ObjectEnemyTurretUtil(const std::string& name, unsigned int spriteId, unsigned int spriteFrameNumber, eTAG tag)
	: Object(name, spriteId, tag)
{
	mFrameNumber = spriteFrameNumber;
	mMaxRotation = 90;
}
ObjectEnemyTurretUtil::ObjectEnemyTurretUtil(const std::string& name, int health, int damage, unsigned int spriteId, unsigned int spriteFrameNumber, const Vector2& position, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG tag)
	: Object(name, 0, health, damage, Vector2(0,0), spriteId, viewArea, viewAreaOffset, tag)
{
	mFrameNumber = spriteFrameNumber;
	mMaxRotation = maxRotateAngle;
	transform->SetPosition(position);
}

void ObjectEnemyTurretUtil::Update()
{
	if (mTarget != nullptr && mIsActive)
	{
		WORLD.SendMessage(eWorld_message_types::FIRE, &WorldMessage_Fire(this, eTAG::PLAYER, eTAG::PROJECTILE_BULLET, transform->GetPosition()));
	}
}

void ObjectEnemyTurretUtil::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == eTAG::PLAYER)
		mTarget = otherObject;
		
}

void ObjectEnemyTurretUtil::OnCollisionExit(Object* otherObject)
{
	if (otherObject->GetTag() == eTAG::PLAYER)
		mTarget = nullptr;
}