#pragma once

namespace enchanter {

struct world {
	int x = 0;
	int y = 0;
	int scale_factor = 0;
	float scale = 1.f;

	int get_x(int x) const;
	int get_y(int y) const;
};

} // namespace enchanter
