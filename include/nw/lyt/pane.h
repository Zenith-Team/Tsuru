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
    u8 childList[0xC];
    Vec3f translate;
    Vec3f rotate;
    Vec2f scale;
    u8 _3C[0xa4-0x3c];
};

static_assert(sizeof(Pane) == 0xA4, "nw::lyt::Pane size mismatch");

} }
