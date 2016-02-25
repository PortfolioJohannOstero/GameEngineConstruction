#ifndef SHEEP_DEBUG
#define SHEEP_DEBUG

/*
+=============================================+
+==============================================+
Debug.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The Debug class is purely there to make debugging and testing easier.
it allows for user to display the:
	- FramePerSecond
	- The Box Collider(s) around the object
	- The Direction vector

: it uses the line drawing from the VIEW blackbox
+==============================================+
+============================================+
*/


#include <HAPI_lib.h>
#include "Precision.h"
namespace Sheep
{
	class Object;	
	struct Debug
	{
		void static DisplayFPS(bool state, int x, int y);
		void static DisplayCollisionBox(const Object& object, const HAPI_TColour& lineColour);
		void static DisplayDirection(const Object& object, real distance, const HAPI_TColour& lineColour);
	};
}

#endif