#pragma once

#include <sead/task.h>
#include <agl/lyr/renderinfo.h>

class AreaTask : public sead::CalculateTask {
public:
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    // Custom functions
    void readOptions();
    void drawLayerDebug(const agl::lyr::RenderInfo& renderInfo);

    static AreaTask* sInstance;

    u8 _C8[1636];
    u32 mWrapFlag;
    u8 _730[1204];
};
