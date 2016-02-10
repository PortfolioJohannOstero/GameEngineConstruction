#ifndef UTILITY
#define UTILITY

/* +============================+
Utility Functions
---------------------------
Author: Jóhann Østerø
+============================+
*/

#include "Vector2.h"
#include <random>
#include <cmath>
namespace Sheep
{
	template<typename T>
	T Random(T min, T max)
	{
		return min + std::rand() % ((max + 1) - min);
	}

	template<typename T>
	T toRadian(float deg)
	{
		return deg * ((T)std::_Pi) / 180;
	}

	template<typename T>
	T toDegrees(float rad)
	{
		return rad * 180 / ((T)std::_Pi);
	}
}


#endif