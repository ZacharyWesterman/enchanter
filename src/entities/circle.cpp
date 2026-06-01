#include "circle.hpp"
#include <raylib.h>

namespace enchanter {

circle::circle(int x, int y, float radius, Color color) : entity(x, y), radius(radius), color(color) {}

void circle::update() {}

void circle::draw() const {
	DrawCircle(x, y, radius, color);
}

} // namespace enchanter
