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
	/* +==== Decleration ====+ */
	// Random
	template<typename T> T randomRange(T min, T max);
	
	// Conversion
	template<typename T> T toRadian(float deg);
	template<typename T> T toDegrees(float rad);
	
	extern int roundFromHalf(float value);

	// Vector methods
	extern Vector2 getSheerRotation(const Vector2& initPos, float angle);
	extern Vector2 getBasicRotation(const Vector2& initPos, float angle);

	// Boundaries
	template<typename T> T min(T value1, T value2);
	template<typename T> T max(T value1, T value2);

	#pragma region RANDOM
	template<typename T>
	T randomRange(T min, T max)
	{
		return min + std::rand() % ((max + 1) - min);
	}
	#pragma endregion Random

	#pragma region CONVERSION
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

	#pragma endregion Conversion

	#pragma region BOUNDARIES
	template<typename T>
	T min(T value1, T value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	template<typename T>
	T max(T value1, T value2)
	{
		return (value1 > value2) ? value1 : value2;
	}
	#pragma endregion Boundaries
}

#include "Utility.cpp"
#endif