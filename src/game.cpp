#include "game.hpp"
#include "controls.hpp"
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

// Later this will set up data, but for now, nothing.
game::game() {}

void game::run() {
	const auto appName =
#ifdef DEBUG
		"Enchanter [Debug Build]"
#else
		"Enchanter"
#endif
		;

	InitWindow(screenWidth, screenHeight, appName);
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

	if (controls::mouse::left() && controls::mouse::in_screen()) {
		auto delta = GetMouseDelta();
		pos_x += delta.x;
		pos_y += delta.y;
	}
}

void game::draw() {
	// Don't render anything to the screen if not focused.
	// Just update and return.
	if (!IsWindowFocused()) {
		BeginDrawing();
		EndDrawing();
		return;
	}

	BeginDrawing();

	ClearBackground(DARKGRAY);

	int center_x = GetRenderWidth() / 2 + pos_x;
	int center_y = GetRenderHeight() / 2 + pos_y;

	DrawCircle(center_x, center_y, 10, LIGHTGRAY);

	DrawText("Hello World!", center_x, center_y + 20, 20, LIGHTGRAY);

	EndDrawing();
}

} // namespace enchanter
