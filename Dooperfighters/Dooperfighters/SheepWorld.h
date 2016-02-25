#ifndef SHEEP_WORLD
#define SHEEP_WORLD

/*
+=============================================+
+==============================================+
Sheep World.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This class handles everything that has to do with the world.
It handles updating every object, telling every object to render itself, passing custom messages to other objects.
Bullet managment.
It is blackboxed to clean up the main as much as possible. When initialised, the client can change maps,
and pass objects in using (wip) xml files
+==============================================+
+============================================+
*/

#include "SheepView.h"
#include <vector>
#include "SheepTag.h"

namespace Sheep
{
	#define WORLD Sheep::World::getInstance()

	// Custom message types, used to pass information around through the world
	enum eWorld_message_types
	{
		FIRE = 0,
	};


	class Object;
	class World
	{
	public:
		/* +==== Singleton - Construction ====+ */
		static void Create();
		static void Destroy();
		static World& getInstance() { return *INSTANCE; }

		bool Initialise(int screenWidth, int screenHeight);

		// loads any map specified (TODO: use xml files)
		void LoadLevel(unsigned int index);
		void ExecuteGameLoop(); // <--- When runned, the game loop will continue until it is turned off

		// Sets the speed of the object updates
		void SetFPS(unsigned int fps);

		// Handles custom message
		void SendMessage(eWorld_message_types messageType, const void* messenger);

	private:
		static World* INSTANCE;
		
		std::vector<Object*> mObjectList;
		std::vector<int> mBulletManager;
		int mFPS = 25;

		// Locates an inactive projectile and returns it to be activated
		Object* FindProjectile(eTAG projectileType);


		World() {}
		~World();

	};
}

#endif