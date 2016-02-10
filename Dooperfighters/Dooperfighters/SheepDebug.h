#ifndef SHEEP_DEBUG
#define SHEEP_DEBUG

#include <HAPI_lib.h>
namespace Sheep
{
	class Object;	
	struct Debug
	{
		void static DisplayFPS(bool state, int x, int y);
		void static DisplayCollisionBox(const Object& object, const HAPI_TColour& lineColour);
		void static DisplayDirection(const Object& object, int distance, const HAPI_TColour& lineColour);
	};
}

#endif