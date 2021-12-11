#pragma once

#include "sead/bitflag.h"
#include "sead/color.h"
#include "sead/graphics.h"

namespace sead {

class GraphicsContext { // Size: 0x74
public:
    struct RenderState {
        u32 polygonModeFront;                   // _0     Inited to Fill
        u32 polygonModeBack;                    // _4     Inited to Fill
        bool polyOffsetFrontEnable;             // _8     Inited to false
        bool polyOffsetBackEnable;              // _9     Inited to false
        bool polyLineOffsetEnable;              // _A     Inited to false
    };

public:
    GraphicsContext();

    virtual void vfC(); // deleted

    void apply();

    bool depthTestEnable;                       // _0      Inited to true
    bool depthWriteEnable;                      // _1      Inited to true
    Graphics::DepthFunc depthFunc;              // _4      Inited to LessEqual
    Graphics::CullingMode cullingMode;          // _8      Inited to Back
    bool blendEnable;                           // _C      Inited to true
    Graphics::BlendFactor blendFactorSrcRGB;    // _10     Inited to SrcAlpha
    Graphics::BlendFactor blendFactorSrcA;      // _14     Inited to SrcAlpha
    Graphics::BlendFactor blendFactorDstRGB;    // _18     Inited to InvSrcAlpha
    Graphics::BlendFactor blendFactorDstA;      // _1C     Inited to InvSrcAlpha
    Graphics::BlendEquation blendEquationRGB;   // _20     Inited to Add
    Graphics::BlendEquation blendEquationA;     // _24     Inited to Add
    sead::Color4f blendConstantColor;           // _28     Inited to colorWhite
    bool alphaTestEnable;                       // _38     Inited to false
    Graphics::AlphaFunc alphaTestFunc;          // _3C     Inited to Greater
    f32 alphaTestRef;                           // _40     Inited to 0.0f
    bool colorMaskR;                            // _44     Inited to true
    bool colorMaskG;                            // _45     Inited to true
    bool colorMaskB;                            // _46     Inited to true
    bool colorMaskA;                            // _47     Inited to true
    bool stencilTestEnable;                     // _48     Inited to false
    Graphics::StencilFunc stencilTestFunc;      // _4C     Inited to Never
    s32 stencilTestRef;                         // _50     Inited to 0
    u32 stencilTestMask;                        // _54     Inited to 0xFFFFFFFF
    Graphics::StencilOp stencilOpFail;          // _58     Inited to Keep
    Graphics::StencilOp stencilOpZFail;         // _5C     Inited to Keep
    Graphics::StencilOp stencilOpZPass;         // _60     Inited to Keep
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
