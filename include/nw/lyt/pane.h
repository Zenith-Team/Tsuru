#pragma once

#include "types.h"
#include "nw/ut/linkedlist.h"

namespace nw { namespace lyt {

namespace internal {

class PaneBase {
public:
    nw::ut::LinkListNode link;

    virtual void vtable(); // TODO
};

}

class Pane : public internal::PaneBase {
public:
    Pane* parent;
    u8 _10[148]; // Unknown values
};

static_assert(sizeof(Pane) == 0xA4, "nw::lyt::Pane size mismatch");

} }
