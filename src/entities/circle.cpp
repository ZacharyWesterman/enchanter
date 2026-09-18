#include "circle.hpp"
#include <raylib.h>

namespace enchanter {

circle::circle(position pos, float radius, Color color) : entity(pos), radius(radius), color(color) {}

void circle::update() {}

void circle::draw() const {
	DrawCircle(pos.x, pos.y, radius, color);
}

} // namespace enchanter
