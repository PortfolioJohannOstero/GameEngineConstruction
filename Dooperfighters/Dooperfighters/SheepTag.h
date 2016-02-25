#ifndef SHEEPTAG
#define SHEEPTAG

/*
+=============================================+
+==============================================+
Sheep eTag.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This enum list stores every possible object enum. More can be added on the fly as they are needed.
It is simply a means of passing information around and comparisons.
+==============================================+
+============================================+
*/

namespace Sheep
{
	enum eTAG
	{
		NEUTRAL = 0,
		ENEMY,
		PLAYER,
		PICKUP,
		PROJECTILE_BULLET,
		PROJECTILE_MISSILE,
		PROJECTILE_BOMB
	};
}


#endif