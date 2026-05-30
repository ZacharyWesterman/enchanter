#pragma once

#include "../world.hpp"

namespace enchanter {

struct entity {
	int x;
	int y;

	entity(int x, int y);
	virtual ~entity();

	virtual void update() = 0;
	virtual void draw(const world &game_world) const = 0;
};

} // namespace enchanter
