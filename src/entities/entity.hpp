#pragma once

namespace enchanter {

struct entity {
	float x;
	float y;

	entity(float x, float y);
	virtual ~entity();

	virtual void update() = 0;
	virtual void draw() const = 0;
};

} // namespace enchanter
