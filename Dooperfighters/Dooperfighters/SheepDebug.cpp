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
	r.Translate(object.transform->GetPosition() + object.GetCollisionBorderOffset());
	VIEW.DrawSquare(r, lineColour);
}

void Debug::DisplayDirection(const Object& object, real distance, const HAPI_TColour& lineColour)
{
	const Vector2 centerOfContainer = object.GetCollisionBorder().Center();
	const Vector2 currPos = object.transform->GetPosition() + object.GetCollisionBorderOffset() + centerOfContainer;

	VIEW.DrawLine(currPos, currPos + object.transform->GetDirection(Right()) * distance, lineColour);
}