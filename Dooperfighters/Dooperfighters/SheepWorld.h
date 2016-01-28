#ifndef SHEEP_WORLD
#define SHEEP_WORLD

#include "SheepView.h"
#include <vector>

namespace Sheep
{
	#define WORLD Sheep::World::getInstance()

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

	private:
		static World* INSTANCE;
		
		std::vector<Object*> mObjectList;
		int mFPS = 25;
		
		World() {}
		~World();

	};
}

#endif