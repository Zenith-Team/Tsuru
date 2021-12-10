#pragma once

#include "sead/bitflag.h"
#include "sead/color.h"
#include "sead/graphics.h"

namespace sead {

class GraphicsContext { // Size: 0x74
public:
    struct RenderState {
        u32 polygonModeFront;       // _0
        u32 polygonModeBack;        // _4
        u8 polyOffsetFrontEnable;   // _8
        u8 polyOffsetBackEnable;    // _9
        u8 polyLineOffsetEnable;    // _A
    };

public:
    GraphicsContext();

    virtual void vfC(); // deleted

    void apply();

    bool depthTestEnable;                       // _0
    bool depthWriteEnable;                      // _1
    Graphics::DepthFunc depthFunc;              // _4
    Graphics::CullingMode cullingMode;          // _8
    bool blendEnable;                           // _C
    Graphics::BlendFactor blendFactorSrcRGB;    // _10
    Graphics::BlendFactor blendFactorSrcA;      // _14
    Graphics::BlendFactor blendFactorDstRGB;    // _18
    Graphics::BlendFactor blendFactorDstA;      // _1C
    Graphics::BlendEquation blendEquationRGB;   // _20
    Graphics::BlendEquation blendEquationA;     // _24
    sead::Color4f blendConstantColor;           // _28
    bool alphaTestEnable;                       // _38
    Graphics::AlphaFunc alphaTestFunc;          // _3C
    f32 alphaTestRef;                           // _40
    bool colorMaskR;                            // _44
    bool colorMaskG;                            // _45
    bool colorMaskB;                            // _46
    bool colorMaskA;                            // _47
    bool stencilTestEnable;                     // _48
    Graphics::StencilFunc stencilTestFunc;      // _4C
    s32 stencilTestRef;                         // _50
    u32 stencilTestMask;                        // _54
    Graphics::StencilOp stencilOpFail;          // _58
    Graphics::StencilOp stencilOpZFail;         // _5C
    Graphics::StencilOp stencilOpZPass;         // _60
    RenderState renderState;                    // _64
};

static_assert(sizeof(GraphicsContext) == 0x74, "sead::GraphicsContext size mismatch");

class GraphicsContextMRT { // Size: 0x11C
public:
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
