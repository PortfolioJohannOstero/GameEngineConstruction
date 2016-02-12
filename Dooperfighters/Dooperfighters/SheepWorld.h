#ifndef SHEEP_WORLD
#define SHEEP_WORLD

#include "SheepView.h"
#include <vector>
#include "SheepTag.h"

namespace Sheep
{
	#define WORLD Sheep::World::getInstance()

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

		void LoadLevel(unsigned int index);
		void ExecuteGameLoop();

		void SetFPS(unsigned int fps);

		void SendMessage(eWorld_message_types messageType, const void* messenger);
		Object* FindProjectile(eTAG projectileType);

	private:
		static World* INSTANCE;
		
		std::vector<Object*> mObjectList;
		int mFPS = 25;

		World() {}
		~World();

	};
}

#endif