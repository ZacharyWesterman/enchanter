#include "input.hpp"
#include <cmath>
#include <raylib.h>

#define NONE_ANY {affinity::NONE, 0}
#define OUT_ANY {affinity::NONE, -1}
#define IN_ANY {affinity::NONE, 1}

namespace enchanter::glyph {

input::input(position pos) : glyph(pos, YELLOW, "glyph::input", {NONE_ANY, NONE_ANY, NONE_ANY, OUT_ANY, NONE_ANY, NONE_ANY}) {}

} // namespace enchanter::glyph
