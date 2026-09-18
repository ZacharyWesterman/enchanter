#pragma once

#include "../types/position.hpp"

namespace enchanter {

struct entity {
	position pos;

	entity(position pos);
	virtual ~entity();

	virtual void update() = 0;
	virtual void draw() const = 0;
};

} // namespace enchanter
