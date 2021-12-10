#pragma once

namespace sead {

class Graphics {
public:
    enum DevicePosture {
        DevicePosture_Same              = 0,
        DevicePosture_RotateRight       = 1,
        DevicePosture_RotateLeft        = 2,
        DevicePosture_RotateHalfAround  = 3,
        DevicePosture_FlipX             = 4,
        DevicePosture_FlipY             = 5,
        DevicePosture_FlipXY            = 3,
        DevicePosture_Invalid           = 4
    };

    enum DepthFunc {
        DepthFunc_Never                 = 0,
        DepthFunc_Less                  = 1,
        DepthFunc_Equal                 = 2,
        DepthFunc_LessEqual             = 3,
        DepthFunc_Greater               = 4,
        DepthFunc_NotEqual              = 5,
        DepthFunc_GreaterEqual          = 6,
        DepthFunc_Always                = 7
    };

    enum CullingMode {
        CullingMode_Front               = 0,
        CullingMode_Back                = 1,
        CullingMode_None                = 2,
        CullingMode_All                 = 3
    };

    enum BlendFactor {
        BlendFactor_Zero                = 0,
        BlendFactor_One                 = 1,
        BlendFactor_SrcColor            = 2,
        BlendFactor_InvSrcColor         = 3,
        BlendFactor_SrcAlpha            = 4,
        BlendFactor_InvSrcAlpha         = 5,
        BlendFactor_DstAlpha            = 6,
        BlendFactor_InvDstAlpha         = 7,
        BlendFactor_DstColor            = 8,
        BlendFactor_InvDstColor         = 9,
        BlendFactor_SrcAlphaSaturate    = 10,
        BlendFactor_ConstantColor       = 13,
        BlendFactor_InvConstantColor    = 14,
        BlendFactor_ConstantAlpha       = 19,
        BlendFactor_InvConstantAlpha    = 20
    };

    enum BlendEquation {
        BlendEquation_Add               = 0,
        BlendEquation_Subtract          = 1,
        BlendEquation_Min               = 2,
        BlendEquation_Max               = 3,
        BlendEquation_ReverseSubtract   = 4
    };

    enum AlphaFunc {
        AlphaFunc_Never                 = 0,
        AlphaFunc_Less                  = 1,
        AlphaFunc_Equal                 = 2,
        AlphaFunc_LessEqual             = 3,
        AlphaFunc_Greater               = 4,
        AlphaFunc_NotEqual              = 5,
        AlphaFunc_GreaterEqual          = 6,
        AlphaFunc_Always                = 7
    };

    enum StencilFunc {
        StencilFunc_Never               = 0,
        StencilFunc_Less                = 1,
        StencilFunc_Equal               = 2,
        StencilFunc_LessEqual           = 3,
        StencilFunc_Greater             = 4,
        StencilFunc_NotEqual            = 5,
        StencilFunc_GreaterEqual        = 6,
        StencilFunc_Always              = 7
    };

    enum StencilOp {
        StencilOp_Keep                  = 0,
        StencilOp_Zero                  = 1,
        StencilOp_Replace               = 2,
        StencilOp_Incriment             = 3,
        StencilOp_Decriment             = 4,
        StencilOp_Invert                = 5,
        StencilOp_IncrimentWrap         = 6,
        StencilOp_DecrimentWrap         = 7
    };
};

}
