#pragma once

#include "entity.hpp"
#include <raylib.h>

namespace enchanter {

struct circle : public entity {
	float radius;
	Color color;

	circle(int x, int y, float radius, Color color);

	void update() override;
	void draw(const world &game_world) const override;
};

} // namespace enchanter
