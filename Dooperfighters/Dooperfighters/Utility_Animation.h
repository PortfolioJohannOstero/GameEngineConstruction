#ifndef UTILITY_ANIMATION
#define UTILITY_ANIMATION

/* +============================+
	Utility Functions
		~Animations Helpers
	---------------------------	
	Author: Jóhann Østerø
	+============================+
*/

#include "Vector2.h"

namespace Sheep
{
	template <typename T, typename timeType>
	T Lerp(const T& positionA, const T& positionB, timeType time)
	{
		return positionA + (positionB - positionA) * time;
	}
}


#endif