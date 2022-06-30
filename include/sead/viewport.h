#pragma once

#include "boundbox.h"
#include "framebuffer.h"
#include "sead/graphics.h"

namespace sead {

class Viewport : public BoundBox2<f32> {
public:
    Viewport();
    Viewport(f32, f32, f32, f32);
    Viewport(const BoundBox2<f32>& box);
    Viewport(const LogicalFrameBuffer& frame_buffer);

    virtual ~Viewport() { }

    void apply(const LogicalFrameBuffer& frame_buffer) const;

protected:
    Graphics::DevicePosture devicePosture;
};

static_assert(sizeof(Viewport) == 0x18, "sead::Viewport size mismatch");

}
