#include "SheepObjectEnemyPatrol.h"
#include "SheepObjectEnemyTurretUtil.h"
#include "SheepTransform2D.h"
#include "Vector2.h"
#include "Rect.h"

using namespace Sheep;

/* +=== Constructors ====+ */
#pragma region CONSTRUCTORS
ObjectEnemyPatrol::ObjectEnemyPatrol(const std::string& name, unsigned int spriteId, eTAG tag)
	: Object(name, spriteId, tag)
{}
ObjectEnemyPatrol::ObjectEnemyPatrol(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{}

ObjectEnemyPatrol::ObjectEnemyPatrol(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{}

ObjectEnemyPatrol::~ObjectEnemyPatrol()
{
	for (auto& point : mPoints)
	{
		delete point;
		point = nullptr;
	}
	mPoints.clear();
}

#pragma endregion Constructors

ObjectEnemyTurretUtil* ObjectEnemyPatrol::AttachTurret(int damage, int spriteFrameNumber, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG target)
{
	if (mTurret == nullptr)
	{
		mTurret = new ObjectEnemyTurretUtil(mName + ": Turret", 1, damage, mSpriteId, spriteFrameNumber, transform->GetPosition(), viewArea, viewAreaOffset, maxRotateAngle);
		mTurret->AddCollisionTag(target);
	}

	return mTurret;
}


void ObjectEnemyPatrol::AddPatrolPoint(const Vector2& point)
{
	mPoints.push_back(new Vector2(point));
}

void ObjectEnemyPatrol::Update()
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

		if (mPoints.size() > 0)
		{
			Vector2& pos = transform->GetPosition();

			if (mCurrentIndex >= mPoints.size())
				mCurrentIndex = 0;

			float x = 0;
			float y = 0;
			if (mPoints[mCurrentIndex]->x > pos.x)
				x = mSpeed;
			else if (mPoints[mCurrentIndex]->x < pos.x)
				x = -mSpeed;

			if (mPoints[mCurrentIndex]->y > pos.y)
				y = mSpeed;
			else if (mPoints[mCurrentIndex]->y < pos.y)
				y = -mSpeed;

			transform->Translate(x, y);

			if (mPoints[mCurrentIndex]->x == pos.x && mPoints[mCurrentIndex]->y == pos.y)
				mCurrentIndex++;
		}
	}
}

void ObjectEnemyPatrol::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == eTAG::PLAYER)
		otherObject->TakeDamage(mCollisionDamage);
}