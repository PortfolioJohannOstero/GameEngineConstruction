#include "SheepSprite.h"
#include "SheepTransform2D.h"
#include "SheepDebugMessage.h"
#include "Utility.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region CONSTRUCTORS
Sprite::~Sprite()
{
	delete[] mTexture;
	delete[] mRotatedTexture;
}

/* +=== Copy ===+ */
#pragma region COPY
Sprite::Sprite(const Sprite& cpy)
{
	*this = cpy;
}

Sprite& Sprite::operator = (const Sprite& rhs)
{
	if (rhs.mBoundingBox != mBoundingBox || !mTexture)
	{
		mBoundingBox = rhs.mBoundingBox;

		mTexture = new BYTE[mBoundingBox.Area() * BYTE_SIZE];
	}

	memcpy(mTexture, rhs.mTexture, mBoundingBox.Area() * BYTE_SIZE);

	return *this; 
}
#pragma endregion copy

#pragma endregion Constructors

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

	// Creating a modifiable texture array with initial values set to 0 
	const unsigned int textureSize = mSheetSize.Area() * BYTE_SIZE;
	mRotatedTexture = new BYTE[textureSize];
	memset(mRotatedTexture, 0, textureSize);
	
	switch (type)
	{
	case BLITTING_TYPES::LINE_BY_LINE:
		RenderType = &Sprite::BlitLineByLine;
		break;
	case BLITTING_TYPES::TRANSPARENT:
		RenderType = &Sprite::BlitTransparent;
		break;
	default:
		RenderType = nullptr;
		return false;
	}

	return true;
}

/* +==== Render ====+ */
void Sprite::Render(const Transform2D& transform, float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	if (!RenderType)
		return;

	(this->*RenderType)(transform, previousRotation, screenPointer, screenBoundary, frameNumber);
}

#pragma region BLITTING METHODS
void Sprite::BlitLineByLine(const Transform2D& transform, float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	Vector2 pos = transform.GetPosition();

	if (mBoundingBox.CompletelyOutside(screenBoundary, (int)pos.x, (int)pos.y))
		return;

	Rect Clipped = Clipping(screenBoundary, pos.x, pos.y);
	AnimationOffset(frameNumber, Clipped);

	BYTE* destinationPointer = screenPointer + ((int)pos.x + (int)pos.y * screenBoundary.Width()) * BYTE_SIZE;
	BYTE* sourcePointer = mTexture + (Clipped.left + Clipped.top * mSheetSize.Width()) * BYTE_SIZE;
	
	for (int y = 0; y < Clipped.Height(); y++)
	{
		memcpy(destinationPointer, sourcePointer, mBoundingBox.Width() * BYTE_SIZE);

		sourcePointer += mSheetSize.Width() * BYTE_SIZE;
		destinationPointer += screenBoundary.Width() * BYTE_SIZE;
	}
}

void Sprite::Rotate(real angle)
{
	angle = toRadian<float>(angle);

	const Vector2 posH = getBasicRotation(Right(), -angle);
	const Vector2 posV = getBasicRotation(Up(), -angle);

	Vector2 coord0 = getBasicRotation(Vector2(mBoundingBox.Center() * -1), -angle) + mBoundingBox.Center();
	
	for (int y = 0; y < mBoundingBox.Height(); y++)
	{
		Vector2 coord1 = coord0;
		for (int x = 0; x < mBoundingBox.Width(); x++)
		{
			int xx = (int)coord1.x;
			int yy = (int)coord1.y;
			
			const int rIndex = (x + y * mSheetSize.Width()) * BYTE_SIZE;
			const int index = (xx + yy * mSheetSize.Width()) * BYTE_SIZE;
			
			BYTE alpha = 0;
			if (rIndex < 0 && rIndex >= mBoundingBox.Area() * BYTE_SIZE)
				alpha = 0;
			else					
				alpha = mTexture[index + 3];
			
			mRotatedTexture[rIndex] = mTexture[index];
			mRotatedTexture[rIndex + 1] = mTexture[index + 1];
			mRotatedTexture[rIndex + 2] = mTexture[index + 2];
			mRotatedTexture[rIndex + 3] = alpha;

			coord1 += posH;
		}
		coord0 += posV;
	}
}

void Sprite::BlitTransparent(const Transform2D& transform, float previousRotation, BYTE* screenPointer, const Rect& screenBoundary, unsigned int frameNumber)
{
	Vector2 pos = transform.GetPosition();

	if (transform.GetRotation() != previousRotation)
		Rotate(transform.GetRotation());

	DEBUG_MESSAGE.PushMessage(std::to_string(transform.GetRotation()) + " : " + std::to_string(previousRotation));

	if (mBoundingBox.CompletelyOutside(screenBoundary, pos.x, pos.y))
		return;

	Rect Clipped = Clipping(screenBoundary, pos.x, pos.y);
	AnimationOffset(frameNumber, Clipped);

	BYTE* destinationPointer = screenPointer + ((int)pos.x + (int)pos.y * screenBoundary.Width()) * BYTE_SIZE;
	BYTE* sourcePointer = mRotatedTexture + (Clipped.left + Clipped.top * mSheetSize.Width()) * BYTE_SIZE;
	
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
#pragma endregion Blitting methods

Rect Sprite::Clipping(const Rect& screenBoundary, real &x, real &y)
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
#pragma region GETTER METHODS
BYTE* Sprite::GetImagePointer()
{
	return mTexture;
}

/* +=== Get Sprite Bounding Box ===+ */
Rect Sprite::Image() const
{
	return mBoundingBox;
}

#pragma endregion getter methods



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