#include "SheepSprite.h"
#include "SheepTransform2D.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region Constructors
Sprite::Sprite(const std::string& imgFilePath)
{
	if (!HAPI->LoadTexture(imgFilePath, &mTexture, &mBoundingBox.right, &mBoundingBox.bottom))
		HAPI->UserMessage("Could not load image: " + imgFilePath, "Image Failure");

	mBoundingBox.left = 0;
	mBoundingBox.top = 0;
}

Sprite::Sprite(BYTE* spriteImage, int width, int height, int sheetWidth)
{
	mBoundingBox.right = width;
	mBoundingBox.bottom = height;

	mTexture = new BYTE[mBoundingBox.Area() * 4];

	BYTE* destinationPointer = mTexture;
	BYTE* sourcePointer = spriteImage;

	for (int y = 0; y < mBoundingBox.Height(); y++)
	{
		memcpy(destinationPointer, sourcePointer, mBoundingBox.Width() * 4);

		destinationPointer += mBoundingBox.Width() * 4;
		sourcePointer += sheetWidth * 4;
	}

	mBoundingBox.setDimension(0, width, 0, height);
}

Sprite::~Sprite()
{
	delete[] mTexture;
}
#pragma endregion

/* +=== Copy ===+ */
#pragma region Copy
Sprite::Sprite(const Sprite& cpy)
{
	*this = cpy;
}

Sprite& Sprite::operator = (const Sprite& rhs)
{
	if (rhs.mBoundingBox != mBoundingBox || !mTexture)
	{
		mBoundingBox = rhs.mBoundingBox;

		mTexture = new BYTE[mBoundingBox.Area() * 4];
	}

	memcpy(mTexture, rhs.mTexture, mBoundingBox.Area() * 4);

	return *this; 
}
#pragma endregion

/* +==== Setter Methods ====+ */
bool Sprite::Load(std::string& filename, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int maxHorizontalSprites, unsigned int maxVerticalSprites, BLITTING_TYPES type)
{
	if (!HAPI->LoadTexture(filename, &mTexture, &mSheetSize.right, &mSheetSize.bottom))
	{
		HAPI->UserMessage("Could not load image: " + filename, "Image Failure");
		return false;
	}

	mBoundingBox.setDimension(spriteWidth, spriteHeight);

	mMaxSprites_col = maxHorizontalSprites;
	mMaxSprites_row = maxVerticalSprites;

	switch (type)
	{
	case BLITTING_TYPES::LINE_BY_LINE:
		RenderType = &Sprite::BlitLineByLine;
		break;
	case BLITTING_TYPES::TRANSPARENT:
		RenderType = &Sprite::BlitTransparent;
		break;
	case BLITTING_TYPES::TRANSPARENT_ROTATION:
		RenderType = &Sprite::BlitTransparentRotation;
		break;
	default:
		RenderType = nullptr;
		return false;
	}


	return true;
}

/* +==== Render ====+ */
void Sprite::Render(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	if (!RenderType)
		return;

	(this->*RenderType)(transform, screenPointer, screenBoundary, frameNumber);
}

#pragma region Blitting methods
void Sprite::BlitLineByLine(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	Vector2 pos = transform.GetPosition();

	if (mBoundingBox.CompletelyOutside(screenBoundary, pos.x, pos.y))
		return;

	Rect Clipped = Clipping(screenBoundary, pos.x, pos.y);
	AnimationOffset(frameNumber, Clipped);

	BYTE* destinationPointer = screenPointer + (pos.x + pos.y * screenBoundary.Width()) * BYTE_SIZE;
	BYTE* sourcePointer = mTexture + (Clipped.left + Clipped.top * mBoundingBox.Width()) * BYTE_SIZE;
	
	for (int y = 0; y < Clipped.Height(); y++)
	{
		memcpy(destinationPointer, sourcePointer, mBoundingBox.Width() * BYTE_SIZE);

		sourcePointer += mBoundingBox.Width() * BYTE_SIZE;
		destinationPointer += screenBoundary.Width() * BYTE_SIZE;
	}
}

void Sprite::BlitTransparent(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	Vector2 pos = transform.GetPosition();
	if (mBoundingBox.CompletelyOutside(screenBoundary, pos.x, pos.y))
		return;

	Rect Clipped = Clipping(screenBoundary, pos.x, pos.y);
	AnimationOffset(frameNumber, Clipped);

	BYTE* destinationPointer = screenPointer + (pos.x + pos.y * screenBoundary.Width()) * BYTE_SIZE;
	BYTE* sourcePointer = mTexture + (Clipped.left + Clipped.top * mSheetSize.Width()) * BYTE_SIZE;
	
	for (int y = 0; y < Clipped.Height(); y++)
	{
		for (int x = 0; x < Clipped.Width(); x++)
		{
			BYTE alpha = sourcePointer[3];
			if (alpha == 255)
			{
				memcpy(destinationPointer, sourcePointer, BYTE_SIZE);
			}
			else if (alpha != 0)
			{
				BYTE blue = sourcePointer[0];
				BYTE green = sourcePointer[1];
				BYTE red = sourcePointer[2];
		
				destinationPointer[0] = destinationPointer[0] + ((alpha * (blue - destinationPointer[0])) >> 8);
				destinationPointer[1] = destinationPointer[1] + ((alpha * (green - destinationPointer[1])) >> 8);
				destinationPointer[2] = destinationPointer[2] + ((alpha * (red - destinationPointer[2])) >> 8);
			}
		
			sourcePointer +=  BYTE_SIZE;
			destinationPointer += BYTE_SIZE;
		}
		
		destinationPointer += (screenBoundary.Width() - Clipped.Width()) * BYTE_SIZE;
		sourcePointer += (mSheetSize.Width() - Clipped.Width()) * BYTE_SIZE;
	}
}

