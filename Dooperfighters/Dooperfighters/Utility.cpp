#include "Utility.h"

#pragma region CONVERSION
int roundFromHalf(float value)
{
	if (value > 0.5f)
		value = ceil(value);
	else
		value = floor(value);
	return (int)value;
}
#pragma endregion Conversion

#pragma region VECTOR METHODS
Sheep::Vector2 getSheerRotation(const Sheep::Vector2& initPos, float angle)
{
	float x = initPos.y * (sin(angle) * (tan(angle / 2) * tan(angle / 2)) - 2 * tan(angle / 2)) + initPos.x * (-sin(angle) * tan(angle / 2) + 1);
	float y = initPos.y * (-sin(angle) * tan(angle / 2) + 1) + initPos.x * sin(angle);

	return Sheep::Vector2(x, y);
}

Sheep::Vector2 getBasicRotation(const Sheep::Vector2& initPos, float angle)
{
	float x = initPos.x * cos(angle) + initPos.y * sin(angle);
	float y = initPos.y * cos(angle) - initPos.x * sin(angle);

	return Sheep::Vector2(x, y);
}
#pragma endregion Vector methods