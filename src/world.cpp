#include "world.hpp"
#include <raylib.h>

namespace enchanter {

int world::get_x(int world_x) const {
	return GetRenderWidth() / 2 + x + world_x * scale;
}

int world::get_y(int world_y) const {
	return GetRenderHeight() / 2 + y + world_y * scale;
}

int world::get_world_x(int screen_x) const {
	return (screen_x - GetRenderWidth() / 2 - x) / scale;
}

int world::get_world_y(int screen_y) const {
	return (screen_y - GetRenderHeight() / 2 - y) / scale;
}

} // namespace enchanter
