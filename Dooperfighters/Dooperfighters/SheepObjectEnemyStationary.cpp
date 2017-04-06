#include "SheepObjectEnemyStationary.h"
#include "SheepObjectEnemyTurretUtil.h"
#include "SheepTransform2D.h"
#include "Vector2.h"

using namespace Sheep;

/* +=== Constructors ====+ */
#pragma region CONSTRUCTORS
ObjectEnemyStationary::ObjectEnemyStationary(const std::string& name, unsigned int spriteId, eTAG tag)
	: Object(name, spriteId, tag)
{}
ObjectEnemyStationary::ObjectEnemyStationary(const std::string& name, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, 0, health, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{}

ObjectEnemyStationary::ObjectEnemyStationary(const std::string& name, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, 0, health, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{}
#pragma endregion Constructors

ObjectEnemyTurretUtil* ObjectEnemyStationary::AttachTurret(int damage, int spriteFrameNumber, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG target)
{
	if (mTurret == nullptr)
	{
		mTurret = new ObjectEnemyTurretUtil(mName + ": Turret", 1, damage, mSpriteId, spriteFrameNumber, transform->GetPosition(), viewArea, viewAreaOffset, maxRotateAngle);
		mTurret->AddCollisionTag(target);
	}
	
	return mTurret;
}

void ObjectEnemyStationary::Update()
{
	if (mIsActive)
	{
		if (mHealth < 0)
		{
			mIsActive = false;
			mTag = eTAG::NEUTRAL;

			if (mTurret != nullptr)
				mTurret->SetActive(false);
		}
	}
}

void ObjectEnemyStationary::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == eTAG::PLAYER)
		otherObject->TakeDamage(mCollisionDamage);
}