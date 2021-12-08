#include "tsuru/shader.h"

#include "cafe/gfd.h"
#include "sead/filedevicemgr.h"

Shader::Shader(const sead::SafeString& path, u32 vtxIdx, u32 fragIdx, sead::Heap* heap)
    : inited(false)
    , vertexShader(nullptr)
    , pixelShader(nullptr)
    , gsh(nullptr)
{
    {
        sead::FileHandle handle;
        if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, path, sead::FileDevice::FileOpenFlag_ReadOnly, 0))
            return;

        u32 fileSize = handle.getFileSize();

        if (fileSize == 0)
            return;

        if (this->gsh = new(heap, GX2_SHADER_ALIGNMENT) u8[fileSize], !this->gsh)
            return;

        if (handle.read(this->gsh, fileSize) != fileSize) {
            delete[] this->gsh; this->gsh = nullptr;
            return;
        }
    }

    if (GFDGetVertexShaderCount(this->gsh) <= vtxIdx || GFDGetPixelShaderCount(this->gsh) <= fragIdx) {
        delete[] this->gsh; this->gsh = nullptr;
        return;
    }

    this->vertexShader = GFDGetVertexShaderPointer(vtxIdx, this->gsh);
    this->pixelShader = GFDGetPixelShaderPointer(fragIdx, this->gsh);

    if (!this->vertexShader || !this->pixelShader) {
        delete[] this->gsh; this->gsh = nullptr;
        this->vertexShader = nullptr;
        this->pixelShader = nullptr;
        return;
    }

    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, this->vertexShader->shaderData, this->vertexShader->shaderSize);
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, this->pixelShader->shaderData, this->pixelShader->shaderSize);

    this->inited = true;
}

Shader::~Shader() {
    if (!this->inited)
        return;

    if (this->gsh) delete[] this->gsh; this->gsh = nullptr;

    this->vertexShader = nullptr;
    this->pixelShader = nullptr;

    this->inited = false;
}

void Shader::use(const GX2FetchShader* fetchShader) const {
    if (!this->inited)
        return;

    if (fetchShader)
        GX2SetFetchShader(fetchShader);

    GX2SetVertexShader(this->vertexShader);
    GX2SetPixelShader(this->pixelShader);
}

void ShaderUR::use(const GX2FetchShader* fetchShader) const {
    if (!this->inited)
        return;

    GX2SetShaderModeEx(GX2_SHADER_MODE_UNIFORM_REGISTER, 48, 64, 0, 0, 200, 192);

    Shader::use(fetchShader);
}
