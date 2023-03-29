#pragma once

#include "nw/lyt/pane.h"

namespace nw { namespace lyt {

class TextBox : public Pane {
public:
    u16* textBuffer;
    u16 _;
    u8 _AA[90];
};

static_assert(sizeof(TextBox) == 0x104, "nw::lyt::TextBox size mismatch");

} }
