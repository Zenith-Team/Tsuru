#pragma once

#include "dynlibs/gx2/functions.h"

#include "sead/heap.h"
#include "sead/safestring.h"

class Shader {
public:
    Shader(const sead::SafeString& path, u32 vtxIndex = 0, u32 fragIndex = 0, sead::Heap* heap = nullptr);
    virtual ~Shader();

    bool isInitialized() const { return this->inited; }

    virtual void use(const GX2FetchShader* fetchShader) const;

protected:
    bool inited;
    GX2VertexShader* vertexShader;
    GX2PixelShader* pixelShader;
    u8* gsh;
};

// Shader class enforcing uniform register mode
class ShaderUR : public Shader {
public:
    void use(const GX2FetchShader* fetchShader) const override;

    void setBool(const sead::SafeString& name, bool value) const {
        this->setInt(name, (s32)value);
    }

    void setInt(const sead::SafeString& name, s32 value) const {
        const char* cname = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs == -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);
        
        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs == -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }

    void setFloat(const sead::SafeString& name, f32 value) const {
        const char* cname = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs == -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);
        
        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs == -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }
};
