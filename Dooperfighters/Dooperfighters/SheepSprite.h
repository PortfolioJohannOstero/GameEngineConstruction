#ifndef SHEEP_SPRITE
#define SHEEP_SPRITE

/*
+=============================================+
+==============================================+
Sprite.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The sprite class is responsible for rendering the loaded in textures (using the HAPI library).
The sprite class can render sprite in two different ways:
	- Line-By-Line
	- Transparent
--
LbL is considerably faster, however does not support transparent background
+==============================================+
+============================================+
*/

#include <HAPI_lib.h>
#include <string>
#include "Rect.h"
#include "SheepBlittingTypes.h"

namespace Sheep
{
	class Transform2D;
	class Sprite
	{
	public:
		static const BYTE BYTE_SIZE = 4;

		/* +==== Constructors ====+ */
		Sprite() {};

		~Sprite();

		/* +=== Copy ===+ */
		Sprite(const Sprite& cpy);
		Sprite& operator = (const Sprite& rhs);

		/* +==== Setter Methods ====+ */
		/* Loads in the sprite using the HAPI library */
		bool Load(std::string& filename, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int maxHorizontalSprites, unsigned int maxVerticalSprites, BLITTING_TYPES type);

		/* +=== Get Sprite Bounding Box ===+ */
		Rect Image() const;

		/* +==== Render ====+ */
		void Render(const Transform2D& transform, float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);

	private:
		BYTE* mTexture = nullptr;
		BYTE* mRotatedTexture = nullptr; // <-- The rotated texture is the one that is used, mTexture is only a reference. This is to get around allocating during gametime
		Rect mBoundingBox;
		Rect mSheetSize;
		unsigned int mLayer;

		unsigned int mMaxSprites_col;
		unsigned int mMaxSprites_row;

		/* +=== Rendering types ===+ */
		/* Using a function pointer in order to reduce rendering time, because there is no if-statement during gametime that checks what type of rendering method to use*/
		void (Sprite::*RenderType)(const Transform2D&, float, BYTE*, const Rect&, unsigned int) = nullptr;
		void BlitLineByLine(const Transform2D& transform,  float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);
		void BlitTransparent(const Transform2D& transform, float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber);

		/* +==== Image manipulation ====+ */
		// !NOTE: updates the x and y values if needed
		Rect Clipping(const Rect& screenBoundary, real &x, real &y);
		void AnimationOffset(unsigned int frameNumber, Rect& animationClipContainer);
		void Rotate(real angle_deg);
	};
}

#endif