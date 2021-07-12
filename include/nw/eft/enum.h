#ifndef EFT_ENUM_H_
#define EFT_ENUM_H_

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
static_assert(sizeof(BlendType) == 4, "BlendType size mismatch");

enum ColorSourceType {  // Actual name not known 
    ColorSourceType_First = 0,
    ColorSourceType_Random = 1,
    ColorSourceType_3v4k = 2,
    ColorSourceType_Max = 3,
};
static_assert(sizeof(ColorSourceType) == 4, "ColorSourceType size mismatch");

enum CpuCore {
    CpuCore_0 = 0,
    CpuCore_1 = 1,
    CpuCore_2 = 2,
    CpuCore_Max = 3,
};
static_assert(sizeof(CpuCore) == 4, "CpuCore size mismatch");

enum CustomActionCallBackID {
    CustomActionCallBackID_Invalid = 0xFFFFFFFF,
    CustomActionCallBackID_Max = 8,
};
static_assert(sizeof(CustomActionCallBackID) == 4, "CustomActionCallBackID size mismatch");

enum CustomShaderCallBackID {
    CustomShaderCallBackID_Max = 9,
};
static_assert(sizeof(CustomShaderCallBackID) == 4, "CustomShaderCallBackID size mismatch");

enum DisplaySideType {
    DisplaySideType_Both = 0,
    DisplaySideType_Front = 1,
    DisplaySideType_Back = 2,
    DisplaySideType_Max = 3,
};
static_assert(sizeof(DisplaySideType) == 4, "DisplaySideType size mismatch");

enum EmitterType {  // Actual name not known
    EmitterType_Simple = 0,
    EmitterType_Complex = 1,
    EmitterType_Max = 2,
};
static_assert(sizeof(EmitterType) == 4, "EmitterType size mismatch");

enum FragmentComposite {  // Actual name not known 
    FragmentComposite_Mul = 0,
    FragmentComposite_Add = 1,
    FragmentComposite_Sub = 2,
    FragmentComposite_Max = 3,
};
static_assert(sizeof(FragmentComposite) == 4, "FragmentComposite size mismatch");

enum MeshType {
    MeshType_Particle = 0,
    MeshType_Primitive = 1,
    MeshType_Stripe = 2,
    MeshType_Max = 3,
};
static_assert(sizeof(MeshType) == 4, "MeshType size mismatch");

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
static_assert(sizeof(ParticleBehaviorFlag) == 4, "ParticleBehaviorFlag size mismatch");

enum PtclFollowType {
    PtclFollowType_SRT = 0,
    PtclFollowType_None = 1,
    PtclFollowType_Trans = 2,
    PtclFollowType_Max = 3,
};
static_assert(sizeof(PtclFollowType) == 4, "PtclFollowType size mismatch");

enum PtclType {  // Actual name not known
    PtclType_Simple = 0,
    PtclType_Complex = 1,
    PtclType_Child = 2,
    PtclType_Max = 3,
};
static_assert(sizeof(PtclFollowType) == 4, "PtclFollowType size mismatch");

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
static_assert(sizeof(ShaderAttrib) == 4, "ShaderAttrib size mismatch");

enum ShaderType {
    ShaderType_Normal = 0,
    ShaderType_UserMacro1 = 1,
    ShaderType_UserMacro2 = 2,
    ShaderType_Max = 3,
};
static_assert(sizeof(ShaderType) == 4, "ShaderType size mismatch");

enum TextureFilterMode {
    TextureFilterMode_Linear = 0,
    TextureFilterMode_Point = 1,
    TextureFilterMode_Max = 2,
};
static_assert(sizeof(TextureFilterMode) == 4, "TextureFilterMode size mismatch");

enum TextureResFormat {  // Actual name not known 
    TextureResFormat_Invalid = 0,
    TextureResFormat_RGB8_Unorm = 1,
    TextureResFormat_RGBA8_Unorm = 2,
    TextureResFormat_BC1_Unorm = 3,
    TextureResFormat_BC1_SRGB = 4,
    TextureResFormat_BC2_Unorm = 5,
    TextureResFormat_BC2_SRGB = 6,
    TextureResFormat_BC3_Unorm = 7,
    TextureResFormat_BC3_SRGB = 8,
    TextureResFormat_BC4_Unorm = 9,
    TextureResFormat_BC4_Snorm = 10,
    TextureResFormat_BC5_Unorm = 11,
    TextureResFormat_BC5_Snorm = 12,
    TextureResFormat_R8_Unorm = 13,
    TextureResFormat_RG8_Unorm = 14,
    TextureResFormat_RGBA8_SRGB = 15,
    TextureResFormat_Max = 16,
};
static_assert(sizeof(TextureResFormat) == 4, "TextureResFormat size mismatch");

enum TextureSlot {
    TextureSlot_0 = 0,
    TextureSlot_1 = 1,
    TextureSlot_2 = 2,
    TextureSlot_Depth_Buffer = TextureSlot_2,
    TextureSlot_Frame_Buffer = 3,
    TextureSlot_Max = 4,
};
static_assert(sizeof(TextureSlot) == 4, "TextureSlot size mismatch");

enum TextureWrapMode {
    TextureWrapMode_Mirror = 0,
    TextureWrapMode_Wrap = 1,
    TextureWrapMode_Clamp = 2,
    TextureWrapMode_Mirror_Once = 3,
    TextureWrapMode_Max = 4,
};
static_assert(sizeof(TextureWrapMode) == 4, "TextureWrapMode size mismatch");

enum VertexRotationMode {  // Actual name not known 
    VertexRotationMode_None = 0,
    VertexRotationMode_Rotate_X = 1,
    VertexRotationMode_Rotate_Y = 2,
    VertexRotationMode_Rotate_Z = 3,
    VertexRotationMode_Rotate_XYZ = 4,
    VertexRotationMode_Max = 5,
};
static_assert(sizeof(VertexRotationMode) == 4, "VertexRotationMode size mismatch");

enum VertexTransformMode {  // Actual name not known 
    VertexTransformMode_Billboard = 0,
    VertexTransformMode_Plate_XY = 1,
    VertexTransformMode_Plate_XZ = 2,
    VertexTransformMode_Directional_Y = 3,
    VertexTransformMode_Directional_Polygon = 4,
    VertexTransformMode_Stripe = 5,
    VertexTransformMode_Complex_Stripe = 6,
    VertexTransformMode_Primitive = 7,
    VertexTransformMode_Y_Billboard = 8,
};
static_assert(sizeof(VertexTransformMode) == 4, "VertexTransformMode size mismatch");

enum ZBufATestType {
    ZBufATestType_Normal = 0,
    ZBufATestType_Ignore_Z = 1,
    ZBufATestType_Alpha = 2,
    ZBufATestType_Max = 3,
};
static_assert(sizeof(ZBufATestType) == 4, "ZBufATestType size mismatch");

} } // namespace nw::eft

#endif // EFT_ENUM_H_
