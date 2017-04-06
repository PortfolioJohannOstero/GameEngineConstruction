#ifndef SHEEP_PROJECTILE_BOMB
#define SHEEP_PROJECTILE_BOMB

/*
+=============================================+
+==============================================+
Object - Projectile_Bomb.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is a very simple object, this is the object used for every single projectile_bomb.
uppon activation the object, it will automatically just drop straight down
if it hits a player or an enemy, it'll will take of some health

if a bomb leaves the screen or if it hits anything it will automatically deactivate itself
+==============================================+
+============================================+
*/

#include "SheepObject.h"

namespace Sheep
{
	class ObjectProjectile_Bomb : public Object
	{

	public:
		ObjectProjectile_Bomb(const std::string& name, unsigned int spriteId, eTAG tag);
		ObjectProjectile_Bomb(const std::string& name, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);
		ObjectProjectile_Bomb(const std::string& name, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag);

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;

		void SetTarget(eTAG target);

	private:
		eTAG mTarget;
	};
}

#endif