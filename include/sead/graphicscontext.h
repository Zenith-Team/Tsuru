#pragma once

#include "sead/bitflag.h"
#include "sead/color.h"
#include "sead/graphics.h"

namespace sead {

class GraphicsContext { // Size: 0x74
public:
    struct RenderState {
        u32 polygonModeFront;
        u32 polygonModeBack;
        u8 polyOffsetFrontEnable;
        u8 polyOffsetBackEnable;
        u8 polyLineOffsetEnable;
    };

public:
    GraphicsContext();

    virtual void vfC(); // deleted

    void apply();

    bool depthTestEnable;
    bool depthWriteEnable;
    Graphics::DepthFunc depthFunc;
    Graphics::CullingMode cullingMode;
    bool blendEnable;
    Graphics::BlendFactor blendFactorSrcRGB;
    Graphics::BlendFactor blendFactorSrcA;
    Graphics::BlendFactor blendFactorDstRGB;
    Graphics::BlendFactor blendFactorDstA;
    Graphics::BlendEquation blendEquationRGB;
    Graphics::BlendEquation blendEquationA;
    sead::Color4f blendConstantColor;
    bool alphaTestEnable;
    Graphics::AlphaFunc alphaTestFunc;
    f32 alphaTestRef;
    bool colorMaskR;
    bool colorMaskG;
    bool colorMaskB;
    bool colorMaskA;
    bool stencilTestEnable;
    Graphics::StencilFunc stencilTestFunc;
    s32 stencilTestRef;
    u32 stencilTestMask;
    Graphics::StencilOp stencilOpFail;
    Graphics::StencilOp stencilOpZFail;
    Graphics::StencilOp stencilOpZPass;
    RenderState renderState;
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
