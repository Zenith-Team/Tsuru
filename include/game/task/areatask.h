#pragma once

#include <sead/task.h>
#include <agl/lyr/renderinfo.h>

class AreaTask : public sead::CalculateTask { // Task which manages Zones (class name is official)
    SEAD_SINGLETON_TASK(AreaTask)

public:
    // Draws the layer "3D"
    // @param renderInfo Render info for drawing
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    // Custom function, sets custom physics values based on the wrap flag
    void setPhysicsValues();
    // Custom function, renders collisions for debugging
    // @param renderInfo Render info for drawing
    void renderCollisions(const agl::lyr::RenderInfo& renderInfo);

    u8 _C8[1636];
    u32 wrapFlag;
    u8 _730[1204];
};
