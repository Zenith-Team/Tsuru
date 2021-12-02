#ifndef SEAD_FRAME_BUFFER_H_
#define SEAD_FRAME_BUFFER_H_

#include "gfx/seadColor.h"
#include "sead/math/seadBoundBox.h"
#include "sead/math/seadVector.h"
#include "sead/prim/seadRuntimeTypeInfo.h"

namespace sead {

class LogicalFrameBuffer
{
    SEAD_RTTI_BASE(LogicalFrameBuffer)

public:
    LogicalFrameBuffer(const Vector2f& virtual_size, const BoundBox2f& physical_area)
    {
        setVirtualSize(virtual_size);
        setPhysicalArea(physical_area);
    }

    LogicalFrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h)
    {
        setVirtualSize(virtual_size);
        setPhysicalArea(physical_x, physical_y, physical_w, physical_h);
    }

    virtual ~LogicalFrameBuffer()
    {
    }

    const Vector2f& getVirtualSize() const
    {
        return mVirtualSize;
    }

    const BoundBox2f& getPhysicalArea() const
    {
        return mPhysicalArea;
    }

    void setVirtualSize(const Vector2f& virtual_size)
    {
        mVirtualSize = virtual_size;
    }

    void setPhysicalArea(const BoundBox2f& ph_size)
    {
        mPhysicalArea.set(ph_size.getMin(), ph_size.getMax());
    }

    void setPhysicalArea(f32 x, f32 y, f32 w, f32 h)
    {
        mPhysicalArea.setFromCornerAndXY(x, y, w, h);
    }

protected:
    Vector2f mVirtualSize;
    BoundBox2f mPhysicalArea;
};
static_assert(sizeof(LogicalFrameBuffer) == 0x1C, "sead::LogicalFrameBuffer size mismatch");

class DisplayBuffer;

class FrameBuffer : public LogicalFrameBuffer
{
    SEAD_RTTI_OVERRIDE(FrameBuffer, LogicalFrameBuffer)

public:
    FrameBuffer(const Vector2f& virtual_size, const BoundBox2f& physical_area)
        : LogicalFrameBuffer(virtual_size, physical_area)
    {
    }

    FrameBuffer(const Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h)
        : LogicalFrameBuffer(virtual_size, physical_x, physical_y, physical_w, physical_h)
    {
    }

    virtual void copyToDisplayBuffer(const DisplayBuffer* display_buffer) const
    {
    }

    virtual void clear(u32 clr_flag, const Color4f& color, f32 depth, u32 stencil) const
    {
    }

    virtual void clearMRT(u32 target, const Color4f& color) const
    {
    }

    virtual void bindImpl_() const
    {
    }

    void bind() const;
};
static_assert(sizeof(FrameBuffer) == 0x1C, "sead::FrameBuffer size mismatch");

}  // namespace sead

#endif // SEAD_FRAME_BUFFER_H_
