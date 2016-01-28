#include "SheepSpriteSheet.h"

using namespace Sheep;

/* +==== Constructors ====+ */
#pragma region Constructors
Spritesheet::Spritesheet(std::string fileName, int spriteWidth, int spriteHeight)
	: mSpriteWidth(spriteWidth), mSpriteHeight(spriteHeight)
{
	if (!initSpriteContainer(fileName))
		failedToLoad();
}

Spritesheet::Spritesheet(std::string fileName, int spriteSize)
	: mSpriteWidth(spriteSize), mSpriteHeight(spriteSize)
{
	if (!initSpriteContainer(fileName))
		failedToLoad();
}

Spritesheet::~Spritesheet()
{
	delete[] spritesheet;
	spritesheet = nullptr;
}
#pragma endregion

/* +==== Getter Methods ====+ */
#pragma region Getter Methods
Sprite Spritesheet::getSpriteIndex(int y, int x)
{
	if ((y *= mSpriteHeight) > mSheetHeight)
		y = mSheetHeight - mSpriteHeight;
	else if (y < 0)
		y = 0;

	if ((x *= mSpriteWidth) > mSheetWidth)
		x = mSheetWidth - mSpriteWidth;
	else if (x < 0)
		x = 0;


	BYTE* offset = spritesheet + (x + y * mSheetWidth) * 4;
	return Sprite(offset, mSpriteWidth, mSpriteHeight, mSheetWidth);
}

Sprite Spritesheet::operator () (int y, int x)
{
	return getSpriteIndex(y, x);
}

int Spritesheet::getSheetWidth() const
{
	return mSheetWidth;
}

int Spritesheet::getSheetHeight() const
{
	return mSheetHeight;
}

int Spritesheet::getSpriteWidth() const
{
	return mSpriteWidth;
}

int Spritesheet::getSpriteHeight() const
{
	return mSpriteHeight;
}
#pragma endregion


bool Spritesheet::initSpriteContainer(std::string& fileName)
{
	if (!HAPI->LoadTexture(fileName, &spritesheet, &mSheetWidth, &mSheetHeight))
		return false;

	return true;
}

void Spritesheet::failedToLoad()
{
	HAPI->UserMessage("Spritesheet failed to initialize", "Spritesheet Error!");
	HAPI->Close();
}