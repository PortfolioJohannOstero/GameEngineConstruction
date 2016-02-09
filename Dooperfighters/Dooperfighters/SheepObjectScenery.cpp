#include "SheepObjectScenery.h"

using namespace Sheep;

SheepObjectScenery::SheepObjectScenery(const std::string& name, unsigned int spriteId, eTAG tag) : Object(name, spriteId, tag)
{}

SheepObjectScenery::SheepObjectScenery(const std::string& name, unsigned int speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, 1, 1, position, spriteId, collisionBox, tag)
{}

SheepObjectScenery::SheepObjectScenery(const std::string& name, unsigned int speed, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag)
	: Object(name, speed, 1, 1, x, y, spriteId, collisionBox, tag)
{}

void SheepObjectScenery::Update()
{

}