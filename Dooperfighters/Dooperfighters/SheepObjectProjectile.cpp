#include "SheepObjectProjectile.h"
#include "SheepTransform2D.h"
#include "Rect.h"

using namespace Sheep;


ObjectProjectile::ObjectProjectile(unsigned int spriteId, eTAG tag) : Object(spriteId, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, position, spriteId, collisionBox, tag)
{
	SetActive(true);
}

ObjectProjectile::ObjectProjectile(unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, x, y, spriteId, collisionBox, tag)
{
	SetActive(true);
}

void ObjectProjectile::Update()
{
	
	if (isActive())
	{
		// TODO: move into transform
		mPreviousTransform = transform;

		transform->Translate(mSpeed, 0);

		if (transform->GetPosition().x < 0 || transform->GetPosition().x > VIEW.WindowBoundary().Width() ||
			transform->GetPosition().y < 0 || transform->GetPosition().y > VIEW.WindowBoundary().Height())
			SetActive(false);
	}
}


void ObjectProjectile::OnCollisionEnter(Object* otherObject)
{
	if (otherObject->GetTag() == PLAYER)
		SetActive(false);
}