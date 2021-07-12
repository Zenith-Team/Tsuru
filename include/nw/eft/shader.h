#ifndef EFT_SHADER_H_
#define EFT_SHADER_H_

#include "nw/eft/cafewrapper.h"
#include "nw/eft/resdata.h"
#include "nw/eft/uniformblock.h"

#include <cstring>

namespace nw { namespace eft {

struct VertexShaderKey {
    void InitializeSimple(const SimpleEmitterData* data) {
        transformMode = data->vertexTransformMode;
        rotationMode = (u8)(data->rotationMode != VertexRotationMode_None);
        shaderUserSetting = data->shaderUserSetting;
        shaderUserFlag = data->shaderUserFlag;
        shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        stripeType = 0;
        //stripeEmitterCoord = false; <-- Nintendo forgot to do this
        isPrimitive = data->meshType == MeshType_Primitive;
    }

    void InitializeComplex(const ComplexEmitterData* cdata) {
        InitializeSimple(cdata);

        if (cdata->vertexTransformMode == VertexTransformMode_Stripe || cdata->vertexTransformMode == VertexTransformMode_Complex_Stripe) {
            stripeType = reinterpret_cast<const StripeData*>((u32)cdata + cdata->stripeDataOffs)->type;
            if (cdata->stripeFlags & 1) stripeEmitterCoord = true;
            else                        stripeEmitterCoord = false;
        }
        
        else {
            stripeEmitterCoord = false;
        }
    }

