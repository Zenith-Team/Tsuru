#pragma once

#include "nw/g3d/res/resmaterial.h"
#include "nw/g3d/fnd/buffer.h"

namespace nw { namespace g3d {

namespace res { class ResTexture; }

class MaterialObj {
public:
    int GetShaderParamIndex(const char* name) const { return res->GetShaderParamIndex(name); }

    res::ResShaderParam* GetResShaderParam(int paramIndex)
    {
        return res->GetShaderParam(paramIndex);
    }

    template <typename T>
    T* EditShaderParam(int paramIndex)
    {
        res::ResShaderParam* param = GetResShaderParam(paramIndex);
        if (param->GetOffset() >= 0 && param->GetType() != res::ResShaderParam::TYPE_TEXSRTEX)
            SetDirtyFlag(paramIndex);

        return AddOffset<T>(srcParam, param->GetSrcOffset());
    }

    res::ResMaterial* res;
    u32 flag;
    u32* dirtyFlagArray;
    fnd::GfxBuffer matBlock;
    void* srcParam;
    res::ResTexture** textureArray;
    void* userPtr;
    void* bufferPtr;
    void* blockBuffer;

protected:
    enum Flag
    {
        BLOCK_BUFFER_VALID  = 0x1 << 0,
        BLOCK_BUFFER_SWAP   = 0x1 << 1,
        PARAM_DIRTY         = 0x1 << 2
    };

    void SetDirtyFlag(int paramIndex)
    {
        flag |= PARAM_DIRTY;
        dirtyFlagArray[paramIndex >> 5] |= 0x1 << (paramIndex & 0x1F);
    }
};

} }