void Sprite::BlitTransparentRotation(const Transform2D& transform, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	Vector2 center = getSimpleRotation(Vector2(0, 0), transform.GetRotation());
	Vector2 pos = transform.GetPosition() + center;

	if (mBoundingBox.CompletelyOutside(screenBoundary, pos.x, pos.y))
		return;

	Rect Clipped = Clipping(screenBoundary, pos.x, pos.y);
	AnimationOffset(frameNumber, Clipped);

	BYTE* destinationPointer = screenPointer + (pos.x + pos.y * screenBoundary.Width()) * BYTE_SIZE;
	BYTE* sourcePointer = mTexture + (Clipped.left + Clipped.top * mSheetSize.Width()) * BYTE_SIZE;

	for (int y = 0; y < Clipped.Height(); y++)
	{
		for (int x = 0; x < Clipped.Width(); x++)
		{
			BYTE alpha = sourcePointer[3];
			if (alpha == 255)
			{
				memcpy(destinationPointer, sourcePointer, BYTE_SIZE);
			}
			else if (alpha != 0)
			{
				BYTE blue = sourcePointer[0];
				BYTE green = sourcePointer[1];
				BYTE red = sourcePointer[2];

				destinationPointer[0] = destinationPointer[0] + ((alpha * (blue - destinationPointer[0])) >> 8);
				destinationPointer[1] = destinationPointer[1] + ((alpha * (green - destinationPointer[1])) >> 8);
				destinationPointer[2] = destinationPointer[2] + ((alpha * (red - destinationPointer[2])) >> 8);
			}

			sourcePointer += BYTE_SIZE;
			destinationPointer += BYTE_SIZE;
		}

		destinationPointer += (screenBoundary.Width() - Clipped.Width()) * BYTE_SIZE;
		sourcePointer += (mSheetSize.Width() - Clipped.Width()) * BYTE_SIZE;
	}
}
#pragma endregion

Vector2 Sprite::getRotation(const Vector2& initPos, int angle)
{
	int x = initPos.y * (sin(angle) * (tan(angle / 2) * tan(angle / 2)) - 2 * tan(angle / 2)) + initPos.x * (-sin(angle) * tan(angle / 2) + 1);
	int y = initPos.y * (-sin(angle) * tan(angle / 2) + 1) + initPos.x * sin(angle);

	return Vector2(x, y);
}

Vector2 Sprite::getSimpleRotation(const Vector2& initPos, int angle)
{
	return Sheep::Vector2(initPos.x * cos(angle) + initPos.y * sin(angle),
						  initPos.y * cos(angle) - initPos.x * sin(angle));
}

Rect Sprite::Clipping(const Rect& screenBoundary, int &x, int &y)
{
	Rect Clipped(0, mBoundingBox.Width(), 0, mBoundingBox.Height()); /* 1. source space */
	Clipped.Translate(x, y); /* 2. Convert to screen space */
	Clipped.ClipTo(screenBoundary); /* 3. Clip to window */
	Clipped.Translate(-x, -y); /* 4. Convert back to source space */

	/* 5. clamp x and y values if they go below 0 */
	if (x < 0) x = 0;
	if (y < 0) y = 0;

	return Clipped;
}

void Sprite::AnimationOffset(unsigned int frameNumber, Rect& animationClipContainer)
{
	unsigned int yoffset = 0;
	while (frameNumber > mMaxSprites_col)
	{
		frameNumber -= mMaxSprites_col;
		yoffset++;
	}

	if (yoffset > mMaxSprites_row)
		yoffset = mMaxSprites_row;

	animationClipContainer.Translate(frameNumber * mBoundingBox.Width(), yoffset * mBoundingBox.Height());
}

/* +==== Getter Methods ====+ */
#pragma region Getter Methods
BYTE* Sprite::GetImagePointer()
{
	return mTexture;
}

/* +=== Get Sprite Bounding Box ===+ */
Rect Sprite::Image() const
{
	return mBoundingBox;
}

#pragma endregion



/* +==== Pixel Handling ====+ */
BYTE* Sprite::GetPixel(int x, int y)
{
	return mTexture + ((x + y * mBoundingBox.Width()) * BYTE_SIZE);
}

void Sprite::SetPixel(int x, int y, const HAPI_TColour& colour)
{
	memcpy(GetPixel(x, y), &colour, BYTE_SIZE);
}

/*
bool Sprite::resizePixels(int newWidth, int newHeight) {
	BYTE* newTexture = new BYTE[newWidth * newHeight * 4];
	BYTE* destinationPointer = newTexture;
	BYTE* sourcePointer = mTexture;
	
	int x_ratio = (int)((mWidth << 16) / newWidth) + 1;
	int y_ratio = (int)((mHeight << 16) / newHeight) + 1;
	
	for (int y = 0; y < newHeight; y++)
	{
		for (int x = 0; x < newWidth; x++)
		{
			BYTE blue = sourcePointer[0];
			BYTE green = sourcePointer[1];
			BYTE red = sourcePointer[2];
			BYTE alpha = sourcePointer[3];

			sourcePointer += 4;
			destinationPointer += 4;
		}
	}

	return true;

}*/