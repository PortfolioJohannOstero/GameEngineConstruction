#pragma once
#include "SheepObject.h"

namespace Sheep
{
	class SheepObjectScenery : public Object
	{
	public:
		SheepObjectScenery(const std::string& name, unsigned int spriteId, eTAG tag);
		SheepObjectScenery(const std::string& name, unsigned int speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		SheepObjectScenery(const std::string& name, unsigned int speed, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag);

		void Update() override final;
	};
}

