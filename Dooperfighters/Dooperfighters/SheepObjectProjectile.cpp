#include "SheepObjectProjectile.h"
#include "SheepTransform2D.h"
#include "Rect.h"
#include "Utility.h"

using namespace Sheep;


ObjectProjectile::ObjectProjectile(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, tag)
{
	SetActive(true);
}

void ObjectProjectile::Update()
{
	if (isActive())
	{
		// TODO: move into transform
		mPreviousTransform = transform;

		float angle = toRadian<float>(transform->GetRotation());
		int x = roundFromHalf(sin(angle));
		int y = roundFromHalf(cos(angle));

		transform->Translate(Vector2(x,y) * mSpeed);

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