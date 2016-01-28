#ifndef SHEEP_SPRITESHEET
#define SHEEP_SPRITESHEET

#include <HAPI_lib.h>
#include <vector>
#include "SheepSprite.h"

namespace Sheep
{
	class Spritesheet
	{
	public:
		/* +==== Constructors ====+ */
		Spritesheet(std::string fileName, int spriteWidth, int spriteHeight);
		Spritesheet(std::string fileName, int spriteSize);
		~Spritesheet();

		/* +==== Getter Methods ====+ */
		Sprite getSpriteIndex(int y, int x);
		Sprite operator () (int y, int x);

		int getSheetWidth() const;
		int getSheetHeight() const;

		int getSpriteWidth() const;
		int getSpriteHeight() const;

	private:

		bool initSpriteContainer(std::string& fileName);
		void failedToLoad();

		BYTE* spritesheet = nullptr;
		int mSheetWidth, mSheetHeight;
		int mSpriteWidth, mSpriteHeight;
	};

}


#endif