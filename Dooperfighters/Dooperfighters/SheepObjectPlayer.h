#ifndef SHEEP_OBJECT_PLAYER
#define SHEEP_OBJECT_PLAYER

#include "SheepObject.h"
#include "SheepControls.h"
#include "Vector2.h"

namespace Sheep
{
	class Ammo;
	class ObjectPlayer : public Object
	{
	public:
		ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag, const Ammo& ammo);
		ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag, const Ammo& ammo);
		ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag, const Ammo& ammo);
		~ObjectPlayer();

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;
		void OnCollisionExit(Object* otherObject) override final;

		/* +==== Controls ====+ */
		void SetControls(const PlayerControls& controls);
		void SetControls(unsigned int left, unsigned int right, unsigned int up, unsigned int down, unsigned int fire);

		/* +=== Projectile handling ===+ */
		/* NOTE: it moves with the player */
		void SetProjectileSpawnPoint(const Vector2& point);
		Vector2 GetProjectileSpawnPoint() const;

		void AddAmmo(int ammoCount);
		eTAG GetAmmoType() const;

	private:
		PlayerControls mControls;
		Vector2 mProjectileSpawnPoint; // <--- default is in the center of the collision box

		Ammo* mProjectile_machineGun;

	};
}

#endif

