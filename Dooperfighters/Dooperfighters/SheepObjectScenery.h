#pragma once
#include "SheepObject.h"

/*
+=============================================+
+==============================================+
Object - Scenery.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The scenery object is extremely simple and and it's only purpose is aesthetics, such as background.
+==============================================+
+============================================+
*/

namespace Sheep
{
	class SheepObjectScenery : public Object
	{
	public:
		SheepObjectScenery(const std::string& name, unsigned int spriteId, eTAG tag);
		SheepObjectScenery(const std::string& name, real speed, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);
		SheepObjectScenery(const std::string& name, real speed, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);

		void Update() override final;
	};
}

