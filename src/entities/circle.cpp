#include "circle.hpp"
#include <raylib.h>

namespace enchanter {

circle::circle(int x, int y, float radius, Color color) : entity(x, y), radius(radius), color(color) {}

void circle::update() {}

void circle::draw(const world &world) const {
	DrawCircle(world.get_x(x), world.get_y(y), radius * world.scale, color);
}

} // namespace enchanter
