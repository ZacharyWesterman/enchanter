#pragma once

#include "../../types/mana.hpp"
#include "glyph_base.hpp"

namespace enchanter::glyph {

struct input : public glyph_base {
	using glyph_base::glyph_base;

	void update() override;
	void draw() const override;
};

} // namespace enchanter::glyph
