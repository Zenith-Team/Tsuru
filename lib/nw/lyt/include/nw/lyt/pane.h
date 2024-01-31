#pragma once

#include "types.h"
#include "nw/math/math_Types.h"
#include "nw/ut/ut_LinkList.h"

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
    math::VEC3 translate;
    math::VEC3 rotate;
    math::VEC2 scale;
    u8 _3C[0xa4-0x3c];
};

static_assert(sizeof(Pane) == 0xA4, "nw::lyt::Pane size mismatch");

} }
