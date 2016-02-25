#ifndef UTILITY_ANIMATION
#define UTILITY_ANIMATION

/*
+=============================================+
+==============================================+
Utility_Animation.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is a general utility function, but more specialised towards animations.
+==============================================+
+============================================+
*/

#include "Vector2.h"

namespace Sheep
{
	template <typename T, typename timeType>
	T Lerp(const T& positionA, const T& positionB, timeType time)
	{
		return positionA + (positionB - positionA) * time;
	}
}


#endif