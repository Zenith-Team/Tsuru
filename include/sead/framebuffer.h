#pragma once

#include <sead/boundbox.h>
#include <sead/runtimetypeinfo.h>
#include <sead/color.h>

namespace sead {

class DisplayBuffer;

class LogicalFrameBuffer { // Size: 0x1C
    SEAD_RTTI_BASE(LogicalFrameBuffer)

public:
    virtual void vf1C(); // deleted
	virtual void copyToDisplayBuffer(const DisplayBuffer* displayBuffer);
	virtual void clear(u32, u32, const Color4f& color, f32 depthValue, u32 stencilValue);
	virtual void vf34(); // deleted
	virtual void bindImpl_();

    void bind() const;

    Vec2f virtualSize;
    BoundBox2<f32> physicalArea;
};

class FrameBuffer : public LogicalFrameBuffer { // Size: 0x1C
};

static_assert(sizeof(FrameBuffer) == 0x1C, "sead::FrameBuffer size mismatch");

}
