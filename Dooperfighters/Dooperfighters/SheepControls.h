#ifndef SHEEP_CONTROLS
#define SHEEP_CONTROLS

/*
+=============================================+
+==============================================+
Controls.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
This merely file used for storing custom controls. At this current time, there are only Player controls added
+==============================================+
+============================================+
*/

namespace Sheep
{
	struct PlayerControls
	{
		unsigned int left, right, up, down;
		unsigned int fire_bullet, fire_missile, fire_bomb;

		PlayerControls() { left = 0; right = 0; up = 0; down = 0; fire_bullet = 0; fire_missile = 0, fire_bomb = 0; }

		PlayerControls(unsigned int left_key, unsigned int right_key, unsigned int up_key, unsigned int down_key, unsigned int fire_bullet_key, unsigned int fire_missile_key, unsigned int fire_bomb_key)
			: left(left_key), right(right_key), up(up_key), down(down_key), fire_bullet(fire_bullet_key), fire_missile(fire_missile_key), fire_bomb(fire_bomb_key) {}
	};
}

#endif