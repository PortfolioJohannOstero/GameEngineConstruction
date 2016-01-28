#pragma once
#include "SheepObject.h"

namespace Sheep
{
	class SheepObjectScenery : public Object
	{
	public:
		SheepObjectScenery(unsigned int spriteId, eTAG tag);
		SheepObjectScenery(unsigned int speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		SheepObjectScenery(unsigned int speed, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag);

		void Update() override final;
	};
}

