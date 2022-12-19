#pragma once

#include "sead/task.h"
#include "agl/lyr/renderinfo.h"

class AreaTask : public sead::CalculateTask {
    SEAD_SINGLETON_TASK(AreaTask);

public:
    ENUM_CLASS(Flag,
        Wrap = 1 << 0,
        LowGravity = 1 << 1
    );

public:
    // Draws the layer "3D"
    // @param renderInfo Render info for drawing
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    // Custom function, renders collisions for debugging
    // @param renderInfo Render info for drawing
    void renderCollisions(const agl::lyr::RenderInfo& renderInfo);

    u8 _C8[0x72C - 0xCC];
    u32 flags;
};
