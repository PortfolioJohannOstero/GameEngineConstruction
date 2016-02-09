#ifndef UTILITY
#define UTILITY

/* +============================+
Utility Functions
---------------------------
Author: J�hann �ster�
+============================+
*/

#include "Vector2.h"
#include <random>

namespace Sheep
{
	template<typename T>
	T Random(T min, T max)
	{
		return min + std::rand() % ((max + 1) - min);
	}
}


#endif