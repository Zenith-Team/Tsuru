#pragma once

#include "sead/task.h"
#include "agl/renderinfo.h"

class AreaTask : public sead::CalculateTask {
public:
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);

    // Custom functions
    void readOptions();
    void debugDraw(const agl::lyr::RenderInfo& renderInfo);

    static AreaTask* sInstance;

    u8 _0[0x72C];
    u32 mWrapFlag;
    u8 _730[0x4B4];
};
