#include "SheepPhysics.h"
#include "Vector2.h"

using namespace Sheep;

float Physics::mGravity = 9.81f;

void Physics::SetGravity(float value)
{
	mGravity = value;
}

float Physics::GetGravity()
{
	return mGravity;
}

Vector2 Physics::GetGravityVector()
{
	return Vector2(0, mGravity);
}
