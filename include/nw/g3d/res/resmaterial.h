#pragma once

#include "nw/g3d/res/resfile.h"
#include "nw/g3d/res/resdic.h"

namespace nw { namespace g3d { namespace res {

struct ResShaderParamData
{
    u8 type;
    u8 srcSize;
    u16 srcOffset;
    s32 offset;

    BinString ofsId;
};

class ResShaderParam : public ResShaderParamData
{
public:
    enum Type
    {
        TYPE_BOOL, TYPE_BOOL2, TYPE_BOOL3, TYPE_BOOL4,
        TYPE_INT, TYPE_INT2, TYPE_INT3, TYPE_INT4,
        TYPE_UINT, TYPE_UINT2, TYPE_UINT3, TYPE_UINT4,
        TYPE_FLOAT, TYPE_FLOAT2, TYPE_FLOAT3, TYPE_FLOAT4,
        TYPE_RESERVED2, TYPE_FLOAT2x2, TYPE_FLOAT2x3, TYPE_FLOAT2x4,
        TYPE_RESERVED3, TYPE_FLOAT3x2, TYPE_FLOAT3x3, TYPE_FLOAT3x4,
        TYPE_RESERVED4, TYPE_FLOAT4x2, TYPE_FLOAT4x3, TYPE_FLOAT4x4,
        TYPE_SRT2D, TYPE_SRT3D, TYPE_TEXSRT, TYPE_TEXSRTEX,
        NUM_TYPE
    };

    // TODO

    ResShaderParamData* ptr() { return this; }
    const ResShaderParamData* ptr() const { return this; }
    ResShaderParamData& ref() { return *ptr(); }
    const ResShaderParamData& ref() const { return *ptr(); }

    Type GetType() const { return static_cast<Type>(ref().type); }

    s32 GetOffset() const { return ref().offset; }

    s32 GetSrcOffset() const { return ref().srcOffset; }
};

struct ResMaterialData {
    BinaryBlockHeader blockHeader;
    BinString ofsName;
    u32 flag;
    u16 index;
    u16 numRenderInfo;
    u8 numSampler;
    u8 numTexture;
    u16 numShaderParam;
    u16 numShaderParamVolatile;
    u16 srcParamSize;
    u16 rawParamSize;
    u16 numUserData;
    Offset ofsRenderInfoDic;
    Offset ofsRenderState;
    Offset ofsShaderAssign;
    Offset ofsTextureRefArray;
    Offset ofsSamplerArray;
    Offset ofsSamplerDic;
    Offset ofsShaderParamArray;
    Offset ofsShaderParamDic;
    Offset ofsSrcParam;
    Offset ofsUserDataDic;
    BinPtr pUserPtr;
};

#define NW_G3D_RES_DIC(offset) ResDicType::ResCast(offset.to_ptr<ResDicType::DataType>())

class ResMaterial : private ResMaterialData {
public:
    void Setup();
    void Cleanup();
    void Reset();

    // TODO

    ResMaterialData* ptr() { return this; }
    const ResMaterialData* ptr() const { return this; }
    ResMaterialData& ref() { return *ptr(); }
    const ResMaterialData& ref() const { return *ptr(); }

    int GetShaderParamCount() const { return ref().numShaderParam; }

    int GetShaderParamIndex(const char* str)
    {
        return NW_G3D_RES_DIC(ref().ofsShaderParamDic)->FindIndex(str);
    }

    ResShaderParam* GetShaderParam(int idx)
    {
        ResShaderParamData* pArray = ref().ofsShaderParamArray.to_ptr<ResShaderParamData>();
        return static_cast<ResShaderParam*>(&pArray[idx]); 
    }
};

} } }
