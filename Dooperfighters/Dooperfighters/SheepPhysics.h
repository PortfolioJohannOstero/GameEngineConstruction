#ifndef SHEEP_PHYSICS
#define SHEEP_PHYSICS

/*
+=============================================+
+==============================================+
Sheep Physics.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This class is a wip at this current time. It will contain a basic aerodynamic physics,
to allow the plane to feel more realistic.
At this current moment, it only stores gravity and allows anyone to tap into it.
+==============================================+
+============================================+
*/

#include "Precision.h"

namespace Sheep
{
	class Vector2;
	class Physics
	{
	public:
		static void SetGravity(float value);

		static float GetGravity();
		static Vector2 GetGravityVector();
	private:
		static float mGravity;
	};
}

#endif