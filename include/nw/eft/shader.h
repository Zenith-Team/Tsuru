#pragma once

#include <nw/eft/cafewrapper.h>
#include <nw/eft/resdata.h>

#include <cstring>

namespace nw { namespace eft {

struct VertexShaderKey { // Size: 0x20
    void InitializeSimple(const SimpleEmitterData* data) {
        this->transformMode = data->vertexTransformMode;
        this->rotationMode = (u8)(data->rotationMode != VertexRotationMode_None);
        this->shaderUserSetting = data->shaderUserSetting;
        this->shaderUserFlag = data->shaderUserFlag;
        this->shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        this->stripeType = 0;
        //this->stripeEmitterCoord = false; <-- Nintendo forgot to do this
        this->isPrimitive = data->meshType == MeshType_Primitive;
    }

    void InitializeComplex(const ComplexEmitterData* cdata) {
        InitializeSimple(cdata);

        if (cdata->vertexTransformMode == VertexTransformMode_Stripe || cdata->vertexTransformMode == VertexTransformMode_ComplexStripe) {
            this->stripeType = reinterpret_cast<const StripeData*>((u32)cdata + cdata->stripeDataOffs)->type;

            if (cdata->stripeFlags & 1)
                stripeEmitterCoord = true;
            else
                stripeEmitterCoord = false;
        }

        else
            this->stripeEmitterCoord = false;
    }

