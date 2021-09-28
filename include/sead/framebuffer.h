#pragma once

//! TODO: I hate this entire header it's so confusing and I cannot understand anything everything is inlined and the inheritance hierarchy is weird please someone smarter than me fix it :)
//? EDIT: Deleted it all in favor of lazy padding, still requires completion

#include <sead/boundbox.h>
#include <sead/runtimetypeinfo.h>
#include <dynlibs/gx2/types.h>

namespace sead {

class FrameBuffer { // Inherits sead::LogicalFrameBuffer
public:
    ~FrameBuffer();

    void bind() const;

    u8 _0[0x18];
};

static_assert(sizeof(FrameBuffer) == 0x18, "sead::FrameBuffer size mismatch");

}
