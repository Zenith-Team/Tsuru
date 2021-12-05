#pragma once

#include "types.h"

namespace nw { namespace eft {

enum BlendType {
    BlendType_Normal = 0,
    BlendType_Add = 1,
    BlendType_Sub = 2,
    BlendType_Screen = 3,
    BlendType_Mult = 4,
    BlendType_User = 5,
    BlendType_Max = 6,
};

enum ColorSourceType {
    ColorSourceType_First = 0,
    ColorSourceType_Random = 1,
    ColorSourceType_3v4k = 2,
    ColorSourceType_Max = 3,
};

enum CpuCore {
    CpuCore_0 = 0,
    CpuCore_1 = 1,
    CpuCore_2 = 2,
    CpuCore_Max = 3,
};

enum CustomActionCallBackID {
    CustomActionCallBackID_Invalid = 0xFFFFFFFF,
    CustomActionCallBackID_Max = 8,
};

enum CustomShaderCallBackID {
    CustomShaderCallBackID_Max = 9,
};

enum DisplaySideType {
    DisplaySideType_Both = 0,
    DisplaySideType_Front = 1,
    DisplaySideType_Back = 2,
    DisplaySideType_Max = 3,
};

enum EmitterType {
    EmitterType_Simple = 0,
    EmitterType_Complex = 1,
    EmitterType_Max = 2,
};

enum FragmentComposite {
    FragmentComposite_Mul = 0,
    FragmentComposite_Add = 1,
    FragmentComposite_Sub = 2,
    FragmentComposite_Max = 3,
};

enum MeshType {
    MeshType_Particle   = 0,
    MeshType_Primitive  = 1,
    MeshType_Stripe     = 2,
    MeshType_Max        = 3,
};

enum ParticleBehaviorFlag {
    ParticleBehaviorFlag_AirResist       = 0x0001,
    ParticleBehaviorFlag_Gravity         = 0x0002,
    ParticleBehaviorFlag_Rotate          = 0x0004,
    ParticleBehaviorFlag_RotInertia      = 0x0008,
    ParticleBehaviorFlag_WldPosDf        = 0x0010,
    ParticleBehaviorFlag_ScaleAnim       = 0x0040,
    ParticleBehaviorFlag_AlphaAnim       = 0x0080,
    ParticleBehaviorFlag_Color0Anim      = 0x0100,
    ParticleBehaviorFlag_Color1Anim      = 0x0200,
    ParticleBehaviorFlag_Tex0UVShiftAnim = 0x0400,
    ParticleBehaviorFlag_Tex1UVShiftAnim = 0x0800,
    ParticleBehaviorFlag_Tex0PtnAnim     = 0x1000,
    ParticleBehaviorFlag_Tex1PtnAnim     = 0x2000,
    ParticleBehaviorFlag_HasTex1         = 0x4000,
};

enum PtclFollowType {
    PtclFollowType_SRT = 0,
    PtclFollowType_None = 1,
    PtclFollowType_Trans = 2,
    PtclFollowType_Max = 3,
};

enum PtclType {
    PtclType_Simple = 0,
    PtclType_Complex = 1,
    PtclType_Child = 2,
    PtclType_Max = 3,
};

enum ShaderAttrib {
    ShaderAttrib_Scl        = 0x001,
    ShaderAttrib_TexAnim    = 0x002,
    ShaderAttrib_SubTexAnim = 0x004,
    ShaderAttrib_WldPos     = 0x008,
    ShaderAttrib_WldPosDf   = 0x010,
    ShaderAttrib_Color0     = 0x020,
    ShaderAttrib_Color1     = 0x040,
    ShaderAttrib_Rot        = 0x080,
    ShaderAttrib_EmMat      = 0x100,
};

enum ShaderType {
    ShaderType_Normal = 0,
    ShaderType_UserMacro1 = 1,
    ShaderType_UserMacro2 = 2,
    ShaderType_Max = 3,
};

enum TextureFilterMode {
    TextureFilterMode_Linear = 0,
    TextureFilterMode_Point = 1,
    TextureFilterMode_Max = 2,
};

enum TextureResFormat {
    TextureResFormat_Invalid = 0,
    TextureResFormat_RGB8Unorm = 1,
    TextureResFormat_RGBA8Unorm = 2,
    TextureResFormat_BC1Unorm = 3,
    TextureResFormat_BC1SRGB = 4,
    TextureResFormat_BC2Unorm = 5,
    TextureResFormat_BC2SRGB = 6,
    TextureResFormat_BC3Unorm = 7,
    TextureResFormat_BC3SRGB = 8,
    TextureResFormat_BC4Unorm = 9,
    TextureResFormat_BC4Snorm = 10,
    TextureResFormat_BC5Unorm = 11,
    TextureResFormat_BC5Snorm = 12,
    TextureResFormat_R8Unorm = 13,
    TextureResFormat_RG8Unorm = 14,
    TextureResFormat_RGBA8SRGB = 15,
    TextureResFormat_Max = 16,
};

enum TextureSlot {
    TextureSlot_0 = 0,
    TextureSlot_1 = 1,
    TextureSlot_2 = 2,
    TextureSlot_DepthBuffer = TextureSlot_2,
    TextureSlot_FrameBuffer = 3,
    TextureSlot_Max = 4,
};

enum TextureWrapMode {
    TextureWrapMode_Mirror = 0,
    TextureWrapMode_Wrap = 1,
    TextureWrapMode_Clamp = 2,
    TextureWrapMode_Mirror_Once = 3,
    TextureWrapMode_Max = 4,
};

enum VertexRotationMode {
    VertexRotationMode_None = 0,
    VertexRotationMode_RotateX = 1,
    VertexRotationMode_RotateY = 2,
    VertexRotationMode_RotateZ = 3,
    VertexRotationMode_RotateXYZ = 4,
    VertexRotationMode_Max = 5,
};

enum VertexTransformMode {
    VertexTransformMode_Billboard = 0,
    VertexTransformMode_PlateXY = 1,
    VertexTransformMode_PlateXZ = 2,
    VertexTransformMode_DirectionalY = 3,
    VertexTransformMode_Directional_Polygon = 4,
    VertexTransformMode_Stripe = 5,
    VertexTransformMode_ComplexStripe = 6,
    VertexTransformMode_Primitive = 7,
    VertexTransformMode_YBillboard = 8,
};

enum ZBufATestType {
    ZBufATestType_Normal = 0,
    ZBufATestType_IgnoreZ = 1,
    ZBufATestType_Alpha = 2,
    ZBufATestType_Max = 3,
};

} }
