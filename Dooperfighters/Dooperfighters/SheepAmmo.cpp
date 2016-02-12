#include "SheepAmmo.h"
#include <HAPI_lib.h>

using namespace Sheep;

Ammo::Ammo(unsigned int maxAmmo, float fireRate, eTAG ammoType, int currentAmmo)
	: mMaxAmmo(maxAmmo), mFireRate(fireRate), mAmmoType(ammoType)
{
	mCurrentAmmoCount = (currentAmmo < 0) ? mMaxAmmo : currentAmmo;
}

Ammo::Ammo(const Ammo& cpy)
{
	*this = cpy;
}

Ammo& Ammo::operator = (const Ammo& rhs)
{
	mCurrentAmmoCount = rhs.mCurrentAmmoCount;
	mMaxAmmo = rhs.mMaxAmmo;
	mFireRate = rhs.mFireRate;
	mAmmoType = rhs.mAmmoType;

	return *this;
}


bool Ammo::Shoot()
{
	if (!HasAmmo())
		return false;

	mCurrentAmmoCount--;
	return true;
}

/* +==== Getters ====+ */
#pragma region GETTERS
bool Ammo::HasAmmo() const
{
	return mCurrentAmmoCount > 0;
}

int Ammo::GetAmmoCount() const
{
	return mCurrentAmmoCount;
}

eTAG Ammo::GetAmmoType() const
{
	return mAmmoType;
}
#pragma endregion GETTERS

/* +==== Setters ====+ */
void Ammo::AddAmmo(int ammoCount)
{
	mCurrentAmmoCount += ammoCount;

	if ((unsigned int)mCurrentAmmoCount > mMaxAmmo)
		mCurrentAmmoCount = mMaxAmmo;	
}
