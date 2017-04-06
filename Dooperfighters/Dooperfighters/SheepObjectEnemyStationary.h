#ifndef SHEEP_OBCJECT_ENEMY_STATIONARY
#define SHEEP_OBCJECT_ENEMY_STATIONARY

/*
+=============================================+
+==============================================+
Object - Enemy - Stationary.h
Engine: Sheep Engine
Author: J�hann �ster�.
--
This enemy, will never move, but does allow for a turret utility, that will shoot it's given target 
if within range
+==============================================+
+============================================+
*/

#include "SheepObject.h"

namespace Sheep
{
	class ObjectEnemyTurretUtil;
	class ObjectEnemyStationary : public Object
	{
	public:
		ObjectEnemyStationary(const std::string& name, unsigned int spriteId, eTAG tag = NEUTRAL);
		ObjectEnemyStationary(const std::string& name, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);
		ObjectEnemyStationary(const std::string& name, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);

		/* Allows the client to add a turret module to the ai, allowing him to shoot at it's target, independently */
		ObjectEnemyTurretUtil* AttachTurret(int damage, int spriteFrameNumber, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG target);

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;

	private:
		ObjectEnemyTurretUtil* mTurret = nullptr;
	};
}


#endif