#include "SheepObjectProjectile_Bomb.h"
#include "SheepTransform2D.h"
#include "Rect.h"
#include "SheepPhysics.h"

using namespace Sheep;



ObjectProjectile_Bomb::ObjectProjectile_Bomb(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{
	SetActive(true);
}

ObjectProjectile_Bomb::ObjectProjectile_Bomb(const std::string& name, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, 0, 1, damage, position, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetActive(true);
}

ObjectProjectile_Bomb::ObjectProjectile_Bomb(const std::string& name, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, 0, 1, damage, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{
	SetActive(true);
}

void ObjectProjectile_Bomb::Update()
{
	if (isActive())
	{
		transform->Translate(Physics::GetGravityVector());

		if (transform->GetPosition().x < 0 || transform->GetPosition().x > VIEW.WindowBoundary().Width() ||
			transform->GetPosition().y < 0 || transform->GetPosition().y > VIEW.WindowBoundary().Height())
			SetActive(false);
	}
}


void ObjectProjectile_Bomb::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == mTarget && otherObject->isActive())
		otherObject->TakeDamage(mCollisionDamage);
}

void ObjectProjectile_Bomb::SetTarget(eTAG target)
{
	mTarget = target;
}
