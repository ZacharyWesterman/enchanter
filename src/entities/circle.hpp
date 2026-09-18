#pragma once

#include "entity.hpp"
#include <raylib.h>

namespace enchanter {

struct circle : public entity {
	float radius;
	Color color;

	circle(position pos, float radius, Color color);

	void update() override;
	void draw() const override;
};

} // namespace enchanter
