#include "SheepObjectEnemyFollow.h"
#include "SheepObjectEnemyTurretUtil.h"
#include "SheepTransform2D.h"
#include "Vector2.h"

using namespace Sheep;

/* +=== Constructors ====+ */
#pragma region CONSTRUCTORS
ObjectEnemyFollow::ObjectEnemyFollow(const std::string& name, unsigned int spriteId, eTAG tag)
	: Object(name, spriteId, tag)
{}
ObjectEnemyFollow::ObjectEnemyFollow(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{}

ObjectEnemyFollow::ObjectEnemyFollow(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{}

#pragma endregion Constructors

void ObjectEnemyFollow::SetTarget(Transform2D* targetCoord)
{
	mTargetCoord = targetCoord;
}

ObjectEnemyTurretUtil* ObjectEnemyFollow::AttachTurret(int damage, int spriteFrameNumber, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG target)
{
	if (mTurret == nullptr)
	{
		mTurret = new ObjectEnemyTurretUtil(mName + ": Turret", 1, damage, mSpriteId, spriteFrameNumber, transform->GetPosition(), viewArea, viewAreaOffset, maxRotateAngle);
		mTurret->AddCollisionTag(target);
	}

	return mTurret;
}

void ObjectEnemyFollow::Update()
{
	if (mIsActive)
	{
		if (mHealth < 0)
		{
			mIsActive = false;
			mTag = eTAG::NEUTRAL;

			if (mTurret != nullptr)
				mTurret->SetActive(false);
			return;
		}

		if (mTargetCoord != nullptr)
		{
			const Vector2& pos = transform->GetPosition();
			const Vector2& targetPos = mTargetCoord->GetPosition();

			float x = 0;
			float y = 0;
			if (targetPos.x > pos.x)
				x = mSpeed;
			else if (targetPos.x < pos.x)
				x = -mSpeed;

			if (targetPos.y > pos.y)
				y = mSpeed;
			else if (targetPos.y < pos.y)
				y = -mSpeed;

			transform->Translate(x, y);
		}
	}
}

void ObjectEnemyFollow::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == eTAG::PLAYER)
		otherObject->TakeDamage(mCollisionDamage);
}