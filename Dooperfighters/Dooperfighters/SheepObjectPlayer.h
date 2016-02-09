#ifndef SHEEP_OBJECT_PLAYER
#define SHEEP_OBJECT_PLAYER

#include "SheepObject.h"

namespace Sheep
{
	class ObjectPlayer : public Object
	{
	public:
		ObjectPlayer(const std::string& name, unsigned int spriteId, eTAG tag);
		ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, const Vector2& position, unsigned int spriteId, const Rect& collisionBox, eTAG tag);
		ObjectPlayer(const std::string& name, unsigned int speed, int health, int damage, int x, int y, unsigned int spriteId, const Rect& collisionBox, eTAG tag);

		void Update() override final;
		void OnCollisionEnter(Object* otherObject) override final;
		void OnCollisionExit(Object* otherObject) override final;
	};
}

#endif

