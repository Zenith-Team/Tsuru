#pragma once

//! TODO: I hate this entire header it's so confusing and I cannot understand anything everything is inlined and the inheritance hierarchy is weird please someone smarter than me fix it :)
//? EDIT: Deleted it all in favor of lazy padding, still requires completion

#include <sead/boundbox.h>
#include <sead/runtimetypeinfo.h>
#include <dynlibs/gx2/types.h>

namespace sead {

class FrameBuffer { // Inherits sead::LogicalFrameBuffer
    SEAD_RTTI_BASE(FrameBuffer)

public:
    ~FrameBuffer();

    virtual void vf1C(); // deleted
	virtual void copyToDisplayBuffer(void* displayBuffer);
	virtual void clear(u32 flags, Color4f* color, u32 stencilValue, f32 depthValue);
	virtual void vf34(); // deleted
	virtual void bindImpl_();

    void bind() const;

    Vec2f virtualSize;
    BoundBox2<f32> physicalArea;
};

// TODO: Verify this size
static_assert(sizeof(FrameBuffer) == 0x1C, "sead::FrameBuffer size mismatch");

}
