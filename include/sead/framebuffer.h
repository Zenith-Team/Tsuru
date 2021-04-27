#pragma once

#include "sead.h"
#include "types.h"
#include "util/rect.h"

namespace sead {

class DisplayBuffer;

class FrameBuffer {
public:
    void bind();

    virtual bool checkDerivedRuntimeTypeInfo(void*);
    virtual void vf14() deleted;
    virtual void vf1C() deleted;
    virtual void copyToDisplayBuffer(DisplayBuffer*);
    virtual void clear(u32 flags, Color4f* color, u32 stencilValue, f32 depthValue);
    virtual void vf34(); //nullptr
    virtual void bindImpl();

    f32 width;
    f32 height;
    Rect rect;
};


}