    void Initialize(const SimpleEmitterData* data) {
        if (data->type == EmitterType_Complex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        this->shaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        if (data->type == EmitterType_Complex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(this->shaderUserMacro, userMacro);
        else
            this->shaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data) {
        this->transformMode = data->vertexTransformMode;
        this->rotationMode = (u8)(data->rotationMode != VertexRotationMode_None);
        this->shaderUserSetting = data->shaderUserSetting;
        this->shaderUserFlag = data->shaderUserFlag;
        this->shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        this->stripeType = 3;
        //this->stripeEmitterCoord = false; <-- Nintendo forgot to do this
        this->isPrimitive = data->meshType == MeshType_Primitive;
    }

    void Initialize(const ChildData* data) {
        InitializeChild(data);
        this->shaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, const char* userMacro) {
        InitializeChild(data);

        if (userMacro != NULL)
            strcpy(shaderUserMacro, userMacro);
        else
            this->shaderUserMacro[0] = '\0';
    }

    bool operator==(const VertexShaderKey& other) {
        return (this->transformMode           == other.transformMode
                && this->rotationMode         == other.rotationMode
                && this->shaderUserSetting    == other.shaderUserSetting
                && this->shaderUserFlag       == other.shaderUserFlag
                && this->shaderUserSwitchFlag == other.shaderUserSwitchFlag
                && this->stripeType           == other.stripeType
                && this->stripeEmitterCoord   == other.stripeEmitterCoord
                && this->isPrimitive          == other.isPrimitive
                && strcmp(this->shaderUserMacro, other.shaderUserMacro) == 0);
    }

    u8 transformMode;
    u8 rotationMode;
    u8 shaderUserSetting;
    u8 stripeType;
    bool stripeEmitterCoord;
    bool isPrimitive;
    u32 shaderUserFlag;
    u32 shaderUserSwitchFlag;
    char shaderUserMacro[16];
};

static_assert(sizeof(VertexShaderKey) == 0x20, "nw::eft::VertexShaderKey size mismatch");

struct FragmentShaderKey {
    void InitializeSimple(const SimpleEmitterData* data) {
        this->shaderMode           = data->fragmentShaderMode;
        this->softEdge             = data->fragmentSoftEdge;
        this->textureMode          = (data->textures[1].width != 0 && data->textures[1].height != 0) ? 1 : 0;
        this->colorMode            = data->fragmentColorMode;
        this->alphaMode            = data->fragmentAlphaMode;
        this->shaderUserSetting    = data->shaderUserSetting;
        this->shaderUserFlag       = data->shaderUserFlag;
        this->shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        this->refractionApplyAlpha = data->refractionApplyAlpha;
        this->isPrimitive          = data->meshType == MeshType_Primitive;

        switch (data->textureColorBlend) {
            case FragmentComposite_Mul: this->textureColorBlend = 0; break;
            case FragmentComposite_Add: this->textureColorBlend = 1; break;
            case FragmentComposite_Sub: this->textureColorBlend = 2; break;
        }

        switch (data->textureAlphaBlend) {
            case FragmentComposite_Mul: this->textureAlphaBlend = 0; break;
            case FragmentComposite_Add: this->textureAlphaBlend = 1; break;
            case FragmentComposite_Sub: this->textureAlphaBlend = 2; break;
        }

        switch (data->primitiveColorBlend) {
            case FragmentComposite_Mul: this->primitiveColorBlend = 0; break;
            case FragmentComposite_Add: this->primitiveColorBlend = 1; break;
            case FragmentComposite_Sub: this->primitiveColorBlend = 2; break;
        }

        switch (data->primitiveAlphaBlend) {
            case FragmentComposite_Mul: this->primitiveAlphaBlend = 0; break;
            case FragmentComposite_Add: this->primitiveAlphaBlend = 1; break;
            case FragmentComposite_Sub: this->primitiveAlphaBlend = 2; break;
        }

        this->texture0ColorSrc  = data->flags >> 11 & 1;
        this->texture1ColorSrc  = data->flags >> 12 & 1;
        this->primitiveColorSrc = data->flags >> 13 & 1;
        this->texture0AlphaSrc  = data->flags >> 14 & 1;
        this->texture1AlphaSrc  = data->flags >> 15 & 1;
        this->primitiveAlphaSrc = data->flags >> 16 & 1;

        this->unused0 = 0;
        this->unused1 = 0;
    }

    void Initialize(const SimpleEmitterData* data) {
        InitializeSimple(data);
        this->shaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(this->shaderUserMacro, userMacro);
        else
            this->shaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data, u32 childFlags) {
        this->shaderMode           = data->fragmentShaderMode;
        this->softEdge             = data->fragmentSoftEdge;
        this->textureMode          = 0;
        this->colorMode            = data->fragmentColorMode;
        this->alphaMode            = data->fragmentAlphaMode;
        this->shaderUserSetting    = data->shaderUserSetting;
        this->shaderUserFlag       = data->shaderUserFlag;
        this->shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        this->refractionApplyAlpha = data->refractionApplyAlpha;
        this->textureColorBlend    = 0;
        this->textureAlphaBlend    = 0;
        this->isPrimitive          = data->meshType == MeshType_Primitive;

        switch (data->primitiveColorBlend) {
            case FragmentComposite_Mul: this->primitiveColorBlend = 0; break;
            case FragmentComposite_Add: this->primitiveColorBlend = 1; break;
            case FragmentComposite_Sub: this->primitiveColorBlend = 2; break;
        }

        switch (data->primitiveAlphaBlend) {
            case FragmentComposite_Mul: this->primitiveAlphaBlend = 0; break;
            case FragmentComposite_Add: this->primitiveAlphaBlend = 1; break;
            case FragmentComposite_Sub: this->primitiveAlphaBlend = 2; break;
        }

        this->texture0ColorSrc  = childFlags >> 17 & 1;
        this->texture1ColorSrc  = 0;
        this->primitiveColorSrc = childFlags >> 18 & 1;
        this->texture0AlphaSrc  = childFlags >> 19 & 1;
        this->texture1AlphaSrc  = 0;
        this->primitiveAlphaSrc = childFlags >> 20 & 1;

        this->unused0 = 0;
        this->unused1 = 0;
    }

    void Initialize(const ChildData* data, u32 childFlags) {
        InitializeChild(data, childFlags);
        this->shaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, u32 childFlags, const char* userMacro) {
        InitializeChild(data, childFlags);

        if (userMacro != NULL)
            strcpy(this->shaderUserMacro, userMacro);
        else
            this->shaderUserMacro[0] = '\0';
    }

    bool operator==(const FragmentShaderKey& other) {
        return (this->shaderMode                == other.shaderMode
                && this->softEdge               == other.softEdge
                && this->textureMode            == other.textureMode
                && this->colorMode              == other.colorMode
                && this->alphaMode              == other.alphaMode
                && this->shaderUserSetting      == other.shaderUserSetting
                && this->isPrimitive            == other.isPrimitive
                && this->textureColorBlend      == other.textureColorBlend
                && this->textureAlphaBlend      == other.textureAlphaBlend
                && this->primitiveColorBlend    == other.primitiveColorBlend
                && this->primitiveAlphaBlend    == other.primitiveAlphaBlend
                && this->texture0ColorSrc       == other.texture0ColorSrc
                && this->texture1ColorSrc       == other.texture1ColorSrc
                && this->primitiveColorSrc      == other.primitiveColorSrc
                && this->texture0AlphaSrc       == other.texture0AlphaSrc
                && this->texture1AlphaSrc       == other.texture1AlphaSrc
                && this->primitiveAlphaSrc      == other.primitiveAlphaSrc
                && this->refractionApplyAlpha   == other.refractionApplyAlpha
                && this->shaderUserFlag         == other.shaderUserFlag
                && this->shaderUserSwitchFlag   == other.shaderUserSwitchFlag
                && strcmp(this->shaderUserMacro,   other.shaderUserMacro) == 0);
    }

    u8 shaderMode;
    bool softEdge;
    u8 textureMode;
    u8 colorMode;
    u8 alphaMode;
    u8 shaderUserSetting;
    bool isPrimitive;
    u8 textureColorBlend;
    u8 textureAlphaBlend;
    u8 primitiveColorBlend;
    u8 primitiveAlphaBlend;
    u8 texture0ColorSrc;
    u8 texture1ColorSrc;
    u8 primitiveColorSrc;
    u8 texture0AlphaSrc;
    u8 texture1AlphaSrc;
    u8 primitiveAlphaSrc;
    u8 refractionApplyAlpha;
    u16 unused0;
    u32 shaderUserFlag;
    u32 shaderUserSwitchFlag;
    char shaderUserMacro[16];
    u16 unused1;
    //u8 pad[2];
};

static_assert(sizeof(FragmentShaderKey) == 0x30, "nw::eft::FragmentShaderKey size mismatch");

struct GeometryShaderKey { // Size: 0x4
    u8 unused[4];
};

static_assert(sizeof(GeometryShaderKey) == 4, "nw::eft::GeometryShaderKey size mismatch");

struct ShaderTable { // Size: 0x10
    u32 numShaderProg;
    u32 size;
    u32 shaderSrcOffs;
    u32 shaderProgOffs;
};

static_assert(sizeof(ShaderTable) == 0x10, "nw::eft::ShaderTable size mismatch");

struct ShaderProgram { // Size: 0x5C
    VertexShaderKey vertexShaderKey;
    FragmentShaderKey fragmentShaderKey;
    GeometryShaderKey geometryShaderKey; // ?
    u32 binSize;
    u32 binOffs;
};

static_assert(sizeof(ShaderProgram) == 0x5C, "nw::eft::ShaderProgram size mismatch");

struct VertexTextureLocation { // Size: 0x4
    u32 location;
};

static_assert(sizeof(VertexTextureLocation) == 4, "nw::eft::VertexTextureLocation size mismatch");

struct FragmentTextureLocation { // Size: 0x4
    u32 location;
};

static_assert(sizeof(FragmentTextureLocation) == 4, "nw::eft::FragmentTextureLocation size mismatch");

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

    u8 displayList[512];
    u32 displayListSize;
    Shader shader;
    VertexShaderKey vertexShaderKey;
    FragmentShaderKey fragmentShaderKey;
    GeometryShaderKey geometryShaderKey; // ?
    u32 attrPosBuffer;
    u32 attrNormalBuffer;
    u32 attrColorBuffer;
    u32 attrTexCoordBuffer;
    u32 unusedAttrBuffer;
    u32 attrIndexBuffer;
    u32 attrOuterBuffer;
    u32 attrDirBuffer;
    FragmentTextureLocation fragmentSamplerLocations[2];
    union {
        FragmentTextureLocation fragmentSamplerLocations2[2];
        struct {
            FragmentTextureLocation fragmentDepthBufferSamplerLocation;
            FragmentTextureLocation fragmentFrameBufferSamplerLocation;
        };
    };
    u32 attrSclBuffer;
    u32 attrTexAnimBuffer;
    u32 attrSubTexAnimBuffer;
    u32 attrWldPosBuffer;
    u32 attrWldPosDfBuffer;
    u32 attrColor0Buffer;
    u32 attrColor1Buffer;
    u32 attrRotBuffer;
    u32 attrEmMat0Buffer;
    u32 attrEmMat1Buffer;
    u32 attrEmMat2Buffer;
    UniformBlock vertexViewUniformBlock;
    UniformBlock fragmentViewUniformBlock;
    UniformBlock vertexEmitterStaticUniformBlock;
    UniformBlock vertexEmitterDynamicUniformBlock;
    UniformBlock unusedUniformBlock; // ?
    UniformBlock fragmentEmitterStaticUniformBlock;
    UniformBlock stripeUniformBlock;
    UniformBlock vertexUserUniformBlocks[2];
    UniformBlock fragmentUserUniformBlocks[2];
    VertexTextureLocation vertexUserSamplerLocations[8];
    FragmentTextureLocation fragmentUserSamplerLocations[8];
};

static_assert(sizeof(ParticleShader) == 0x61C, "nw::eft::ParticleShader size mismatch");

} }
