#include "SheepDebug.h"
#include "SheepObject.h"
#include "Rect.h"
#include "SheepTransform2D.h"
#include "Utility.h"

using namespace Sheep;

void Debug::DisplayFPS(bool state, int x, int y)
{
	HAPI->SetShowFPS(state, x, y);
}

void Debug::DisplayCollisionBox(const Object& object, const HAPI_TColour& lineColour)
{
	Rect r = object.GetCollisionBorder();
	r.Translate(object.transform->GetPosition());
	VIEW.DrawSquare(r, lineColour);
}

void Debug::DisplayDirection(const Object& object, int distance, const HAPI_TColour& lineColour)
{
	const Vector2 pos = object.transform->GetPosition();
	const Rect container = object.GetCollisionBorder();
	const float angle = object.transform->GetRotation();

	const Vector2 origin(pos + container.Center());

	const float s = sin(toRadian<float>(angle));
	const float c = cos(toRadian<float>(angle));

	const Vector2 rotatedPoint(origin.x * c - origin.y * s, 
							   origin.x * s + origin.y * c);

	VIEW.DrawLine(origin, rotatedPoint, lineColour);
}