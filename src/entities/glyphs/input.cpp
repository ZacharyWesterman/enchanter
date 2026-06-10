#include "input.hpp"
#include <raylib.h>

namespace enchanter::glyph {

void input::update() {}

void input::draw() const {
	// Outline
	DrawPolyLinesEx({x, y}, 6, 75, 0, 5, YELLOW);

	// Input arrow
	DrawPoly({x, y - 50}, 3, 10, -30, YELLOW);

	int font_size = 20;
	auto name = "glyph::input";
	auto width = MeasureText(name, font_size);
	DrawText(name, x - width / 2, y - font_size / 2, font_size, YELLOW);
}

} // namespace enchanter::glyph
