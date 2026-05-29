#include "game.hpp"
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static int screenWidth = 1920;
static int screenHeight = 1080;

namespace enchanter {

// Later this will set up data, but for now, nothing.
game::game() {}

void game::run() {
	InitWindow(screenWidth, screenHeight, "Enchanter");

#ifdef PLATFORM_WEB
	emscripten_set_main_loop([this]() { draw(); });
#else

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		draw();
	}
#endif

	CloseWindow();
}

void game::draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);
	DrawText("Hello World!", 190, 200, 20, LIGHTGRAY);

	EndDrawing();
}

} // namespace enchanter
