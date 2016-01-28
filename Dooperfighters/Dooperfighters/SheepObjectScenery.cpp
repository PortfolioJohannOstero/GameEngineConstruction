#include "SheepObjectScenery.h"

using namespace Sheep;

SheepObjectScenery::SheepObjectScenery(unsigned int spriteId, eTAG tag) : Object(spriteId, tag)
{}

SheepObjectScenery::SheepObjectScenery(unsigned int speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, 1, 1, position, spriteId, collisionBox, tag)
{}

SheepObjectScenery::SheepObjectScenery(unsigned int speed, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(speed, 1, 1, x, y, spriteId, collisionBox, tag)
{}

void SheepObjectScenery::Update()
{

}