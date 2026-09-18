#include "glyph.hpp"
#include <cmath>
#include <string>

#ifndef PI
#define PI 3.141592653589
#endif

namespace enchanter::glyph {

glyph::glyph(position pos, Color col, const char *name, std::initializer_list<mana> &&list) : entity(pos), col(col), name(name) {
	int i = 0;
	for (auto elem : list) {
		if (i >= 6) {
			break;
		}
		io[i] = {affinity::NONE, 0};
		accept[i++] = elem;
	}
}

void glyph::draw() const {
	int radius = 75;

	// Outline
	DrawPolyLinesEx({pos.x, pos.y}, accept.size(), radius, 0, 5, col);

	float frac = 2 * PI / accept.size();

	for (unsigned int i = 0; i < accept.size(); i++) {
		if (accept[i].intensity == 0) {
			continue;
		}

		float angle = PI + i * frac;
		int distance = radius * 2 / 3;

		float rotation = i * 360 / accept.size() + 30 + (accept[i].intensity > 0 ? 180 : 0);

		// I/O arrow
		int arrow_radius = 10;
		float x = sin(angle) * distance;
		float y = cos(angle) * distance;
		DrawPoly({x, y}, 3, arrow_radius, rotation, col);

		// I/O amount
		DrawText(std::to_string(io[i].intensity).c_str(), x, y, 10, BLACK);
	}

	// Name
	int font_size = 20;
	auto width = MeasureText(name, font_size);
	DrawText(name, pos.x - width / 2, pos.y - font_size / 2, font_size, col);
}

void glyph::update() {}

} // namespace enchanter::glyph
