#pragma once

#include "nw/eft/cafewrapper.h"
#include "nw/eft/resdata.h"

#include <cstring>

namespace nw { namespace eft {

struct VertexShaderKey { // Size: 0x20
    void InitializeSimple(const SimpleEmitterData* data) {
        this->mTransformMode = data->mVertexTransformMode;
        this->mRotationMode = (u8)(data->mRotationMode != VertexRotationModeNone);
        this->mShaderUserSetting = data->mShaderUserSetting;
        this->mShaderUserFlag = data->mShaderUserFlag;
        this->mShaderUserSwitchFlag = data->mShaderUserSwitchFlag;
        this->mStripeType = 0;
        //this->mStripeEmitterCoord = false; <-- Nintendo forgot to do this
        this->mIsPrimitive = data->mMeshType == MeshTypePrimitive;
    }

    void InitializeComplex(const ComplexEmitterData* cdata) {
        InitializeSimple(cdata);

        if (cdata->mVertexTransformMode == VertexTransformModeStripe || cdata->mVertexTransformMode == VertexTransformModeComplexStripe) {
            this->mStripeType = reinterpret_cast<const StripeData*>((u32)cdata + cdata->mStripeDataOffs)->mType;

            if (cdata->mStripeFlags & 1)
                mStripeEmitterCoord = true;
            else
                mStripeEmitterCoord = false;
        }
        
        else
            this->mStripeEmitterCoord = false;
    }

