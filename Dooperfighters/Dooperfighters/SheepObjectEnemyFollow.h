#ifndef SHEEP_OBJECT_ENEMY_FOLLOW
#define SHEEP_OBJECT_ENEMY_FOLLOW

/*
+=============================================+
+==============================================+
Object - Enemy - Stationary.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This enemy, will follow a target, but does allow for a turret utility, that will shoot it's given target
if within range
+==============================================+
+============================================+
*/

#include "SheepObject.h"

namespace Sheep
{
	class ObjectEnemyTurretUtil;
	class ObjectEnemyFollow : public Object
	{
	public:
		ObjectEnemyFollow(const std::string& name, unsigned int spriteId, eTAG tag = NEUTRAL);
		ObjectEnemyFollow(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);
		ObjectEnemyFollow(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag = NEUTRAL);
		
		void SetTarget(Transform2D* targetCoord);

		/* Allows the client to add a turret module to the ai, allowing him to shoot at it's target, independently */
		ObjectEnemyTurretUtil* AttachTurret(int damage, int spriteFrameNumber, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG target);

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;

	private:
		Transform2D* mTargetCoord;
		ObjectEnemyTurretUtil* mTurret = nullptr;
	};
}


#endif