#pragma once

#include "sead/bitflag.h"
#include "sead/color.h"

namespace sead {

struct BlendExpression { // Size: 0x18
    inline BlendExpression()
        : colorSrcBlend(4)
        , colorCombine(0)
        , colorDstBlend(5)
        , alphaSrcBlend(4)
        , alphaDstBlend(5)
        , alphaCombine(0)
    { }

    u32 colorSrcBlend;
    u32 alphaSrcBlend;
    u32 colorDstBlend;
    u32 alphaDstBlend;
    u32 colorCombine;
    u32 alphaCombine;
};

class GraphicsContext { // Size: 0x74
public:
    GraphicsContext();

    virtual void vfC(); // deleted

    void apply();

    bool depthEnable;                       // 0
    bool depthWriteEnable;                  // 1
    u32 depthFunc;                          // 4
    u32 _8;                                 // 8
    bool blendEnable;                       // C
    BlendExpression blendExpression;        // D
    Color4f blendColor;                     // 28
    bool alphaTestEnable;                   // 38
    u32 alphaFunc;                          // 3C
    f32 ref;                                // 40
    u8 _44;                                 // 44
    u8 _45;                                 // 45
    u8 _46;                                 // 46
    u8 _47;                                 // 47
    bool stencilEnable;                     // 48
    u32 stencilFunc;                        // 4C
    u32 writeMask;                          // 50
    s32 preMask;                            // 54
    u32 stencilFail;                        // 58
    u32 stencilZFail;                       // 5C
    u32 stencilZPass;                       // 60
    u32 polygonModeFront;                   // 64
    u32 polygonModeBack;                    // 68
    bool polyOffsetFrontEnable;             // 6C
    bool polyOffsetBackEnable;              // 6D
    bool polyLineOffsetEnable;              // 6E
};

static_assert(sizeof(GraphicsContext) == 0x74, "sead::GraphicsContext size mismatch");

class GraphicsContextMRT { // Size: 0x11C
public:
    GraphicsContextMRT();

    virtual void vfC(); // deleted

    bool depthEnable;                       // 0
    bool depthWriteEnable;                  // 1
    u32 depthFunc;                          // 4
    u32 _8;                                 // 8
    sead::BitFlag32 blendEnableMask;        // C
    BlendExpression blendExpressions[8];    // 10
    Color4f blendColor;                     // D0
    bool alphaTestEnable;                   // E0
    u32 alphaFunc;                          // E4
    f32 ref;                                // E8
    s32 targetChannelMasks;                 // EC
    bool stencilEnable;                     // F0
    u32 stencilFunc;                        // F4
    u32 writeMask;                          // F8
    s32 preMask;                            // FC
    u32 stencilFail;                        // 100
    u32 stencilZFail;                       // 104
    u32 stencilZPass;                       // 108
    u32 _10C;                               // 10C
    u32 _110;                               // 110
    u8 _114;                                // 114
};

static_assert(sizeof(GraphicsContextMRT) == 0x11C, "sead::GraphicsContextMRT size mismatch");

}
