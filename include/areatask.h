#pragma once

#include "agl/renderinfo.h"

class AreaTask {  // size: 0xBE4
public:
    void readOptions();
    void drawLayer3D(const agl::lyr::RenderInfo& renderInfo);
    void debugDraw(const agl::lyr::RenderInfo& renderInfo);

    static AreaTask* instance;

    u8 _0[0x72C];     // 0
    u32 wrapFlag;     // 72C
    u8 _730[0x4B4];   // 730
};
