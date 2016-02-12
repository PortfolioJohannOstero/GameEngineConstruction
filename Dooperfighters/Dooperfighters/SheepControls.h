#ifndef SHEEP_CONTROLS
#define SHEEP_CONTROLS

namespace Sheep
{
	struct PlayerControls
	{
		unsigned int left, right, up, down;
		unsigned int fire;

		PlayerControls() { left = 0; right = 0; up = 0; down = 0; fire = 0; }

		PlayerControls(unsigned int left_key, unsigned int right_key, unsigned int up_key, unsigned int down_key, unsigned int fire_key)
			: left(left_key), right(right_key), up(up_key), down(down_key), fire(fire_key) {}
	};
}

#endif