    void Initialize(const SimpleEmitterData* data) {
        if (data->mType == EmitterTypeComplex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        this->mShaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        if (data->mType == EmitterTypeComplex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(this->mShaderUserMacro, userMacro);
        else
            this->mShaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data) {
        this->mTransformMode = data->mVertexTransformMode;
        this->mRotationMode = (u8)(data->mRotationMode != VertexRotationModeNone);
        this->mShaderUserSetting = data->mShaderUserSetting;
        this->mShaderUserFlag = data->mShaderUserFlag;
        this->mShaderUserSwitchFlag = data->mShaderUserSwitchFlag;
        this->mStripeType = 3;
        //this->mStripeEmitterCoord = false; <-- Nintendo forgot to do this
        this->mIsPrimitive = data->mMeshType == MeshTypePrimitive;
    }

    void Initialize(const ChildData* data) {
        InitializeChild(data);
        this->mShaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, const char* userMacro) {
        InitializeChild(data);

        if (userMacro != NULL)
            strcpy(mShaderUserMacro, userMacro);
        else
            this->mShaderUserMacro[0] = '\0';
    }

    bool operator==(const VertexShaderKey& other) {
        return (this->mTransformMode           == other.mTransformMode
                && this->mRotationMode         == other.mRotationMode
                && this->mShaderUserSetting    == other.mShaderUserSetting
                && this->mShaderUserFlag       == other.mShaderUserFlag
                && this->mShaderUserSwitchFlag == other.mShaderUserSwitchFlag
                && this->mStripeType           == other.mStripeType
                && this->mStripeEmitterCoord   == other.mStripeEmitterCoord
                && this->mIsPrimitive          == other.mIsPrimitive
                && strcmp(this->mShaderUserMacro, other.mShaderUserMacro) == 0);
    }

    u8 mTransformMode;
    u8 mRotationMode;
    u8 mShaderUserSetting;
    u8 mStripeType;
    bool mStripeEmitterCoord;
    bool mIsPrimitive;
    u32 mShaderUserFlag;
    u32 mShaderUserSwitchFlag;
    char mShaderUserMacro[16];
};

static_assert(sizeof(VertexShaderKey) == 0x20, "VertexShaderKey size mismatch");

struct FragmentShaderKey {
    void InitializeSimple(const SimpleEmitterData* data) {
        this->mShaderMode           = data->mFragmentShaderMode;
        this->mSoftEdge             = data->mFragmentSoftEdge;
        this->mTextureMode          = (data->mTextures[1].mWidth != 0 && data->mTextures[1].mHeight != 0) ? 1 : 0;
        this->mColorMode            = data->mFragmentColorMode;
        this->mAlphaMode            = data->mFragmentAlphaMode;
        this->mShaderUserSetting    = data->mShaderUserSetting;
        this->mShaderUserFlag       = data->mShaderUserFlag;
        this->mShaderUserSwitchFlag = data->mShaderUserSwitchFlag;
        this->mRefractionApplyAlpha = data->mRefractionApplyAlpha;
        this->mIsPrimitive          = data->mMeshType == MeshTypePrimitive;

        switch (data->mTextureColorBlend) {
            case FragmentCompositeMul: this->mTextureColorBlend = 0; break;
            case FragmentCompositeAdd: this->mTextureColorBlend = 1; break;
            case FragmentCompositeSub: this->mTextureColorBlend = 2; break;
        }

        switch (data->mTextureAlphaBlend) {
            case FragmentCompositeMul: this->mTextureAlphaBlend = 0; break;
            case FragmentCompositeAdd: this->mTextureAlphaBlend = 1; break;
            case FragmentCompositeSub: this->mTextureAlphaBlend = 2; break;
        }

        switch (data->mPrimitiveColorBlend) {
            case FragmentCompositeMul: this->mPrimitiveColorBlend = 0; break;
            case FragmentCompositeAdd: this->mPrimitiveColorBlend = 1; break;
            case FragmentCompositeSub: this->mPrimitiveColorBlend = 2; break;
        }

        switch (data->mPrimitiveAlphaBlend) {
            case FragmentCompositeMul: this->mPrimitiveAlphaBlend = 0; break;
            case FragmentCompositeAdd: this->mPrimitiveAlphaBlend = 1; break;
            case FragmentCompositeSub: this->mPrimitiveAlphaBlend = 2; break;
        }

        this->mTexture0ColorSrc  = data->mFlags >> 11 & 1;
        this->mTexture1ColorSrc  = data->mFlags >> 12 & 1;
        this->mPrimitiveColorSrc = data->mFlags >> 13 & 1;
        this->mTexture0AlphaSrc  = data->mFlags >> 14 & 1;
        this->mTexture1AlphaSrc  = data->mFlags >> 15 & 1;
        this->mPrimitiveAlphaSrc = data->mFlags >> 16 & 1;

        this->mUnused0 = 0;
        this->mUnused1 = 0;
    }

    void Initialize(const SimpleEmitterData* data) {
        InitializeSimple(data);
        this->mShaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(this->mShaderUserMacro, userMacro);
        else
            this->mShaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data, u32 childFlags) {
        this->mShaderMode           = data->mFragmentShaderMode;
        this->mSoftEdge             = data->mFragmentSoftEdge;
        this->mTextureMode          = 0;
        this->mColorMode            = data->mFragmentColorMode;
        this->mAlphaMode            = data->mFragmentAlphaMode;
        this->mShaderUserSetting    = data->mShaderUserSetting;
        this->mShaderUserFlag       = data->mShaderUserFlag;
        this->mShaderUserSwitchFlag = data->mShaderUserSwitchFlag;
        this->mRefractionApplyAlpha = data->mRefractionApplyAlpha;
        this->mTextureColorBlend    = 0;
        this->mTextureAlphaBlend    = 0;
        this->mIsPrimitive          = data->mMeshType == MeshTypePrimitive;

        switch (data->mPrimitiveColorBlend) {
            case FragmentCompositeMul: this->mPrimitiveColorBlend = 0; break;
            case FragmentCompositeAdd: this->mPrimitiveColorBlend = 1; break;
            case FragmentCompositeSub: this->mPrimitiveColorBlend = 2; break;
        }

        switch (data->mPrimitiveAlphaBlend) {
            case FragmentCompositeMul: this->mPrimitiveAlphaBlend = 0; break;
            case FragmentCompositeAdd: this->mPrimitiveAlphaBlend = 1; break;
            case FragmentCompositeSub: this->mPrimitiveAlphaBlend = 2; break;
        }

        this->mTexture0ColorSrc  = childFlags >> 17 & 1;
        this->mTexture1ColorSrc  = 0;
        this->mPrimitiveColorSrc = childFlags >> 18 & 1;
        this->mTexture0AlphaSrc  = childFlags >> 19 & 1;
        this->mTexture1AlphaSrc  = 0;
        this->mPrimitiveAlphaSrc = childFlags >> 20 & 1;

        this->mUnused0 = 0;
        this->mUnused1 = 0;
    }

    void Initialize(const ChildData* data, u32 childFlags) {
        InitializeChild(data, childFlags);
        this->mShaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, u32 childFlags, const char* userMacro) {
        InitializeChild(data, childFlags);

        if (userMacro != NULL)
            strcpy(this->mShaderUserMacro, userMacro);
        else
            this->mShaderUserMacro[0] = '\0';
    }

    bool operator==(const FragmentShaderKey& other) {
        return (this->mShaderMode                == other.mShaderMode
                && this->mSoftEdge               == other.mSoftEdge
                && this->mTextureMode            == other.mTextureMode
                && this->mColorMode              == other.mColorMode
                && this->mAlphaMode              == other.mAlphaMode
                && this->mShaderUserSetting      == other.mShaderUserSetting
                && this->mIsPrimitive            == other.mIsPrimitive
                && this->mTextureColorBlend      == other.mTextureColorBlend
                && this->mTextureAlphaBlend      == other.mTextureAlphaBlend
                && this->mPrimitiveColorBlend    == other.mPrimitiveColorBlend
                && this->mPrimitiveAlphaBlend    == other.mPrimitiveAlphaBlend
                && this->mTexture0ColorSrc       == other.mTexture0ColorSrc
                && this->mTexture1ColorSrc       == other.mTexture1ColorSrc
                && this->mPrimitiveColorSrc      == other.mPrimitiveColorSrc
                && this->mTexture0AlphaSrc       == other.mTexture0AlphaSrc
                && this->mTexture1AlphaSrc       == other.mTexture1AlphaSrc
                && this->mPrimitiveAlphaSrc      == other.mPrimitiveAlphaSrc
                && this->mRefractionApplyAlpha   == other.mRefractionApplyAlpha
                && this->mShaderUserFlag         == other.mShaderUserFlag
                && this->mShaderUserSwitchFlag   == other.mShaderUserSwitchFlag
                && strcmp(this->mShaderUserMacro,   other.mShaderUserMacro) == 0);
    }

    u8 mShaderMode;
    bool mSoftEdge;
    u8 mTextureMode;
    u8 mColorMode;
    u8 mAlphaMode;
    u8 mShaderUserSetting;
    bool mIsPrimitive;
    u8 mTextureColorBlend;
    u8 mTextureAlphaBlend;
    u8 mPrimitiveColorBlend;
    u8 mPrimitiveAlphaBlend;
    u8 mTexture0ColorSrc;
    u8 mTexture1ColorSrc;
    u8 mPrimitiveColorSrc;
    u8 mTexture0AlphaSrc;
    u8 mTexture1AlphaSrc;
    u8 mPrimitiveAlphaSrc;
    u8 mRefractionApplyAlpha;
    u16 mUnused0;
    u32 mShaderUserFlag;
    u32 mShaderUserSwitchFlag;
    char mShaderUserMacro[16];
    u16 mUnused1;
    //u8 pad[2];
};

static_assert(sizeof(FragmentShaderKey) == 0x30, "FragmentShaderKey size mismatch");

struct GeometryShaderKey { // Size: 0x4
    u8 mUnused[4];
};

static_assert(sizeof(GeometryShaderKey) == 4, "GeometryShaderKey size mismatch");

struct ShaderTable { // Size: 0x10
    u32 mNumShaderProg;
    u32 mSize;
    u32 mShaderSrcOffs;
    u32 mShaderProgOffs;
};

static_assert(sizeof(ShaderTable) == 0x10, "ShaderTable size mismatch");

struct ShaderProgram { // Size: 0x5C
    VertexShaderKey mVertexShaderKey;
    FragmentShaderKey mFragmentShaderKey;
    GeometryShaderKey mGeometryShaderKey; // ?
    u32 mBinSize;
    u32 mBinOffs;
};

static_assert(sizeof(ShaderProgram) == 0x5C, "ShaderProgram size mismatch");

struct VertexTextureLocation { // Size: 0x4
    u32 mLocation;
};

static_assert(sizeof(VertexTextureLocation) == 4, "VertexTextureLocation size mismatch");

struct FragmentTextureLocation { // Size: 0x4
    u32 mLocation;
};

static_assert(sizeof(FragmentTextureLocation) == 4, "FragmentTextureLocation size mismatch");

class Heap;

class ParticleShader { // Size: 0x61C
public:
    ParticleShader();
    
    void Finalize(Heap* heap);
    void InitializeVertexShaderLocation();
    void InitializeFragmentShaderLocation();
    void InitializeAttribute();
    void InitializeStripeVertexShaderLocation();
    void InitializeStripeAttribute();
    bool SetupShaderResource(Heap* heap, void* binary, u32 binarySize);
    void Bind();
    void EnableInstanced();
    void DisableInstanced();

    u8 mDisplayList[512];
    u32 mDisplayListSize;
    Shader mShader;
    VertexShaderKey mVertexShaderKey;
    FragmentShaderKey mFragmentShaderKey;
    GeometryShaderKey mGeometryShaderKey; // ?
    u32 mAttrPosBuffer;
    u32 mAttrNormalBuffer;
    u32 mAttrColorBuffer;
    u32 mAttrTexCoordBuffer;
    u32 mUnusedAttrBuffer;
    u32 mAttrIndexBuffer;
    u32 mAttrOuterBuffer;
    u32 mAttrDirBuffer;
    FragmentTextureLocation mFragmentSamplerLocations[2];
    union {
        FragmentTextureLocation mFragmentSamplerLocations2[2];
        struct {
            FragmentTextureLocation mFragmentDepthBufferSamplerLocation;
            FragmentTextureLocation mFragmentFrameBufferSamplerLocation;
        };
    };
    u32 mAttrSclBuffer;
    u32 mAttrTexAnimBuffer;
    u32 mAttrSubTexAnimBuffer;
    u32 mAttrWldPosBuffer;
    u32 mAttrWldPosDfBuffer;
    u32 mAttrColor0Buffer;
    u32 mAttrColor1Buffer;
    u32 mAttrRotBuffer;
    u32 mAttrEmMat0Buffer;
    u32 mAttrEmMat1Buffer;
    u32 mAttrEmMat2Buffer;
    UniformBlock mVertexViewUniformBlock;
    UniformBlock mFragmentViewUniformBlock;
    UniformBlock mVertexEmitterStaticUniformBlock;
    UniformBlock mVertexEmitterDynamicUniformBlock;
    UniformBlock mUnusedUniformBlock; // ?
    UniformBlock mFragmentEmitterStaticUniformBlock;
    UniformBlock mStripeUniformBlock;
    UniformBlock mVertexUserUniformBlocks[2];
    UniformBlock mFragmentUserUniformBlocks[2];
    VertexTextureLocation mVertexUserSamplerLocations[8];
    FragmentTextureLocation mFragmentUserSamplerLocations[8];
};

static_assert(sizeof(ParticleShader) == 0x61C, "ParticleShader size mismatch");

} }
