#ifndef SHEEP_OBJECT_ENEMY_TURRET_UTIL
#define SHEEP_OBJECT_ENEMY_TURRET_UTIL

#include "SheepObject.h"

/*
+=============================================+
+==============================================+
Object - Enemy - Turret Utility.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This class is an extension class. It allows any enemy to have a weapon that will shoot at the player
if within range.

This class is not needed for every AI, but the option is available.
The Base Enemy classes have a Method called AttachTurret, this is used to add a turret module on it
+==============================================+
+============================================+
*/

namespace Sheep
{
	class ObjectEnemyTurretUtil : public Object
	{
	public:
		ObjectEnemyTurretUtil(const std::string& name, unsigned int spriteId, unsigned int spriteFrameNumber, eTAG tag = NEUTRAL);
		ObjectEnemyTurretUtil(const std::string& name, int health, int damage, unsigned int spriteId, unsigned int spriteFrameNumber, const Vector2& position, const Rect& viewArea, const Vector2& viewAreaOffset, real maxRotateAngle, eTAG tag = NEUTRAL);
		
		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;
		void OnCollisionExit(Object* otherObject) override final;

	private:
		real mMaxRotation;
		Object* mTarget = nullptr;
	};
}

#endif