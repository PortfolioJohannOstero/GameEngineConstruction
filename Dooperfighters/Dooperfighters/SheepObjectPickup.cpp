#include "SheepObjectPickup.h"
#include "SheepTransform2D.h"

using namespace Sheep;

ObjectPickup::ObjectPickup(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{}

ObjectPickup::ObjectPickup(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, position, spriteId, collisionBox, tag)
{}

ObjectPickup::ObjectPickup(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, health, damage, x, y, spriteId, collisionBox, tag)
{}

void ObjectPickup::Update()
{
}