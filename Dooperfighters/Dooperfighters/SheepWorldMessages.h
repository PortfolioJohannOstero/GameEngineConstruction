#ifndef SHEEP_WORLD_MESSAGES
#define SHEEP_WORLD_MESSAGES

/*
+=============================================+
+==============================================+
Sheep World Message.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This file is here to store every custom message type that can be passed int the worlds Message System
+==============================================+
+============================================+
*/

namespace Sheep
{
	enum eTAG;
	class ObjectPlayer;
	// Allows for any object to shoot any type of projectile.
	struct WorldMessage_Fire
	{
		Object* messenger = nullptr;
		eTAG target;
		eTAG projectileType;
		Vector2 firePoint;

		WorldMessage_Fire(Object* sender, eTAG bulletTarget, eTAG typeOfProjectile, const Vector2 spawnPoint)
			: messenger(sender), target(bulletTarget), projectileType(typeOfProjectile), firePoint(spawnPoint){}
	};
}

#endif