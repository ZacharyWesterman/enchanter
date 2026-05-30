#include "world.hpp"
#include <raylib.h>

namespace enchanter {

int world::get_x(int x) const {
	return GetRenderWidth() / 2 + this->x + x * scale;
}

int world::get_y(int y) const {
	return GetRenderHeight() / 2 + this->y + y * scale;
}

} // namespace enchanter
