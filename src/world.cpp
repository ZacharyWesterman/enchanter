#include "world.hpp"
#include "entities/circle.hpp"
#include <cmath>
#include <raylib.h>

namespace enchanter {

world::world() {
	entities.push_back(new circle(-30, 0, 20, ORANGE));
	entities.push_back(new circle(30, 0, 20, LIME));
}

world::~world() {
	for (auto e : entities) {
		delete e;
	}
}

void world::init() {
	initialized = true;
	camera.offset = {GetRenderWidth() / 2.f, GetRenderHeight() / 2.f};
	camera.rotation = 0.f;
	camera.target = {0.f, 0.f};
	camera.zoom = 1.f;
	scale_factor = 0;
}

void world::zoom(int step) {
	scale_factor = std::min(10, std::max(-10, scale_factor + step));
	camera.zoom = std::pow(2, scale_factor / 2.f);
}

void world::pan(float x, float y) {
	camera.target.x -= x / camera.zoom;
	camera.target.y -= y / camera.zoom;
}

void world::update() {
	if (!initialized) {
		init();
	}

	for (auto e : entities) {
		e->update();
	}
}

void world::draw() const {
	BeginMode2D(camera);

	for (auto e : entities) {
		e->draw();
	}

	EndMode2D();
}

} // namespace enchanter
