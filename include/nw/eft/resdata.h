#pragma once

#include <dynlibs/gx2/types.h>
#include <nw/math/mtx34.h>
#include <nw/math/vec3.h>
#include <nw/ut/color4f.h>
#include <nw/eft/enum.h>

namespace nw { namespace eft{

struct TextureRes { // Size: 0x114
    u16 width;
    u16 height;
    u32 tileMode; // GX2TileMode
    u32 swizzle;
    u32 alignment;
    u32 pitch;
    u8 wrapMode;
    u8 filterMode;
    u32 numMips;
    u32 compSel;
    u32 mipOffset[13];
    f32 maxLOD;
    f32 biasLOD;
    TextureResFormat originalTexFormat;
    u32 originalTexDataOffs;
    u32 originalTexDataSize;
    TextureResFormat cafeTexFormat;
    u32 cafeTexDataSize;
    u32 cafeTexDataOffs;
    u32 initialized;
    GX2Texture GX2Texture;
};

static_assert(sizeof(TextureRes) == 0x114, "nw::eft::TextureRes size mismatch");

struct EmitterData { // Size: 0x280
    EmitterType type;
    u32 flags;
    u32 seed;
    u32 userData;
    u8 unusedPad0[36];
    CustomActionCallBackID callbackID;
    u32 nameOffs;
    const char* name;
    TextureRes textures[2];
    void* keyAnimArray;
    u32 keyAnimArrayOffs;
    u32 keyAnimArraySize;
    u8 unusedPad1[8];
    u32 primitiveIdx;
};

static_assert(sizeof(EmitterData) == 0x280, "nw::eft::EmitterData size mismatch");

struct TextureEmitterData { // Size: 0x78
    bool hasTexPtnAnim;
    bool texPtnAnimRandStart;
    bool texPtnAnimClamp;
    u8 texPtnAnimIdxDiv;
    u8 unusedPad0;
    u8 texPtnAnimNum;
    u8 unusedPad1[2];
    s16 texPtnAnimPeriod;
    s16 texPtnAnimUsedSize;
    u8 texPtnAnimData[32];
    u8 unusedPad2[4];
    math::VEC2 UVScaleInit;
    u32 UVShiftAnimMode;
    math::VEC2 texIncScroll;
    math::VEC2 texInitScroll;
    math::VEC2 texInitScrollRandom;
    math::VEC2 texIncScale;
    math::VEC2 texInitScale;
    math::VEC2 texInitScaleRandom;
    f32 texIncRotate;
    f32 texInitRotate;
    f32 texInitRotateRandom;
};

static_assert(sizeof(TextureEmitterData) == 0x78, "nw::eft::TextureEmitterData size mismatch");

struct anim3v4Key { // Size: 0x14
    f32 startValue;
    f32 startDiff;
    f32 endDiff;
    s32 time;
    s32 time2;
};

static_assert(sizeof(anim3v4Key) == 0x14, "nw::eft::anim3v4Key size mismatch");

struct SimpleEmitterData : EmitterData { // Size: 0x6F4
    u8 unused0[3];
    u8 transformGravity;
    u8 unused1;
    u8 noEmitAtFade;
    u8 sphereDivTblIdx;
    u8 arcStartAngleRandom;
    u8 displayParent;
    u8 emitSameDistance;
    u8 sphereUseLatitude;
    VertexRotationMode rotationMode;
    PtclFollowType ptclFollowType;
    u32 fragmentColorMode;
    u32 fragmentAlphaMode;
    s32 bitForUnusedFlag;
    DisplaySideType displaySideType;
    f32 momentumRandom;
    math::MTX34 animMatrixSRT;
    math::MTX34 animMatrixRT;
    math::VEC3 emitterScale;
    math::VEC3 emitterRotate;
    math::VEC3 emitterTranslate;
    math::VEC3 emitterRotateRandom;
    math::VEC3 emitterTranslateRandom;
    BlendType blendType;
    ZBufATestType zBufATestType;
    u32 emitFunction;
    math::VEC3 volumeScale;
    s32 arcStartAngle;
    u32 arcLength;
    f32 volumeFillRatio;
    f32 sphereLatitude;
    math::VEC3 sphereLatitudeDir;
    f32 lineCenter;
    math::VEC3 emissionShapeScale;
    ut::Color4f emitterColor0;
    ut::Color4f emitterColor1;
    f32 emitterAlpha;
    f32 emitSameDistanceUnit;
    f32 emitSameDistanceMax;
    f32 emitSameDistanceMin;
    f32 emitSameDistanceThreshold;
    f32 emissionRate;
    s32 startFrame;
    s32 endFrame;
    s32 emitInterval;
    s32 emitIntervalRandom;
    f32 allDirVel;
    f32 dirVel;
    f32 dirVelRandom;
    math::VEC3 dir;
    f32 dispersionAngle;
    math::VEC3 diffusionVel;
    f32 airResist;
    math::VEC3 gravity;
    f32 yDiffusionVel;
    f32 ptclPosRandom;
    s32 ptclMaxLifespan;
    s32 ptclLifespanRandom;
    MeshType meshType;
    VertexTransformMode vertexTransformMode;
    math::VEC2 rotBasis;
    f32 cameraOffset;
    TextureEmitterData texAnimParam[2];
    ColorSourceType ptclColorSrc[2];
    ut::Color4f ptclColorTbl[2][3];
    s32 colorTime[2];
    s32 colorTime2[2];
    s32 colorTime3[2];
    s32 colorNumRepetition[2];
    s32 colorRandomStart[2];
    f32 colorScaleFactor;
    anim3v4Key alphaAnim;
    FragmentComposite textureColorBlend;
    FragmentComposite primitiveColorBlend;
    FragmentComposite textureAlphaBlend;
    FragmentComposite primitiveAlphaBlend;
    s32 scaleAnimTime;
    s32 scaleAnimTime2;
    f32 ptclScaleRandom;
    math::VEC2 ptclEmitScale;
    math::VEC2 ptclScaleStart;
    math::VEC2 ptclScaleStartDiff;
    math::VEC2 ptclScaleEndDiff;
    math::VEC3 ptclRotate;
    math::VEC3 ptclRotateRandom;
    math::VEC3 angularVelocity;
    math::VEC3 angularVelocityRandom;
    f32 rotInertia;
    f32 fadeAlphaStep;
    u8 fragmentShaderMode;
    u8 shaderUserSetting;
    bool fragmentSoftEdge;
    bool refractionApplyAlpha;
    math::VEC2 shaderParam01;
    f32 fragmentSoftEdgeFadeDist;
    f32 fragmentSoftEdgeVolume;
    char userMacro1[16];
    char userMacro2[16];
    u32 shaderUserFlag;
    u32 shaderUserSwitchFlag;
    u8 unusedPad[0x6F4 - 0x674];
};

static_assert(sizeof(SimpleEmitterData) == 0x6F4, "nw::eft::SimpleEmitterData size mismatch");

struct ComplexEmitterData : SimpleEmitterData { // Size: 0x70C
    u32 childFlags;
    u16 fieldFlags;
    u16 fluctuationFlags;
    u16 stripeFlags;
    u8 unusedPad[2];
    u16 childDataOffs;
    u16 fieldDataOffs;
    u16 fluctuationDataOffs;
    u16 stripeDataOffs;
    u32 dataSize;
};

static_assert(sizeof(ComplexEmitterData) == 0x70C, "nw::eft::ComplexEmitterData size mismatch");

struct ChildData { // Size: 0x2FC
    s32 numChildParticles;
    s32 startFramePercent;
    s32 ptclMaxLifespan;
    s32 emissionInterval;
    f32 velInheritRatio;
    f32 allDirVel;
    math::VEC3 diffusionVel;
    f32 ptclPosRandom;
    u8 unusedPad0[8];
    u32 primitiveIdx;
    f32 momentumRandom;
    BlendType blendType;
    MeshType meshType;
    VertexTransformMode vertexTransformMode;
    ZBufATestType zBufATestType;
    TextureRes texture;
    DisplaySideType displaySideType;
    math::VEC3 ptclColor0;
    math::VEC3 ptclColor1;
    u8 unusedPad1[4];
    FragmentComposite primitiveColorBlend;
    FragmentComposite primitiveAlphaBlend;
    f32 ptclAlphaMid;
    f32 ptclAlphaEnd;
    f32 ptclAlphaStart;
    f32 scaleInheritRatio;
    math::VEC2 ptclEmitScale;
    f32 ptclScaleRandom;
    VertexRotationMode rotationMode;
    math::VEC3 ptclRotate;
    math::VEC3 ptclRotateRandom;
    math::VEC3 angularVelocity;
    math::VEC3 angularVelocityRandom;
    f32 rotInertia;
    math::VEC2 rotBasis;
    math::VEC3 gravity;
    s32 alphaAnimTime3;
    s32 alphaAnimTime2;
    s32 scaleAnimTime1;
    math::VEC2 ptclScaleEnd;
    u16 texPtnAnimNum;
    u8 texPtnAnimIdxDiv;
    math::VEC2 UVScaleInit;
    u8 texPtnAnimData[32];
    s16 texPtnAnimPeriod;
    s16 texPtnAnimUsedSize;
    bool texPtnAnimClamp;
    u32 fragmentColorMode;
    u32 fragmentAlphaMode;
    f32 airResist;
    u8 fragmentShaderMode;
    u8 shaderUserSetting;
    bool fragmentSoftEdge;
    bool refractionApplyAlpha;
    math::VEC2 shaderParam1;
    f32 fragmentSoftEdgeFadeDist;
    f32 fragmentSoftEdgeVolume;
    char userMacro1[16];
    char userMacro2[16];
    u32 shaderUserFlag;
    u32 shaderUserSwitchFlag;
    u8 unusedPad2[0x80]; // 27C
};

static_assert(sizeof(ChildData) == 0x2FC, "nw::eft::ChildData size mismatch");

struct FieldRandomData { // Size: 0x10
    s32 period;
    math::VEC3 randomVelScale;
};

static_assert(sizeof(FieldRandomData) == 0x10, "nw::eft::FieldRandomData size mismatch");

struct FieldMagnetData { // Size: 0x14
    f32 strength;
    math::VEC3 pos;
    u32 flags;
};

static_assert(sizeof(FieldMagnetData) == 0x14, "nw::eft::FieldMagnetData size mismatch");

struct FieldSpinData { // Size: 0xC
    s32 angle;
    u32 axis;
    f32 diffusionVel;
};

static_assert(sizeof(FieldSpinData) == 0xC, "nw::eft::FieldSpinData size mismatch");

struct FieldCollisionData { // SizeL 0xC
    u16 collisionType;
    u16 coordSystem;
    f32 y;
    f32 friction;
};

static_assert(sizeof(FieldCollisionData) == 0xC, "nw::eft::FieldCollisionData size mismatch");

struct FieldConvergenceData { // Size: 0x10
    math::VEC3 pos;
    f32 strength;
};

static_assert(sizeof(FieldConvergenceData) == 0x10, "nw::eft::FieldConvergenceData size mismatch");

struct FieldPosAddData { // Size: 0xC
    math::VEC3 posAdd;
};

static_assert(sizeof(FieldPosAddData) == 0xC, "nw::eft::FieldPosAddData size mismatch");

struct FluctuationData {
    f32 amplitude;
    f32 frequency;
    u32 enableRandom;
};

static_assert(sizeof(FluctuationData) == 0xC, "nw::eft::FluctuationData size mismatch");

struct StripeData {
    u32 type;
    u32 crossType;
    u32 connectionType;
    u32 textureType;
    u32 numSliceHistory;
    u32 numDivisions;
    f32 alphaStart;
    f32 alphaEnd;
    u8  unusedPad[8];
    u32 sliceHistInterval;
    f32 sliceInterpolation;
    f32 dirInterpolation;
};

static_assert(sizeof(StripeData) == 0x34, "nw::eft::StripeData size mismatch");

struct EmitterTblData { // Size: 0x8
    u32 dataOffs;
    EmitterData* data;
};

static_assert(sizeof(EmitterTblData) == 8, "nw::eft::EmitterTblData size mismatch");

struct EmitterSetData { // Size: 0x1C
    u32 userData;
    u8  unusedPad[4];
    u32 nameOffs;
    const char* name;
    s32 numEmitter;
    u32 emitterRefOffs;
    EmitterTblData* emitterRef;
};

static_assert(sizeof(EmitterSetData) == 0x1C, "nw::eft::EmitterSetData size mismatch");

struct Header { // Size: 0x40
    char magic[4];
    u32 version;
    s32 numEmitterSet;
    u8  unusedPad0[4];
    u32 strTblOffs;
    u32 textureDataTblOffs;
    u32 textureDataTblSize;
    u32 shaderTblOffs;
    u32 shaderTblSize;
    u32 keyAnimArrayTblOffs;
    u32 keyAnimArrayTblSize;
    u32 primitiveTblOffs;
    u32 primitiveTblSize;
    u8  unusedPad1[12];
};

static_assert(sizeof(Header) == 0x40, "nw::eft::Header size mismatch");

struct PrimitiveAttrib { // Size: 0x10
    u32 count;
    u32 size;
    u32 bufferOffs;
    u32 bufferSize;
};

static_assert(sizeof(PrimitiveAttrib) == 0x10, "nw::eft::PrimitiveAttrib size mismatch");

struct PrimitiveData { // Size: 0x50
    PrimitiveAttrib pos;
    PrimitiveAttrib normal;
    PrimitiveAttrib color;
    PrimitiveAttrib texCoord;
    PrimitiveAttrib index;
};

static_assert(sizeof(PrimitiveData) == 0x50, "nw::eft::PrimitiveData size mismatch");

struct PrimitiveTable { // Size: 0xC
    u32 numPrimitive;
    u32 size;
    u32 primitiveOffs;
};

static_assert(sizeof(PrimitiveTable) == 0xC, "nw::eft::PrimitiveTable size mismatch");

struct KeyFrameAnimArray {
    char magic[4];
    u32 numAnim;
};

struct KeyFrameAnim {
    u32 numKeys;
    u32 interpolation;
    u32 animValIdx;
    u32 loop;
    u32 nextOffs;
    u8  unusedPad[4];
};

struct KeyFrameAnimKey {
    f32 time;
    f32 value;
};

} }
