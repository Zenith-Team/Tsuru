#pragma once

#include "nw/g3d/res/resfile.h"

namespace nw { namespace g3d { namespace res {

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

class ResMaterial : private ResMaterialData {
public:
    void Setup();
    void Cleanup();
    void Reset();

    // TODO
};

} } }
