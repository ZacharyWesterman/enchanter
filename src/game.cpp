#include "game.hpp"
#include "controls.hpp"
#include "entities/circle.hpp"
#include "world.hpp"
#include <cmath>
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static int screenWidth = 800;
static int screenHeight = 600;

#ifdef PLATFORM_WEB
static enchanter::game *main_game = nullptr;
static void run_main_loop() {
	main_game->draw();
}
#endif

namespace enchanter {

game::game() : game_world(0, 0, 0) {
	entities.push_back(new circle(-30, 0, 20, ORANGE));
	entities.push_back(new circle(30, 0, 20, LIME));
}

game::~game() {
	for (auto e : entities) {
		delete e;
	}
}

void game::run() {
	const auto app_name =
#ifdef DEBUG
		"Enchanter [Debug Build]"
#else
		"Enchanter"
#endif
		;

	InitWindow(screenWidth, screenHeight, app_name);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(640, 480);

#ifdef PLATFORM_WEB
	main_game = this;
	emscripten_set_main_loop(run_main_loop, 0, 1);
#else
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		update();
		draw();
	}
#endif

	CloseWindow();
}

void game::update() {
	// Don't process game logic if window is not focused.
	if (!IsWindowFocused()) {
		return;
	}

	if (controls::mouse::in_screen()) {
		if (controls::mouse::right()) {
			auto delta = GetMouseDelta();
			game_world.x += delta.x;
			game_world.y += delta.y;
		}

		auto scroll = GetMouseWheelMove();
		if (std::abs(scroll) > 0.1) {
			game_world.scale_factor = std::min(10, std::max(-10, game_world.scale_factor + (scroll > 0 ? 1 : -1)));
			game_world.scale = std::pow(2, game_world.scale_factor / 2.f);
		}
	}
}

void game::draw() const {
	// Don't render anything to the screen if not focused.
	// Just update and return.
	if (!IsWindowFocused()) {
		BeginDrawing();
		EndDrawing();
		return;
	}

	BeginDrawing();

	ClearBackground(DARKGRAY);

	int center_x = game_world.x;
	int center_y = game_world.y;

	// DrawCircle(center_x, center_y, 10 * std::pow(2, scale / 2.f), LIGHTGRAY);
	for (auto e : entities) {
		e->draw(game_world);
	}

	DrawText("Hello World!", center_x, center_y + 20, 20, LIGHTGRAY);

	EndDrawing();
}

} // namespace enchanter
