#include "SheepView.h"
#include <assert.h>

#include "Rect.h"
#include "Vector2.h"
#include "SheepTransform2D.h"

#include "SheepSprite.h"

using namespace Sheep;

/* +==== Singleton - Construction ====+ */
#pragma region Singleton - Construction
View* View::INSTANCE = nullptr;

/* +=== Create and destroy the singleton ===+ */
void View::Create()
{
	/* If instance has not been created */
	if (!INSTANCE)
		INSTANCE = new View();
}

void View::Destroy()
{
	/* If instance has been created */
	if (INSTANCE)
	{
		delete INSTANCE;
		INSTANCE = nullptr;
	}		
}

/* +=== Initialises the HAPI library; creates a window ===+ */
bool View::Initialise(int screenWidth, int screenHeight)
{
	/* Check if the instance has been created and if the happy initialize */
	if (!INSTANCE)
		return false;

	// TODO: fix [original: !HAPI->Initialise(&screenWidth, &screenHeight)
	if (!HAPI->Initialise(&screenWidth, &screenHeight))
		return false;

	/* Get Window properties */
	mWindowBoundary = new Rect(0, screenWidth, 0, screenHeight);
	mScreenPointer = HAPI->GetScreenPointer();

	return true;
}

View::~View()
{
	delete mWindowBoundary;
	mWindowBoundary = nullptr;

	/* Remove the sprites */
	for (Sprite* s : mSpriteContainer)
	{
		delete s;
		s = nullptr;
	}

	mSpriteContainer.clear();
}
#pragma endregion

/* +==== Window Resolution ====+ */
Rect View::WindowBoundary() const
{
	return *mWindowBoundary;
}

/* +==== Sprite Handling ====+ */
bool View::CreateSprite(unsigned int& spriteId, std::string filename, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int maxHorizontalSprites, unsigned int maxVerticalSprites, BLITTING_TYPES type)
{
	Sprite* newSprite = new Sprite;
	if (!newSprite->Load(filename, spriteWidth, spriteHeight, maxHorizontalSprites, maxVerticalSprites, type))
	{
		HAPI->UserMessage("Could not load " + filename, "Image Load Failure");
		return false;
	}

	spriteId = mSpriteContainer.size();
	mSpriteContainer.push_back(newSprite);

	return true;
}


void View::Render(unsigned int id, const Transform2D& transform, float previousRotation, int framecount)
{
	assert(id >= 0 && id <= mSpriteContainer.size());
	assert(mSpriteContainer[id]);
	mSpriteContainer[id]->Render(transform, previousRotation, this->mScreenPointer, *mWindowBoundary, framecount);
}


/* +==== Rendering ====+ */
#pragma region Drawing Methods

/* +=== Text ===+ */
void View::DrawText(const std::string& message, const HAPI_TColour& colour, int x, int y)
{
	HAPI->RenderText(x, y, colour, message);
}


/* +=== Dynamic Drawing ===+ */
#pragma region Dynamic Drawing
void View::ClearScreen(const HAPI_TColour& colour)
{
	for (int i = 0; i < mWindowBoundary->Width() * mWindowBoundary->Height() * BYTE_SIZE; i += BYTE_SIZE)
		memcpy(mScreenPointer + i, &colour, BYTE_SIZE);
}

void View::DrawLine(const Vector2& positionA, const Vector2& positionB, const HAPI_TColour& color)
{
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm	
	Vector2 delta(abs(positionB.x - positionA.x), -abs(positionB.y - positionA.y));

	int x = (int)positionA.x;
	int y = (int)positionA.y;

	int sx = x < positionB.x ? 1 : -1;
	int sy = y < positionB.y ? 1 : -1;

	int err = (int)(delta.x + delta.y);
	int err2 = 0;

	BYTE* buffer = nullptr;
	while (true)
	{
		if (x < 0 || y < 0 || x >= mWindowBoundary->Width() || y >= mWindowBoundary->Height())
			break;
		
		memcpy(mScreenPointer + ((int)(x + y * mWindowBoundary->Width())) * BYTE_SIZE, &color, BYTE_SIZE);
		err2 = 2 * err;

		if (err2 >= delta.y)
		{
			if (x == positionB.x) break;
			err += (int)delta.y;
			x += sx;
		}

		if (err2 <= delta.x)
		{
			if (y == positionB.y) break;
			err += (int)delta.x;
			y += sy;
		}
	}
}

void View::DrawLines(const std::vector<Vector2>& points, const HAPI_TColour& color, bool wrapAround)
{
	for (unsigned int i = 1; i < points.size(); ++i)
		DrawLine(points[i - 1], points[i], color);

	if (wrapAround) // connect the last line ("wrap around")
		DrawLine(points[0], points[points.size() - 1], color);
}

void View::DrawSquare(const Rect& rectangle, const HAPI_TColour& colour)
{
	DrawLine(Vector2((real)rectangle.left, (real)rectangle.top), Vector2((real)rectangle.right, (real)rectangle.top), colour);
	DrawLine(Vector2((real)rectangle.right, (real)rectangle.top), Vector2((real)rectangle.right, (real)rectangle.bottom), colour);
	DrawLine(Vector2((real)rectangle.right, (real)rectangle.bottom), Vector2((real)rectangle.left, (real)rectangle.bottom), colour);
	DrawLine(Vector2((real)rectangle.left, (real)rectangle.bottom), Vector2((real)rectangle.left, (real)rectangle.top), colour);
}
#pragma endregion
#pragma endregion


