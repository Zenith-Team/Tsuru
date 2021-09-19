#pragma once

#include <sead/task.h>
#include <agl/lyr/renderinfo.h>

class AreaTask : public sead::CalculateTask {
    SEAD_SINGLETON_TASK(AreaTask)

public:
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    // Custom functions
    void setPhysicsValues();
    void renderCollisions(const agl::lyr::RenderInfo& renderInfo);

    u8 _C8[1636];
    u32 wrapFlag;
    u8 _730[1204];
};
