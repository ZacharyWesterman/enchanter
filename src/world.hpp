#pragma once

namespace enchanter {

struct world {
	int x = 0;
	int y = 0;
	int scale_factor = 0;
	float scale = 1.f;

	int get_x(int x) const;
	int get_y(int y) const;

	int get_world_x(int screen_x) const;
	int get_world_y(int screen_y) const;
};

} // namespace enchanter
