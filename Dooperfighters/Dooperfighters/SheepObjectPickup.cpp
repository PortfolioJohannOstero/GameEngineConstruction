#include "SheepObjectPickup.h"
#include "SheepTransform2D.h"

using namespace Sheep;

ObjectPickup::ObjectPickup(unsigned int spriteId, eTAG tag) : Object(spriteId, tag)
{}

ObjectPickup::ObjectPickup(unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, position, spriteId, collisionBox, tag)
{}

ObjectPickup::ObjectPickup(unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, health, damage, x, y, spriteId, collisionBox, tag)
{}

void ObjectPickup::Update()
{
}