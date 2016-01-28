#ifndef SHEEP_PLAYER_CONTROLLER
#define SHEEP_PLAYER_CONTROLLER

#include "SheepObject.h"
#include <vector>

namespace Sheep
{
	class PlayerController : public Object
	{
	public:
		bool isJumping = false;
		bool isTouchingGround = false;

		/* Controlls: up, down, left, right, jump */
		PlayerController(const Vector2& position, const Sprite& sprite, int controlls[])
		{
			Object::Object(position, sprite);
		}

		bool checkControls(const HAPI_TKeyboardData& keyData);
		bool checkControls(const HAPI_TControllerData& controllerData);

	private:
		std::vector<int> mControls;
	};
}

#endif