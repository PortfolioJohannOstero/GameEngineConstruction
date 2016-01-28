#ifndef SHEEP_SPRITE
#define SHEEP_SPRITE


#include <HAPI_lib.h>
#include <string>
#include "Rect.h"

namespace Sheep
{
	class Transform2D;
	class Sprite
	{
	public:
		static const BYTE BYTE_SIZE = 4;

		/* +==== Constructors ====+ */
		Sprite() {};
		Sprite(const std::string& imgFilePath);
		Sprite(BYTE* spriteImage, int width, int height, int sheetWidth);

		~Sprite();

		/* +=== Copy ===+ */
		Sprite(const Sprite& cpy);
		Sprite& operator = (const Sprite& rhs);

		/* +==== Setter Methods ====+ */
		bool Load(std::string& filename, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int maxHorizontalSprites, unsigned int maxVerticalSprites, bool isTransparent);

		/* +==== Getter methods ====+ */
		BYTE* GetImagePointer();

		/* +=== Get Sprite Bounding Box ===+ */
		Rect Image() const;

		/* +==== Render ====+ */
		void Render(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);

	private:
		BYTE* mTexture = nullptr;
		Rect mBoundingBox;
		Rect mSheetSize;
		unsigned int mLayer;

		unsigned int mMaxSprites_col;
		unsigned int mMaxSprites_row;

		/* +=== Rendering types ===+ */
		void (Sprite::*RenderType)(const Transform2D&, BYTE*, const Rect&, unsigned int) = nullptr;
		void BlitLineByLine(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);
		void BlitTransparent(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);

		// !NOTE: updates the x and y values if needed
		Rect Clipping(const Rect& screenBoundary, int &x, int &y);

		Vector2 getRotation(const Vector2& initPos, int angle);
		Vector2 getSimpleRotation(const Vector2& initPos, int angle);

		/* +=== Pixel handling ===+ */
		BYTE* GetPixel(int x, int y);
		void SetPixel(int x, int y, const HAPI_TColour& colour);
	};
}

#endif