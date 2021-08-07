#pragma once

#include <types.h>

namespace nw { namespace eft {

enum BlendType {
    BlendTypeNormal = 0,
    BlendTypeAdd = 1,
    BlendTypeSub = 2,
    BlendTypeScreen = 3,
    BlendTypeMult = 4,
    BlendTypeUser = 5,
    BlendTypeMax = 6,
};

static_assert(sizeof(BlendType) == 4, "BlendType size mismatch");

enum ColorSourceType { 
    ColorSourceTypeFirst = 0,
    ColorSourceTypeRandom = 1,
    ColorSourceType3v4k = 2,
    ColorSourceTypeMax = 3,
};

static_assert(sizeof(ColorSourceType) == 4, "ColorSourceType size mismatch");

enum CpuCore {
    CpuCore0 = 0,
    CpuCore1 = 1,
    CpuCore2 = 2,
    CpuCoreMax = 3,
};

static_assert(sizeof(CpuCore) == 4, "CpuCore size mismatch");

enum CustomActionCallBackID {
    CustomActionCallBackIDInvalid = 0xFFFFFFFF,
    CustomActionCallBackIDMax = 8,
};

static_assert(sizeof(CustomActionCallBackID) == 4, "CustomActionCallBackID size mismatch");

enum CustomShaderCallBackID {
    CustomShaderCallBackIDMax = 9,
};

static_assert(sizeof(CustomShaderCallBackID) == 4, "CustomShaderCallBackID size mismatch");

enum DisplaySideType {
    DisplaySideTypeBoth = 0,
    DisplaySideTypeFront = 1,
    DisplaySideTypeBack = 2,
    DisplaySideTypeMax = 3,
};

static_assert(sizeof(DisplaySideType) == 4, "DisplaySideType size mismatch");

enum EmitterType {
    EmitterTypeSimple = 0,
    EmitterTypeComplex = 1,
    EmitterTypeMax = 2,
};

static_assert(sizeof(EmitterType) == 4, "EmitterType size mismatch");

enum FragmentComposite { 
    FragmentCompositeMul = 0,
    FragmentCompositeAdd = 1,
    FragmentCompositeSub = 2,
    FragmentCompositeMax = 3,
};

static_assert(sizeof(FragmentComposite) == 4, "FragmentComposite size mismatch");

enum MeshType {
    MeshTypeParticle = 0,
    MeshTypePrimitive = 1,
    MeshTypeStripe = 2,
    MeshTypeMax = 3,
};

static_assert(sizeof(MeshType) == 4, "MeshType size mismatch");

enum ParticleBehaviorFlag {
    ParticleBehaviorFlagAirResist       = 0x0001,
    ParticleBehaviorFlagGravity         = 0x0002,
    ParticleBehaviorFlagRotate          = 0x0004,
    ParticleBehaviorFlagRotInertia      = 0x0008,
    ParticleBehaviorFlagWldPosDf        = 0x0010,
    ParticleBehaviorFlagScaleAnim       = 0x0040,
    ParticleBehaviorFlagAlphaAnim       = 0x0080,
    ParticleBehaviorFlagColor0Anim      = 0x0100,
    ParticleBehaviorFlagColor1Anim      = 0x0200,
    ParticleBehaviorFlagTex0UVShiftAnim = 0x0400,
    ParticleBehaviorFlagTex1UVShiftAnim = 0x0800,
    ParticleBehaviorFlagTex0PtnAnim     = 0x1000,
    ParticleBehaviorFlagTex1PtnAnim     = 0x2000,
    ParticleBehaviorFlagHasTex1         = 0x4000,
};

static_assert(sizeof(ParticleBehaviorFlag) == 4, "ParticleBehaviorFlag size mismatch");

enum PtclFollowType {
    PtclFollowTypeSRT = 0,
    PtclFollowTypeNone = 1,
    PtclFollowTypeTrans = 2,
    PtclFollowTypeMax = 3,
};

static_assert(sizeof(PtclFollowType) == 4, "PtclFollowType size mismatch");

enum PtclType {
    PtclTypeSimple = 0,
    PtclTypeComplex = 1,
    PtclTypeChild = 2,
    PtclTypeMax = 3,
};

static_assert(sizeof(PtclFollowType) == 4, "PtclFollowType size mismatch");

enum ShaderAttrib {
    ShaderAttribScl        = 0x001,
    ShaderAttribTexAnim    = 0x002,
    ShaderAttribSubTexAnim = 0x004,
    ShaderAttribWldPos     = 0x008,
    ShaderAttribWldPosDf   = 0x010,
    ShaderAttribColor0     = 0x020,
    ShaderAttribColor1     = 0x040,
    ShaderAttribRot        = 0x080,
    ShaderAttribEmMat      = 0x100,
};

static_assert(sizeof(ShaderAttrib) == 4, "ShaderAttrib size mismatch");

enum ShaderType {
    ShaderTypeNormal = 0,
    ShaderTypeUserMacro1 = 1,
    ShaderTypeUserMacro2 = 2,
    ShaderTypeMax = 3,
};

static_assert(sizeof(ShaderType) == 4, "ShaderType size mismatch");

enum TextureFilterMode {
    TextureFilterModeLinear = 0,
    TextureFilterModePoint = 1,
    TextureFilterModeMax = 2,
};

static_assert(sizeof(TextureFilterMode) == 4, "TextureFilterMode size mismatch");

enum TextureResFormat { 
    TextureResFormatInvalid = 0,
    TextureResFormatRGB8Unorm = 1,
    TextureResFormatRGBA8Unorm = 2,
    TextureResFormatBC1Unorm = 3,
    TextureResFormatBC1SRGB = 4,
    TextureResFormatBC2Unorm = 5,
    TextureResFormatBC2SRGB = 6,
    TextureResFormatBC3Unorm = 7,
    TextureResFormatBC3SRGB = 8,
    TextureResFormatBC4Unorm = 9,
    TextureResFormatBC4Snorm = 10,
    TextureResFormatBC5Unorm = 11,
    TextureResFormatBC5Snorm = 12,
    TextureResFormatR8Unorm = 13,
    TextureResFormatRG8Unorm = 14,
    TextureResFormatRGBA8SRGB = 15,
    TextureResFormatMax = 16,
};

static_assert(sizeof(TextureResFormat) == 4, "TextureResFormat size mismatch");

enum TextureSlot {
    TextureSlot0 = 0,
    TextureSlot1 = 1,
    TextureSlot2 = 2,
    TextureSlotDepthBuffer = TextureSlot2,
    TextureSlotFrameBuffer = 3,
    TextureSlotMax = 4,
};

static_assert(sizeof(TextureSlot) == 4, "TextureSlot size mismatch");

enum TextureWrapMode {
    TextureWrapModeMirror = 0,
    TextureWrapModeWrap = 1,
    TextureWrapModeClamp = 2,
    TextureWrapModeMirror_Once = 3,
    TextureWrapModeMax = 4,
};

static_assert(sizeof(TextureWrapMode) == 4, "TextureWrapMode size mismatch");

enum VertexRotationMode { 
    VertexRotationModeNone = 0,
    VertexRotationModeRotateX = 1,
    VertexRotationModeRotateY = 2,
    VertexRotationModeRotateZ = 3,
    VertexRotationModeRotateXYZ = 4,
    VertexRotationModeMax = 5,
};

static_assert(sizeof(VertexRotationMode) == 4, "VertexRotationMode size mismatch");

enum VertexTransformMode { 
    VertexTransformModeBillboard = 0,
    VertexTransformModePlateXY = 1,
    VertexTransformModePlateXZ = 2,
    VertexTransformModeDirectionalY = 3,
    VertexTransformModeDirectional_Polygon = 4,
    VertexTransformModeStripe = 5,
    VertexTransformModeComplexStripe = 6,
    VertexTransformModePrimitive = 7,
    VertexTransformModeYBillboard = 8,
};

static_assert(sizeof(VertexTransformMode) == 4, "VertexTransformMode size mismatch");

enum ZBufATestType {
    ZBufATestTypeNormal = 0,
    ZBufATestTypeIgnoreZ = 1,
    ZBufATestTypeAlpha = 2,
    ZBufATestTypeMax = 3,
};

static_assert(sizeof(ZBufATestType) == 4, "ZBufATestType size mismatch");

} }
