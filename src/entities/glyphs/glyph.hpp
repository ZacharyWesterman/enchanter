#pragma once

#include "../../types/mana.hpp"
#include "../entity.hpp"
#include <array>
#include <raylib.h>

namespace enchanter::glyph {

struct glyph : public entity {
	Color col;
	const char *name;
	std::array<mana, 6> accept;
	std::array<mana, 6> io;

	glyph(position pos, Color col, const char *name, std::initializer_list<mana> &&list);

	void update() override;
	void draw() const override;
};

} // namespace enchanter::glyph
