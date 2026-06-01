#pragma once
#include "entities/entity.hpp"
#include <raylib.h>
#include <vector>

namespace enchanter {

struct world {
	Camera2D camera;
	bool initialized = false;
	int scale_factor = 0;

	std::vector<entity *> entities;

	world();
	~world();

	void init();

	void zoom(int step);
	void pan(float x, float y);

	void update();
	void draw() const;
};

} // namespace enchanter
