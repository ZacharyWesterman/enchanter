#include "wire.hpp"
#include <raylib.h>

#define NONE_ANY {affinity::NONE, 0}
#define OUT_ANY {affinity::NONE, -1}
#define IN_ANY {affinity::NONE, 1}

namespace enchanter::glyph {

wire::wire(position pos) : glyph(pos, RAYWHITE, "glyph::wire", {IN_ANY, NONE_ANY, NONE_ANY, OUT_ANY, NONE_ANY, NONE_ANY}) {}

} // namespace enchanter::glyph
