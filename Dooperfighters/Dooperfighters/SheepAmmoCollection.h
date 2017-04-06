#ifndef SHEEP_AMMO_COLLECTION
#define SHEEP_AMMO_COLLECTION

/*
+=============================================+
+==============================================+
Ammo Collection.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The AmmoCollection struct is simply a means of grouping all of the possible weapons the client can use,
more can easily be added as one sees fit (keep in mind that the new projectile_type needs to be added to the eTAGS)
+==============================================+
+============================================+
*/

#include "SheepAmmo.h"

namespace Sheep
{
	class AmmoCollection
	{
	public:
		Ammo bullets;
		Ammo missiles;
		Ammo bombs;
	};
}

#endif