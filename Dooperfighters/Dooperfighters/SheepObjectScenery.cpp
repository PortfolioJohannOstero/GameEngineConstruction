#include "SheepObjectScenery.h"
#include "SheepTransform2D.h"
using namespace Sheep;

SheepObjectScenery::SheepObjectScenery(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{}

SheepObjectScenery::SheepObjectScenery(const std::string& name, real speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, 0, 1, position, spriteId, collisionBox, collisionBoxOffset, tag)
{}

SheepObjectScenery::SheepObjectScenery(const std::string& name, real speed, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag)
	: Object(name, speed, 0, 1, x, y, spriteId, collisionBox, collisionBoxOffset, tag)
{}

void SheepObjectScenery::Update()
{
}