#pragma once

#include "dynlibs/gx2/functions.h"

#include "sead/heap.h"
#include "sead/safestring.h"

class Shader {
public:
    Shader(const sead::SafeString& path, u32 vtxIndex = 0, u32 fragIndex = 0, sead::Heap* heap = nullptr);
    virtual ~Shader();

    bool isInitialized() const { return this->inited; }

    virtual void use() const;

protected:
    bool inited;
    GX2VertexShader* vertexShader;
    GX2PixelShader* pixelShader;
    u8* gsh;
};

// Shader class enforcing uniform register mode
class ShaderUR : public Shader {
public:
    ShaderUR(const sead::SafeString& path, u32 vtxIndex = 0, u32 fragIndex = 0, sead::Heap* heap = nullptr)
        : Shader(path, vtxIndex, fragIndex, heap)
    { }

    void use() const override;

    void setBool(const sead::SafeString& name, bool value) const {
        this->setInt(name, (s32)value);
    }

    void setInt(const sead::SafeString& name, s32 value) const {
        const char* cname = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);

        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }

    void setFloat(const sead::SafeString& name, f32 value) const {
        const char* cname = name.cstr();

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 1, &value);

        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 1, &value);
    }

    void setMtx34(const sead::SafeString& name, const Mtx34& mat) const {
        const char* cname = name.cstr();

        // GLSL shader uses column-major matrix
        f32 mtx[16] = {
            mat.rows[0][0], mat.rows[1][0], mat.rows[2][0], 0.0f,
            mat.rows[0][1], mat.rows[1][1], mat.rows[2][1], 0.0f,
            mat.rows[0][2], mat.rows[1][2], mat.rows[2][2], 0.0f,
            mat.rows[0][3], mat.rows[1][3], mat.rows[2][3], 1.0f
        };

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 16, mtx);

        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 16, mtx);
    }

    void setMtx44(const sead::SafeString& name, const Mtx44& mat) const {
        const char* cname = name.cstr();

        // GLSL shader uses column-major matrix
        f32 mtx[16] = {
            mat.rows[0][0], mat.rows[1][0], mat.rows[2][0], mat.rows[3][0],
            mat.rows[0][1], mat.rows[1][1], mat.rows[2][1], mat.rows[3][1],
            mat.rows[0][2], mat.rows[1][2], mat.rows[2][2], mat.rows[3][2],
            mat.rows[0][3], mat.rows[1][3], mat.rows[2][3], mat.rows[3][3]
        };

        s32 vtxOffs = GX2GetVertexUniformVarOffset(this->vertexShader, cname);
        if (vtxOffs != -1)
            GX2SetVertexUniformReg(vtxOffs, 16, mtx);

        s32 frgOffs = GX2GetPixelUniformVarOffset(this->pixelShader, cname);
        if (frgOffs != -1)
            GX2SetPixelUniformReg(frgOffs, 16, mtx);
    }
};
