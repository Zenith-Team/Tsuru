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
        DevicePosture_Invalid           = 4,
    };

    enum DepthFunc {
        DepthFunc_Invalid               = 0xFFFFFFFF,
        DepthFunc_Never                 = 0,
        DepthFunc_Always                = 1,
        DepthFunc_Equal                 = 2,
        DepthFunc_NotEqual              = 3,
        DepthFunc_Less                  = 4,
        DepthFunc_LessEqual             = 5,
        DepthFunc_Greater               = 6,
        DepthFunc_GreaterEqual          = 7,
    };

    enum CullingMode {
        CullingMode_None                = 0xFFFFFFF0,
        CullingMode_All                 = 0xFFFFFFF1,
        CullingMode_Invalid             = 0xFFFFFFFF,
        CullingMode_Front               = 0,
        CullingMode_Back                = 1,
    };

    enum BlendFactor {
        BlendFactor_Invalid             = 0xFFFFFFFF,
        BlendFactor_Zero                = 0,
        BlendFactor_One                 = 1,
        BlendFactor_SrcColor            = 2,
        BlendFactor_InvSrcColor         = 3,
        BlendFactor_DstColor            = 4,
        BlendFactor_InvDstColor         = 5,
        BlendFactor_SrcAlpha            = 6,
        BlendFactor_InvSrcAlpha         = 7,
        BlendFactor_DstAlpha            = 8,
        BlendFactor_InvDstAlpha         = 9,
        BlendFactor_ConstantColor       = 10,
        BlendFactor_InvConstantColor    = 11,
        BlendFactor_ConstantAlpha       = 12,
        BlendFactor_InvConstantAlpha    = 13,
        BlendFactor_SrcAlphaSaturate    = 14,
    };

    enum BlendEquation {
        BlendEquation_Invalid           = 0xFFFFFFFF,
        BlendEquation_Add               = 0,
        BlendEquation_Subtract          = 1,
        BlendEquation_ReverseSubtract   = 2,
        BlendEquation_Min               = 3,
        BlendEquation_Max               = 4,
    };

    enum AlphaFunc {
        AlphaFunc_Invalid               = 0xFFFFFFFF,
        AlphaFunc_Never                 = 0,
        AlphaFunc_Always                = 1,
        AlphaFunc_Equal                 = 2,
        AlphaFunc_NotEqual              = 3,
        AlphaFunc_Less                  = 4,
        AlphaFunc_LessEqual             = 5,
        AlphaFunc_Greater               = 6,
        AlphaFunc_GreaterEqual          = 7,
    };

    enum StencilFunc {
        StencilFunc_Invalid             = 0xFFFFFFFF,
        StencilFunc_Never               = 0,
        StencilFunc_Always              = 1,
        StencilFunc_Equal               = 2,
        StencilFunc_NotEqual            = 3,
        StencilFunc_Less                = 4,
        StencilFunc_LessEqual           = 5,
        StencilFunc_Greater             = 6,
        StencilFunc_GreaterEqual        = 7,
    };

    enum StencilOp {
        StencilOp_Invalid               = 0xFFFFFFFF,
        StencilOp_Keep                  = 0,
        StencilOp_Zero                  = 1,
        StencilOp_Replace               = 2,
        StencilOp_Incriment             = 3,
        StencilOp_Decriment             = 4,
        StencilOp_Invert                = 5,
        StencilOp_IncrimentWrap         = 6,
        StencilOp_DecrimentWrap         = 7,
    };
};

}
