#ifndef SHEEP_OBJECT_PICKUP
#define SHEEP_OBJECT_PICKUP

#include "SheepObject.h"

namespace Sheep
{
	class ObjectPickup : public Object
	{
	public:
		ObjectPickup(const std::string& name, unsigned int spriteId, eTAG tag);
		ObjectPickup(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		ObjectPickup(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag);

		void Update() override final;
	};
}

#endif

