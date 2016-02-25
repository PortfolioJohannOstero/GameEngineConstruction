#ifndef SHEEP_OBJECT_PROJECTILE
#define SHEEP_OBJECT_PROJECTILE

/*
+=============================================+
+==============================================+
Object - Projectile.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is a very simple object, this is the object used for every single projectile.
uppon activation the object, it will automatically just travel in whatever direction given.
if it hits a player or an enemy, it'll will take of some health

if a bullet leaves the screen or if it hits anything it will automatically deactivate itself
+==============================================+
+============================================+
*/

#include "SheepObject.h"

namespace Sheep
{
	class ObjectProjectile : public Object
	{
	
	public:
		ObjectProjectile(const std::string& name, unsigned int spriteId, eTAG tag);
		ObjectProjectile(const std::string& name, real speed, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);
		ObjectProjectile(const std::string& name, real speed, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);
		
		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;

		void SetTarget(eTAG target);

	private:
		eTAG mTarget;
	};
}

#endif