    void Initialize(const SimpleEmitterData* data) {
        if (data->type == EmitterType_Complex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        shaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        if (data->type == EmitterType_Complex)
            InitializeComplex(static_cast<const ComplexEmitterData*>(data));
        else
            InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(shaderUserMacro, userMacro);
        else
            shaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data) {
        transformMode = data->vertexTransformMode;
        rotationMode = (u8)(data->rotationMode != VertexRotationMode_None);
        shaderUserSetting = data->shaderUserSetting;
        shaderUserFlag = data->shaderUserFlag;
        shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        stripeType = 3;
        //stripeEmitterCoord = false; <-- Nintendo forgot to do this
        isPrimitive = data->meshType == MeshType_Primitive;
    }

    void Initialize(const ChildData* data) {
        InitializeChild(data);
        shaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, const char* userMacro) {
        InitializeChild(data);

        if (userMacro != NULL)
            strcpy(shaderUserMacro, userMacro);
        else
            shaderUserMacro[0] = '\0';
    }

    bool operator==(const VertexShaderKey& other) {
        return (transformMode           == other.transformMode
                && rotationMode         == other.rotationMode
                && shaderUserSetting    == other.shaderUserSetting
                && shaderUserFlag       == other.shaderUserFlag
                && shaderUserSwitchFlag == other.shaderUserSwitchFlag
                && stripeType           == other.stripeType
                && stripeEmitterCoord   == other.stripeEmitterCoord
                && isPrimitive          == other.isPrimitive
                && strcmp(shaderUserMacro, other.shaderUserMacro) == 0);
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
static_assert(sizeof(VertexShaderKey) == 0x20, "VertexShaderKey size mismatch");

struct FragmentShaderKey {
    void InitializeSimple(const SimpleEmitterData* data) {
        shaderMode = data->fragmentShaderMode;
        softEdge = data->fragmentSoftEdge;
        textureMode = (data->textures[1].width != 0 && data->textures[1].height != 0) ? 1 : 0;
        colorMode = data->fragmentColorMode;
        alphaMode = data->fragmentAlphaMode;
        shaderUserSetting = data->shaderUserSetting;
        shaderUserFlag = data->shaderUserFlag;
        shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        refractionApplyAlpha = data->refractionApplyAlpha;
        isPrimitive = data->meshType == MeshType_Primitive;

        switch (data->textureColorBlend) {
            case FragmentComposite_Mul: textureColorBlend = 0; break;
            case FragmentComposite_Add: textureColorBlend = 1; break;
            case FragmentComposite_Sub: textureColorBlend = 2; break;
        }

        switch (data->textureAlphaBlend) {
            case FragmentComposite_Mul: textureAlphaBlend = 0; break;
            case FragmentComposite_Add: textureAlphaBlend = 1; break;
            case FragmentComposite_Sub: textureAlphaBlend = 2; break;
        }

        switch (data->primitiveColorBlend) {
            case FragmentComposite_Mul: primitiveColorBlend = 0; break;
            case FragmentComposite_Add: primitiveColorBlend = 1; break;
            case FragmentComposite_Sub: primitiveColorBlend = 2; break;
        }

        switch (data->primitiveAlphaBlend) {
            case FragmentComposite_Mul: primitiveAlphaBlend = 0; break;
            case FragmentComposite_Add: primitiveAlphaBlend = 1; break;
            case FragmentComposite_Sub: primitiveAlphaBlend = 2; break;
        }

        texture0ColorSrc  = data->flags >> 11 & 1;
        texture1ColorSrc  = data->flags >> 12 & 1;
        primitiveColorSrc = data->flags >> 13 & 1;
        texture0AlphaSrc  = data->flags >> 14 & 1;
        texture1AlphaSrc  = data->flags >> 15 & 1;
        primitiveAlphaSrc = data->flags >> 16 & 1;

        _unused0 = 0;
        _unused1 = 0;
    }

    void Initialize(const SimpleEmitterData* data) {
        InitializeSimple(data);
        shaderUserMacro[0] = '\0';
    }

    void Initialize(const SimpleEmitterData* data, const char* userMacro) {
        InitializeSimple(data);

        if (userMacro != NULL)
            strcpy(shaderUserMacro, userMacro);
        else
            shaderUserMacro[0] = '\0';
    }

    void InitializeChild(const ChildData* data, u32 childFlags) {
        shaderMode = data->fragmentShaderMode;
        softEdge = data->fragmentSoftEdge;
        textureMode = 0;
        colorMode = data->fragmentColorMode;
        alphaMode = data->fragmentAlphaMode;
        shaderUserSetting = data->shaderUserSetting;
        shaderUserFlag = data->shaderUserFlag;
        shaderUserSwitchFlag = data->shaderUserSwitchFlag;
        refractionApplyAlpha = data->refractionApplyAlpha;
        textureColorBlend = 0;
        textureAlphaBlend = 0;
        isPrimitive = data->meshType == MeshType_Primitive;

        switch (data->primitiveColorBlend) {
        case FragmentComposite_Mul: primitiveColorBlend = 0; break;
        case FragmentComposite_Add: primitiveColorBlend = 1; break;
        case FragmentComposite_Sub: primitiveColorBlend = 2; break;
        }

        switch (data->primitiveAlphaBlend) {
        case FragmentComposite_Mul: primitiveAlphaBlend = 0; break;
        case FragmentComposite_Add: primitiveAlphaBlend = 1; break;
        case FragmentComposite_Sub: primitiveAlphaBlend = 2; break;
        }

        texture0ColorSrc  = childFlags >> 17 & 1;
        texture1ColorSrc  = 0;
        primitiveColorSrc = childFlags >> 18 & 1;
        texture0AlphaSrc  = childFlags >> 19 & 1;
        texture1AlphaSrc  = 0;
        primitiveAlphaSrc = childFlags >> 20 & 1;

        _unused0 = 0;
        _unused1 = 0;
    }

    void Initialize(const ChildData* data, u32 childFlags) {
        InitializeChild(data, childFlags);
        shaderUserMacro[0] = '\0';
    }

    void Initialize(const ChildData* data, u32 childFlags, const char* userMacro) {
        InitializeChild(data, childFlags);

        if (userMacro != NULL)
            strcpy(shaderUserMacro, userMacro);
        else
            shaderUserMacro[0] = '\0';
    }

    bool operator==(const FragmentShaderKey& other) {
        return (shaderMode == other.shaderMode
                && softEdge == other.softEdge
                && textureMode == other.textureMode
                && colorMode == other.colorMode
                && alphaMode == other.alphaMode
                && shaderUserSetting == other.shaderUserSetting
                && isPrimitive == other.isPrimitive
                && textureColorBlend == other.textureColorBlend
                && textureAlphaBlend == other.textureAlphaBlend
                && primitiveColorBlend == other.primitiveColorBlend
                && primitiveAlphaBlend == other.primitiveAlphaBlend
                && texture0ColorSrc == other.texture0ColorSrc
                && texture1ColorSrc == other.texture1ColorSrc
                && primitiveColorSrc == other.primitiveColorSrc
                && texture0AlphaSrc == other.texture0AlphaSrc
                && texture1AlphaSrc == other.texture1AlphaSrc
                && primitiveAlphaSrc == other.primitiveAlphaSrc
                && refractionApplyAlpha == other.refractionApplyAlpha
                && shaderUserFlag == other.shaderUserFlag
                && shaderUserSwitchFlag == other.shaderUserSwitchFlag
                && strcmp(shaderUserMacro, other.shaderUserMacro) == 0);
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
    u16 _unused0;
    u32 shaderUserFlag;
    u32 shaderUserSwitchFlag;
    char shaderUserMacro[16];
    u16 _unused1;
    //u8 pad[2];
};
static_assert(sizeof(FragmentShaderKey) == 0x30, "FragmentShaderKey size mismatch");

struct GeometryShaderKey {  // Name is not certain 
    u8 _unused[4];
};
static_assert(sizeof(GeometryShaderKey) == 4, "GeometryShaderKey size mismatch");

struct ShaderTable {  // Actual name not known 
    u32 numShaderProg;
    u32 size;
    u32 shaderSrcOffs;
    u32 shaderProgOffs;
};
static_assert(sizeof(ShaderTable) == 0x10, "ShaderTable size mismatch");

struct ShaderProgram {  // Actual name not known 
    VertexShaderKey vertexShaderKey;
    FragmentShaderKey fragmentShaderKey;
    GeometryShaderKey geometryShaderKey; // ?
    u32 binSize;
    u32 binOffs;
};
static_assert(sizeof(ShaderProgram) == 0x5C, "ShaderProgram size mismatch");

struct VertexTextureLocation {
    u32 location;
};
static_assert(sizeof(VertexTextureLocation) == 4, "VertexTextureLocation size mismatch");

struct FragmentTextureLocation {
    u32 location;
};
static_assert(sizeof(FragmentTextureLocation) == 4, "FragmentTextureLocation size mismatch");

class Heap;

class ParticleShader {
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
    u32 displatListSize;
    Shader shader;
    VertexShaderKey vertexShaderKey;
    FragmentShaderKey fragmentShaderKey;
    GeometryShaderKey geometryShaderKey; // ?
    u32 attrPosBuffer;
    u32 attrNormalBuffer;
    u32 attrColorBuffer;
    u32 attrTexCoordBuffer;
    u32 _unusedAttrBuffer;
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
    UniformBlock _unusedUniformBlock; // ?
    UniformBlock fragmentEmitterStaticUniformBlock;
    UniformBlock stripeUniformBlock;
    UniformBlock vertexUserUniformBlocks[2];
    UniformBlock fragmentUserUniformBlocks[2];
    VertexTextureLocation vertexUserSamplerLocations[8];
    FragmentTextureLocation fragmentUserSamplerLocations[8];
};
static_assert(sizeof(ParticleShader) == 0x61C, "ParticleShader size mismatch");

} } // namespace nw::eft

#endif // EFT_SHADER_H_
