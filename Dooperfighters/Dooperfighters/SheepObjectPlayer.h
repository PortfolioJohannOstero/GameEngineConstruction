#ifndef SHEEP_OBJECT_PLAYER
#define SHEEP_OBJECT_PLAYER

/*
+=============================================+
+==============================================+
Object - Player.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is the player object. it is the most intense object.
It supports ammunition, custom player controls and Pseudo physics.
+==============================================+
+============================================+
*/

#include "SheepObject.h"
#include "SheepControls.h"
#include "Vector2.h"

namespace Sheep
{
	class AmmoCollection;
	class ObjectPlayer : public Object
	{
	public:
		ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag, const AmmoCollection& ammo);
		ObjectPlayer(const std::string& name, real speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag, const AmmoCollection& ammo);
		ObjectPlayer(const std::string& name, real speed, int health, int damage, real x, real y, unsigned int spriteId, const Rect& collisionBox, const Vector2& collisionBoxOffset, eTAG tag, const AmmoCollection& ammo);
		~ObjectPlayer();

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;

		/* +==== Controls ====+ */
		void SetControls(const PlayerControls& controls);
		void SetControls(unsigned int left, unsigned int right, unsigned int up, unsigned int down, unsigned int fire_bullet, unsigned int fire_missile, unsigned int fire_bomb);

		/* +=== Projectile handling ===+ */
		/* NOTE: it moves with the player */
		void SetProjectileSpawnPoint(const Vector2& point);
		Vector2 GetProjectileSpawnPoint() const;

		void AddAmmo(int ammoCount, eTAG ammoType);
	private:
		PlayerControls mControls;
		Vector2 mProjectileSpawnPoint; // <--- default is in the center of the collision box

		AmmoCollection* mProjectiles;

		real mCurrentSpeed = 1.f;
	};
}

#endif

