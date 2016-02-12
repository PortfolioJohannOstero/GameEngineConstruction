#ifndef SHEEP_AMMO
#define SHEEP_AMMO

#include "SheepTag.h"

namespace Sheep
{
	class Ammo
	{
	public:
		/* +=== Constructors ===+ */
		Ammo(unsigned int maxAmmo, float fireRate, eTAG ammoType, int currentAmmo = -1);
		Ammo(const Ammo& cpy);
		Ammo& operator = (const Ammo& rhs);

		/* +=== Shooting ===+*/
		/* NOTE: Will decrease the current count, but will not shoot an actual bullet.
			Returns true or false depending on if there are any bullets left or if reloading */
		bool Shoot();

		/* +=== Getters ===+ */
		bool HasAmmo() const;
		float GetFireRate() const;
		int GetAmmoCount() const;
		eTAG GetAmmoType() const;

		/* +=== Setters ===+ */
		void AddAmmo(int ammoCount);

	private:
		int mCurrentAmmoCount;
		unsigned int mMaxAmmo;
		float mFireRate;
		
		eTAG mAmmoType;
	};
}

#endif