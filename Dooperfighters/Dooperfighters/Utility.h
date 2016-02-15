#ifndef SHEEP_UTILITY
#define SHEEP_UTILITY

/* +============================+
Utility Functions
---------------------------
Author: Jóhann Østerø
+============================+
*/

#include "Vector2.h"
#include <random>
#include <cmath>

	/* +==== Decleration ====+ */
	// Random
	template<typename T> T randomRange(T min, T max);
	
	// Conversion
	template<typename T> T toRadian(float deg);
	template<typename T> T toDegrees(float rad);
	
	int roundFromHalf(float value);

	// Vector methods
	Sheep::Vector2 getSheerRotation(const Sheep::Vector2& initPos, float angle);
	Sheep::Vector2 getBasicRotation(const Sheep::Vector2& initPos, float angle);
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

#endif