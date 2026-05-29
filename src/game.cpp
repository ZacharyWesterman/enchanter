#include "game.hpp"
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

static int screenWidth = 1920;
static int screenHeight = 1080;

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
	InitWindow(screenWidth, screenHeight, "Enchanter");

#ifdef PLATFORM_WEB
	main_game = this;
	emscripten_set_main_loop(run_main_loop, 0, 1);
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
