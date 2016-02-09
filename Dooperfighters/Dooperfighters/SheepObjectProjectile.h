#ifndef SHEEP_OBJECT_PROJECTILE
#define SHEEP_OBJECT_PROJECTILE

#include "SheepObject.h"

namespace Sheep
{
	class ObjectProjectile : public Object
	{
	
	public:
		ObjectProjectile(const std::string& name, unsigned int spriteId, eTAG tag);
		ObjectProjectile(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		ObjectProjectile(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		
		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;	
	};
}

#endif