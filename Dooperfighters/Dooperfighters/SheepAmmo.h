#ifndef SHEEP_AMMO
#define SHEEP_AMMO

/*
+=============================================+
+==============================================+
Ammo.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This class is more of a support class. It doesn't actually do anything regarding shooting,
instead it emulates the use of ammunition, which allows the client to check a boolean themselves (to see if there are any bullets left or not),
it also allows for a firerate mechanic, to prevent rappid fire (WIP)
+==============================================+
+============================================+
*/

#include "SheepTag.h"

namespace Sheep
{
	class Ammo
	{
	public:
		/* +=== Constructors ===+ */
		Ammo();
		Ammo(unsigned int maxAmmo, float fireRate, eTAG ammoType, int currentAmmo = -1);
		Ammo(const Ammo& cpy);
		Ammo& operator = (const Ammo& rhs);

		/* +=== Shooting ===+*/
		/* NOTE: Will decrease the current count, but will not shoot an actual bullet.
			Returns true or false depending on if there are any bullets left */
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
		float mCurrTime = 0;

		eTAG mAmmoType;
	};
}

#endif