#include "game.hpp"
#include "controls.hpp"
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
	main_game->update();
	main_game->draw();
}
#endif

namespace enchanter {

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
			game_world.pan(delta.x, delta.y);
		}

		auto scroll = GetMouseWheelMove();
		if (std::abs(scroll) > 0.1) {
			game_world.zoom(scroll >= 0 ? 1 : -1);
		}
	}

	game_world.update();
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

	game_world.draw();

	DrawLine(GetRenderWidth() / 2, GetRenderHeight() / 2 - 20, GetRenderWidth() / 2, GetRenderHeight() / 2 + 20, RAYWHITE);
	DrawLine(GetRenderWidth() / 2 - 20, GetRenderHeight() / 2, GetRenderWidth() / 2 + 20, GetRenderHeight() / 2, RAYWHITE);

	EndDrawing();
}

} // namespace enchanter
