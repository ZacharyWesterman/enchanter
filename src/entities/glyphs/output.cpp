#include "output.hpp"
#include <raylib.h>

#define NONE_ANY {affinity::NONE, 0}
#define OUT_ANY {affinity::NONE, -1}
#define IN_ANY {affinity::NONE, 1}

namespace enchanter::glyph {

output::output(position pos) : glyph(pos, BLUE, "glyph::output", {IN_ANY, NONE_ANY, NONE_ANY, NONE_ANY, NONE_ANY, NONE_ANY}) {}

} // namespace enchanter::glyph
