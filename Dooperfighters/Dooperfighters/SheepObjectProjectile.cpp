#include "SheepObjectProjectile.h"
#include "SheepTransform2D.h"
#include "Rect.h"
#include "Utility.h"

using namespace Sheep;


ObjectProjectile::ObjectProjectile(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(const std::string& name, real speed, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, 1, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(const std::string& name, real speed, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, 1, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetActive(true);
}

void ObjectProjectile::Update()
{
	if (isActive())
	{
		// TODO: move into transform
		mPreviousTransform = transform;
		transform->Translate(transform->GetDirection(Right()) * mSpeed);

		if (transform->GetPosition().x < 0 || transform->GetPosition().x > VIEW.WindowBoundary().Width() ||
			transform->GetPosition().y < 0 || transform->GetPosition().y > VIEW.WindowBoundary().Height())
			SetActive(false);
	}
}


void ObjectProjectile::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == mTarget && otherObject->isActive())
	{
		SetActive(false);
		otherObject->SetActive(false);
	}
}

void ObjectProjectile::SetTarget(eTAG target)
{
	mTarget = target;
}