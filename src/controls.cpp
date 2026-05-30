#include "controls.hpp"
#include <raylib.h>

namespace controls::mouse {

bool left() {
	return IsMouseButtonDown(0);
}

bool right() {
	return IsMouseButtonDown(1);
}

bool in_screen() {
	auto pos = GetMousePosition();
	return pos.x >= 0 && pos.x <= GetRenderWidth() && pos.y >= 0 && pos.y <= GetRenderHeight();
}

} // namespace controls::mouse
