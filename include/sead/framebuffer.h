#pragma once

#include "sead/runtimetypeinfo.h"
#include "sead/boundbox.h"

namespace sead {

class LogicalFrameBuffer {
    SEAD_RTTI_BASE(LogicalFrameBuffer)

public:
    LogicalFrameBuffer()
        : virtualSize(0.0f)
        , physicalArea(0.0f)
    { }

    LogicalFrameBuffer(const sead::Vec2f& virtualSize, const BoundBox2<f32>& physicalArea)
        : virtualSize(virtualSize)
        , physicalArea(physicalArea)
    { }

    virtual ~LogicalFrameBuffer() { }

    sead::Vec2f virtualSize;
    BoundBox2<f32> physicalArea;
};

static_assert(sizeof(LogicalFrameBuffer) == 0x1C, "sead::LogicalFrameBuffer size mismatch");

class DisplayBuffer;

class FrameBuffer : public LogicalFrameBuffer {
    SEAD_RTTI_OVERRIDE(FrameBuffer, LogicalFrameBuffer)

public:
    FrameBuffer(const sead::Vec2f& virtualSize, const BoundBox2<f32>& physicalArea)
        : LogicalFrameBuffer(virtualSize, physicalArea)
    { }

    virtual void copyToDisplayBuffer(const DisplayBuffer* displayBuffer) const { }
    virtual void clear(u32 clearFlag, const Color4f& color, f32 depth, u32 stencil) const { }
    virtual void clearMRT(u32 target, const Color4f& color) const { }
    virtual void bindImpl_() const { }

    void bind() const;
};

static_assert(sizeof(FrameBuffer) == 0x1C, "sead::FrameBuffer size mismatch");

}
