#ifndef CORE_H
#define CORE_H


/*
+=============================================+
+==============================================+
View.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is the main window that stores the pixel addresses and window resolution;
- Draw
+==============================================+
+============================================+
*/


#include <HAPI_lib.h>

class Core
{
public:

private:

	BYTE* mScreen;

};

#endif

#ifndef VIEW
#define VIEW

/*
+=============================================+
+==============================================+
View.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This is the main window that stores the pixel addresses and window resolution;
- Draw
+==============================================+
+============================================+
*/

#include <HAPI_lib.h>
#include "Vector3.h"
#include <vector>

#define BYTESIZE 4 /* <-- The HAPI_TColour consists of rgba, i.e. 4 bytes */

namespace SE
{
	class View
	{
	public:
		/* +==== Constructors ====+ */
		View(int width, int height);
		~View();

		/* +==== View Resolution ====+*/
		int ViewWidth() const;
		int ViewHeight() const;
		int ViewResolution() const;

		/* +==== Pixel Handling ====+ */
		BYTE* getPixel(int x, int y);
		void SetPixel(int x, int y, const HAPI_TColour& colour);
		int getByteSize() const;

		/* +================ Drawing ================+ */

		/* +==== Debug ====+ */
		void DisplayFPS(bool state, int x, int y);

		/* +==== Entire Screen Coverage ===+ */
		void clearScreen(const HAPI_TColour& colour);

		/* +==== Line Drawing ====+ */
		void DrawLine(const BSheep::Vector3& positionA, const BSheep::Vector3& positionB, const HAPI_TColour& color);
		void DrawLines(const std::vector<BSheep::Vector3> points, const HAPI_TColour& color, bool wrapAround);

		/* +=== Text Drawing ====+*/
		void DrawText(const std::string text, const int x, const int y, const HAPI_TColour& colour);

	protected:
		int mWidth, mHeight;
		BYTE* mView; /* <-- The memory address to the first pixel on the screen */
	};
}


#endif