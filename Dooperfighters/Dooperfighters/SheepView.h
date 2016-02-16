#pragma once
/*
+=============================================+
+==============================================+
View.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is the view class, everything related to rendering goes through here!
+==============================================+
+============================================+
*/

#include <HAPI_lib.h>
#include <vector>

#include "SheepBlittingTypes.h"
namespace Sheep
{
	#define VIEW Sheep::View::getInstance()
	class Transform2D;
	class Rect;
	class Vector2;
	class Sprite;
	class View
	{
	public:
		const int BYTE_SIZE = 4;

		/* +==== Singleton - Construction ====+ */
		static void Create();
		static void Destroy();
		static View& getInstance() { return *INSTANCE; }

		bool Initialise(int screenWidth, int screenHeight, unsigned int maxLayers);

		/* +==== Window Resolution ====+ */
		Rect WindowBoundary() const;

		/* +==== Sprite Handling ====+ */
		bool CreateSprite(unsigned int& spriteId, std::string filename, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int maxHorizontalSprites, unsigned int maxVerticalSprites, BLITTING_TYPES type);
		void Render(unsigned int id, const Transform2D& transform, float previousRotation, int framecount = 0);

		/* +==== Rendering ====+ */
			/* +=== Text ===+ */
		void DrawText(const std::string& message, const HAPI_TColour& colour, int x, int y);

			/* +=== Dynamic Drawing ===+ */
		void ClearScreen(const HAPI_TColour& colour);
		void DrawLine(const Vector2& positionA, const Vector2& positionB, const HAPI_TColour& color);
		void DrawLines(const std::vector<Vector2>& points, const HAPI_TColour& color, bool wrapAround);
		void DrawSquare(const Rect& rectangle, const HAPI_TColour& colour);

	private:
		static View* INSTANCE;

		/* +=== Data Members ===+ */
		Rect* mWindowBoundary = nullptr;
		BYTE* mScreenPointer = nullptr;

		std::vector<Sprite*> mSpriteContainer;

		unsigned int mMaxLayers = 10;

		const HAPI_TColour frameBoxColour { 255, 0, 0, 255 };

		View() {}
		~View();
	};
}
