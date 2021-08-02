#pragma once

#include "dynlibs/gx2/types.h"
#include "nw/math/mtx34.h"
#include "nw/math/vec3.h"
#include "nw/ut/color4f.h"
#include "nw/eft/enum.h"

namespace nw { namespace eft{

struct TextureRes { // Size: 0x114
    u16 mWidth;
    u16 mHeight;
    u32 mTileMode; // GX2TileMode
    u32 mSwizzle;
    u32 mAlignment;
    u32 mPitch;
    u8 mWrapMode;
    u8 mFilterMode;
    u32 mNumMips;
    u32 mCompSel;
    u32 mMipOffset[13];
    f32 mMaxLOD;
    f32 mBiasLOD;
    TextureResFormat mOriginalTexFormat;
    u32 mOriginalTexDataOffs;
    u32 mOriginalTexDataSize;
    TextureResFormat mCafeTexFormat;
    u32 mCafeTexDataSize;
    u32 mCafeTexDataOffs;
    u32 mInitialized;
    GX2Texture mGX2Texture;
};

static_assert(sizeof(TextureRes) == 0x114, "TextureRes size mismatch");

struct EmitterData { // Size: 0x280
    EmitterType mType;
    u32 mFlags;
    u32 mSeed;
    u32 mUserData;
    u8 mUnusedPad0[36];
    CustomActionCallBackID mCallbackID;
    u32 mNameOffs;
    const char* mName;
    TextureRes mTextures[2];
    void* mKeyAnimArray;
    u32 mKeyAnimArrayOffs;
    u32 mKeyAnimArraySize;
    u8 mUnusedPad1[8];
    u32 mPrimitiveIdx;
};

static_assert(sizeof(EmitterData) == 0x280, "EmitterData size mismatch");

struct TextureEmitterData { // Size: 0x78
    bool mHasTexPtnAnim;
    bool mTexPtnAnimRandStart;
    bool mTexPtnAnimClamp;
    u8 mTexPtnAnimIdxDiv;
    u8 mUnusedPad0;
    u8 mTexPtnAnimNum;
    u8 mUnusedPad1[2];
    s16 mTexPtnAnimPeriod;
    s16 mTexPtnAnimUsedSize;
    u8 mTexPtnAnimData[32];
    u8 mUnusedPad2[4];
    math::VEC2 mUVScaleInit;
    u32 mUVShiftAnimMode;
    math::VEC2 mTexIncScroll;
    math::VEC2 mTexInitScroll;
    math::VEC2 mTexInitScrollRandom;
    math::VEC2 mTexIncScale;
    math::VEC2 mTexInitScale;
    math::VEC2 mTexInitScaleRandom;
    f32 mTexIncRotate;
    f32 mTexInitRotate;
    f32 mTexInitRotateRandom;
};

static_assert(sizeof(TextureEmitterData) == 0x78, "TextureEmitterData size mismatch");

struct anim3v4Key { // Size: 0x14
    f32 mStartValue;
    f32 mStartDiff;
    f32 mEndDiff;
    s32 mTime2;
    s32 mTime3;
};

static_assert(sizeof(anim3v4Key) == 0x14, "anim3v4Key size mismatch");

struct SimpleEmitterData : EmitterData { // Size: 0x6F4
    u8 mUnused0[3];
    u8 mTransformGravity;
    u8 mUnused1;
    u8 mNoEmitAtFade;
    u8 mSphereDivTblIdx;
    u8 mArcStartAngleRandom;
    u8 mDisplayParent;
    u8 mEmitSameDistance;
    u8 mSphereUseLatitude;
    VertexRotationMode mRotationMode;
    PtclFollowType mPtclFollowType;
    u32 mFragmentColorMode;
    u32 mFragmentAlphaMode;
    s32 mBitForUnusedFlag;
    DisplaySideType mDisplaySideType;
    f32 mMomentumRandom;
    math::MTX34 mAnimMatrixSRT;
    math::MTX34 mAnimMatrixRT;
    math::VEC3 mEmitterScale;
    math::VEC3 mEmitterRotate;
    math::VEC3 mEmitterTranslate;
    math::VEC3 mEmitterRotateRandom;
    math::VEC3 mEmitterTranslateRandom;
    BlendType mBlendType;
    ZBufATestType mZBufATestType;
    u32 mEmitFunction;
    math::VEC3 mVolumeScale;
    s32 mArcStartAngle;
    u32 mArcLength;
    f32 mVolumeFillRatio;
    f32 mSphereLatitude;
    math::VEC3 mSphereLatitudeDir;
    f32 mLineCenter;
    math::VEC3 mEmissionShapeScale;
    ut::Color4f mEmitterColor0;
    ut::Color4f mEmitterColor1;
    f32 mEmitterAlpha;
    f32 mEmitSameDistanceUnit;
    f32 mEmitSameDistanceMax;
    f32 mEmitSameDistanceMin;
    f32 mEmitSameDistanceThreshold;
    f32 mEmissionRate;
    s32 mStartFrame;
    s32 mEndFrame;
    s32 mEmitInterval;
    s32 mEmitIntervalRandom;
    f32 mAllDirVel;
    f32 mDirVel;
    f32 mDirVelRandom;
    math::VEC3 mDir;
    f32 mDispersionAngle;
    math::VEC3 mDiffusionVel;
    f32 mAirResist;
    math::VEC3 mGravity;
    f32 mYDiffusionVel;
    f32 mPtclPosRandom;
    s32 mPtclMaxLifespan;
    s32 mPtclLifespanRandom;
    MeshType mMeshType;
    VertexTransformMode mVertexTransformMode;
    math::VEC2 mRotBasis;
    f32 mCameraOffset;
    TextureEmitterData mTexAnimParam[2];
    ColorSourceType mPtclColorSrc[2];
    ut::Color4f mPtclColorTbl[2][3];
    s32 mColorTime2[2];
    s32 mColorTime3[2];
    s32 mColorTime4[2];
    s32 mColorNumRepetition[2];
    s32 mColorRandomStart[2];
    f32 mColorScaleFactor;
    anim3v4Key mAlphaAnim;
    FragmentComposite mTextureColorBlend;
    FragmentComposite mPrimitiveColorBlend;
    FragmentComposite mTextureAlphaBlend;
    FragmentComposite mPrimitiveAlphaBlend;
    s32 mScaleAnimTime2;
    s32 mScaleAnimTime3;
    f32 mPtclScaleRandom;
    math::VEC2 mPtclEmitScale;
    math::VEC2 mPtclScaleStart;
    math::VEC2 mPtclScaleStartDiff;
    math::VEC2 mPtclScaleEndDiff;
    math::VEC3 mPtclRotate;
    math::VEC3 mPtclRotateRandom;
    math::VEC3 mAngularVelocity;
    math::VEC3 mAngularVelocityRandom;
    f32 mRotInertia;
    f32 mFadeAlphaStep;
    u8 mFragmentShaderMode;
    u8 mShaderUserSetting;
    bool mFragmentSoftEdge;
    bool mRefractionApplyAlpha;
    math::VEC2 mShaderParam01;
    f32 mFragmentSoftEdgeFadeDist;
    f32 mFragmentSoftEdgeVolume;
    char mUserMacro1[16];
    char mUserMacro2[16];
    u32 mShaderUserFlag;
    u32 mShaderUserSwitchFlag;
    u8 mUnusedPad[0x6F4 - 0x674];
};

static_assert(sizeof(SimpleEmitterData) == 0x6F4, "SimpleEmitterData size mismatch");

struct ComplexEmitterData : SimpleEmitterData { // Size: 0x70C
    u32 mChildFlags;
    u16 mFieldFlags;
    u16 mFluctuationFlags;
    u16 mStripeFlags;
    u8 mUnusedPad[2];
    u16 mChildDataOffs;
    u16 mFieldDataOffs;
    u16 mFluctuationDataOffs;
    u16 mStripeDataOffs;
    u32 mDataSize;
};

static_assert(sizeof(ComplexEmitterData) == 0x70C, "ComplexEmitterData size mismatch");

struct ChildData { // Size: 0x2FC
    s32 mNumChildParticles;
    s32 mStartFramePercent;
    s32 mPtclMaxLifespan;
    s32 mEmissionInterval;
    f32 mVelInheritRatio;
    f32 mAllDirVel;
    math::VEC3 mDiffusionVel;
    f32 mPtclPosRandom;
    u8 mUnusedPad0[8];
    u32 mPrimitiveIdx;
    f32 mMomentumRandom;
    BlendType mBlendType;
    MeshType mMeshType;
    VertexTransformMode mVertexTransformMode;
    ZBufATestType mZBufATestType;
    TextureRes mTexture;
    DisplaySideType mDisplaySideType;
    math::VEC3 mPtclColor0;
    math::VEC3 mPtclColor1;
    u8 mUnusedPad1[4];
    FragmentComposite mPrimitiveColorBlend;
    FragmentComposite mPrimitiveAlphaBlend;
    f32 mPtclAlphaMid;
    f32 mPtclAlphaEnd;
    f32 mPtclAlphaStart;
    f32 mCcaleInheritRatio;
    math::VEC2 mPtclEmitScale;
    f32 mPtclScaleRandom;
    VertexRotationMode mRotationMode;
    math::VEC3 mPtclRotate;
    math::VEC3 mPtclRotateRandom;
    math::VEC3 mAngularVelocity;
    math::VEC3 mAngularVelocityRandom;
    f32 mRotInertia;
    math::VEC2 mRotBasis;
    math::VEC3 mGravity;
    s32 mAlphaAnimTime3;
    s32 mAlphaAnimTime2;
    s32 mScaleAnimTime1;
    math::VEC2 mPtclScaleEnd;
    u16 mTexPtnAnimNum;
    u8 mTexPtnAnimIdxDiv;
    math::VEC2 mUVScaleInit;
    u8 mTexPtnAnimData[32];
    s16 mTexPtnAnimPeriod;
    s16 mTexPtnAnimUsedSize;
    bool mTexPtnAnimClamp;
    u32 mFragmentColorMode;
    u32 mFragmentAlphaMode;
    f32 mAirResist;
    u8 mFragmentShaderMode;
    u8 mShaderUserSetting;
    bool mFragmentSoftEdge;
    bool mRefractionApplyAlpha;
    math::VEC2 mShaderParam01;
    f32 mFragmentSoftEdgeFadeDist;
    f32 mFragmentSoftEdgeVolume;
    char mUserMacro1[16];
    char mUserMacro2[16];
    u32 mShaderUserFlag;
    u32 mShaderUserSwitchFlag;
    u8 mUnusedPad2[0x2FC - 0x27C];
};

static_assert(sizeof(ChildData) == 0x2FC, "ChildData size mismatch");

struct FieldRandomData { // Size: 0x10
    s32 mPeriod;
    math::VEC3 mRandomVelScale;
};

static_assert(sizeof(FieldRandomData) == 0x10, "FieldRandomData size mismatch");

struct FieldMagnetData { // Size: 0x14
    f32 mStrength;
    math::VEC3 mPos;
    u32 mFlags;
};

static_assert(sizeof(FieldMagnetData) == 0x14, "FieldMagnetData size mismatch");

struct FieldSpinData { // Size: 0xC
    s32 mAngle;
    u32 mAxis;
    f32 mDiffusionVel;
};

static_assert(sizeof(FieldSpinData) == 0xC, "FieldSpinData size mismatch");

struct FieldCollisionData { // SizeL 0xC
    u16 mCollisionType;
    u16 mCoordSystem;
    f32 mY;
    f32 mFriction;
};

static_assert(sizeof(FieldCollisionData) == 0xC, "FieldCollisionData size mismatch");

struct FieldConvergenceData { // Size: 0x10
    math::VEC3 mPos;
    f32 mStrength;
};

static_assert(sizeof(FieldConvergenceData) == 0x10, "FieldConvergenceData size mismatch");

struct FieldPosAddData { // Size: 0xC
    math::VEC3 mPosAdd;
};

static_assert(sizeof(FieldPosAddData) == 0xC, "FieldPosAddData size mismatch");

struct FluctuationData {
    f32 mAmplitude;
    f32 mFrequency;
    u32 mEnableRandom;
};

static_assert(sizeof(FluctuationData) == 0xC, "FluctuationData size mismatch");

struct StripeData {
    u32 mType;
    u32 mCrossType;
    u32 mConnectionType;
    u32 mTextureType;
    u32 mNumSliceHistory;
    u32 mNumDivisions;
    f32 mAlphaStart;
    f32 mAlphaEnd;
    u8 mUnusedPad[8];
    u32 mSliceHistInterval;
    f32 mSliceInterpolation;
    f32 mDirInterpolation;
};

static_assert(sizeof(StripeData) == 0x34, "StripeData size mismatch");

struct EmitterTblData { // Size: 0x8
    u32 mDataOffs;
    EmitterData* mData;
};

static_assert(sizeof(EmitterTblData) == 8, "EmitterTblData size mismatch");

struct EmitterSetData { // Size: 0x1C
    u32 mUserData;
    u8 mUnusedPad[4];
    u32 mNameOffs;
    const char* mName;
    s32 mNumEmitter;
    u32 mEmitterRefOffs;
    EmitterTblData* mEmitterRef;
};

static_assert(sizeof(EmitterSetData) == 0x1C, "EmitterSetData size mismatch");

struct Header { // Size: 0x40
    char mMagic[4];
    u32 mVersion;
    s32 mNumEmitterSet;
    u8 mUnusedPad0[4];
    u32 mStrTblOffs;
    u32 mTextureDataTblOffs;
    u32 mTextureDataTblSize;
    u32 mShaderTblOffs;
    u32 mShaderTblSize;
    u32 mKeyAnimArrayTblOffs;
    u32 mKeyAnimArrayTblSize;
    u32 mPrimitiveTblOffs;
    u32 mPrimitiveTblSize;
    u8 mUnusedPad1[12];
};

static_assert(sizeof(Header) == 0x40, "Header size mismatch");

struct PrimitiveAttrib { // Size: 0x10
    u32 mCount;
    u32 mSize;
    u32 mBufferOffs;
    u32 mBufferSize;
};

static_assert(sizeof(PrimitiveAttrib) == 0x10, "PrimitiveAttrib size mismatch");

struct PrimitiveData { // Size: 0x50
    PrimitiveAttrib mPos;
    PrimitiveAttrib mNormal;
    PrimitiveAttrib mColor;
    PrimitiveAttrib mTexCoord;
    PrimitiveAttrib mIndex;
};

static_assert(sizeof(PrimitiveData) == 0x50, "PrimitiveData size mismatch");

struct PrimitiveTable { // Size: 0xC
    u32 mNumPrimitive;
    u32 mSize;
    u32 mPrimitiveOffs;
};

static_assert(sizeof(PrimitiveTable) == 0xC, "PrimitiveTable size mismatch");

struct KeyFrameAnimArray {
    char mMagic[4];
    u32 mNumAnim;
};

struct KeyFrameAnim {
    u32 mNumKeys;
    u32 mInterpolation;
    u32 mAnimValIdx;
    u32 mLoop;
    u32 mNextOffs;
    u8 mUnusedPad[4];
};

struct KeyFrameAnimKey {
    f32 mTime;
    f32 mValue;
};

} }
