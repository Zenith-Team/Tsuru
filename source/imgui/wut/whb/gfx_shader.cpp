#include "imgui/wut/gfd.h"
#include "imgui/wut/whb/gfx.h"
#include "imgui/wut/whb/gfx_heap.h"

#include <string.h>

#include "dynlibs/os/functions.h"

static void* GfxHeapAllocMEM2(u32 size, u32 alignment) {
    if (alignment < 4) {
        alignment = 4;
    }

    return MEMAllocFromDefaultHeapEx(size, alignment);
}

static void GfxHeapFreeMEM2(void* block) {
    MEMFreeToDefaultHeap(block);
}

GX2PixelShader* WHBGfxLoadGFDPixelShader(uint32_t index, const void* file) {
    uint32_t headerSize, programSize;
    GX2PixelShader* shader = NULL;
    void* program = NULL;

    if (index >= GFDGetPixelShaderCount(file)) {
        goto error;
    }

    headerSize = GFDGetPixelShaderHeaderSize(index, file);
    if (!headerSize) {
        goto error;
    }

    programSize = GFDGetPixelShaderProgramSize(index, file);
    if (!programSize) {
        goto error;
    }

    shader = (GX2PixelShader*)GfxHeapAllocMEM2(headerSize, 64);
    if (!shader) {
        goto error;
    }

    shader->shaderProgramBuffer.flags = GX2R_RESOURCE_BIND_SHADER_PROGRAM | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    shader->shaderProgramBuffer.elemSize = programSize;
    shader->shaderProgramBuffer.elemCount = 1;
    shader->shaderProgramBuffer.buffer = NULL;
    if (!GX2RCreateBuffer(&shader->shaderProgramBuffer)) {
        goto error;
    }

    program = GX2RLockBufferEx(&shader->shaderProgramBuffer, 0);
    if (!program) {
        goto error;
    }

    if (!GFDGetPixelShader(shader, program, index, file)) {
        GX2RUnlockBufferEx(&shader->shaderProgramBuffer, GX2R_RESOURCE_DISABLE_CPU_INVALIDATE | GX2R_RESOURCE_DISABLE_GPU_INVALIDATE);
        goto error;
    }

    GX2RUnlockBufferEx(&shader->shaderProgramBuffer, 0);

    // For some reason we still need to manually invalidate the buffers,
    // even though GX2RUnlockBuffer SHOULD be doing that for us
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, shader->shaderData, shader->shaderSize);
    return shader;

error:
    if (shader) {
        if (shader->shaderProgramBuffer.buffer) {
            GX2RDestroyBufferEx(&shader->shaderProgramBuffer, 0);
        }

        GfxHeapFreeMEM2(shader);
    }

    return NULL;
}

bool WHBGfxFreePixelShader(GX2PixelShader* shader) {
    if (shader->shaderProgramBuffer.buffer) {
        GX2RDestroyBufferEx(&shader->shaderProgramBuffer, 0);
    }

    GfxHeapFreeMEM2(shader);
    return true;
}

GX2VertexShader* WHBGfxLoadGFDVertexShader(uint32_t index, const void* file) {
    uint32_t headerSize, programSize;
    GX2VertexShader* shader = NULL;
    void* program = NULL;

    if (index >= GFDGetVertexShaderCount(file)) {
        goto error;
    }

    headerSize = GFDGetVertexShaderHeaderSize(index, file);
    if (!headerSize) {
        goto error;
    }

    programSize = GFDGetVertexShaderProgramSize(index, file);
    if (!programSize) {
        goto error;
    }

    shader = (GX2VertexShader*)GfxHeapAllocMEM2(headerSize, 64);
    if (!shader) {
        goto error;
    }

    shader->shaderProgramBuffer.flags = GX2R_RESOURCE_BIND_SHADER_PROGRAM | GX2R_RESOURCE_USAGE_CPU_READ | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ;
    shader->shaderProgramBuffer.elemSize = programSize;
    shader->shaderProgramBuffer.elemCount = 1;
    shader->shaderProgramBuffer.buffer = NULL;
    if (!GX2RCreateBuffer(&shader->shaderProgramBuffer)) {
        goto error;
    }

    program = GX2RLockBufferEx(&shader->shaderProgramBuffer, 0);
    if (!program) {
        goto error;
    }

    if (!GFDGetVertexShader(shader, program, index, file)) {
        GX2RUnlockBufferEx(&shader->shaderProgramBuffer, GX2R_RESOURCE_DISABLE_CPU_INVALIDATE | GX2R_RESOURCE_DISABLE_GPU_INVALIDATE);
        goto error;
    }

    GX2RUnlockBufferEx(&shader->shaderProgramBuffer, 0);

    // For some reason we still need to manually invalidate the buffers,
    // even though GX2RUnlockBuffer SHOULD be doing that for us
    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, shader->shaderData, shader->shaderSize);
    return shader;

error:
    if (shader) {
        if (shader->shaderProgramBuffer.buffer) {
            GX2RDestroyBufferEx(&shader->shaderProgramBuffer, 0);
        }

        GfxHeapFreeMEM2(shader);
    }

    return NULL;
}

bool WHBGfxFreeVertexShader(GX2VertexShader* shader) {
    if (shader->shaderProgramBuffer.buffer) {
        GX2RDestroyBufferEx(&shader->shaderProgramBuffer, 0);
    }

    GfxHeapFreeMEM2(shader);
    return true;
}

bool WHBGfxLoadGFDShaderGroup(WHBGfxShaderGroup* group, uint32_t index, const void* file) {
    memset(group, 0, sizeof(WHBGfxShaderGroup));
    group->vertexShader = WHBGfxLoadGFDVertexShader(index, file);
    group->pixelShader = WHBGfxLoadGFDPixelShader(index, file);

    if (!group->vertexShader || !group->pixelShader) {
        // A shader group requires at least a vertex shader and a pixel shader.
        WHBGfxFreeShaderGroup(group);
        return false;
    }

    return true;
}

static uint32_t GfxGetAttribFormatSel(s32 format) {
    switch (format) {
        case GX2_ATTRIB_FORMAT_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_UINT:
        case GX2_ATTRIB_FORMAT_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_SINT:
        case GX2_ATTRIB_FORMAT_32_FLOAT:
            return GX2_COMP_SEL_X001;
        case GX2_ATTRIB_FORMAT_8_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_8_UINT:
        case GX2_ATTRIB_FORMAT_8_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_8_SINT:
        case GX2_ATTRIB_FORMAT_32_32_FLOAT:
            return GX2_COMP_SEL_XY01;
        case GX2_ATTRIB_FORMAT_32_32_32_FLOAT:
            return GX2_COMP_SEL_XYZ1;
        case GX2_ATTRIB_FORMAT_8_8_8_8_UNORM:
        case GX2_ATTRIB_FORMAT_8_8_8_8_UINT:
        case GX2_ATTRIB_FORMAT_8_8_8_8_SNORM:
        case GX2_ATTRIB_FORMAT_8_8_8_8_SINT:
        case GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT:
            return GX2_COMP_SEL_XYZW;
        default:
            return GX2_COMP_SEL_NONE;
    }
}

static int32_t GfxGetVertexAttribVarLocation(const GX2VertexShader* shader, const char* name) {
    u32 i;

    for (i = 0; i < shader->attributeVarsCount; ++i) {
        if (strcmp(shader->attributeVar[i].name, name) == 0) {
            return shader->attributeVar[i].location;
        }
    }

    return -1;
}

bool WHBGfxInitShaderAttribute(WHBGfxShaderGroup* group, const char* name, uint32_t buffer, uint32_t offset, s32 format) {
    GX2AttribStream* attrib;
    int32_t location;

    location = GfxGetVertexAttribVarLocation(group->vertexShader, name);
    if (location == -1) {
        return false;
    }

    attrib = &group->attributes[group->numAttributes++];
    attrib->location = location;
    attrib->buffer = buffer;
    attrib->offset = offset;
    attrib->format = format;
    attrib->indexType = GX2_ATTRIB_INDEX_PER_VERTEX;
    attrib->divisor = 0;
    attrib->destinationSelector = GfxGetAttribFormatSel(format);
    attrib->endianSwap = GX2_ENDIANSWAP_DEFAULT;
    return true;
}

bool WHBGfxInitFetchShader(WHBGfxShaderGroup* group) {
    uint32_t size = GX2CalcFetchShaderSizeEx(group->numAttributes, GX2_FETCH_SHADER_TESSELATION_NONE, GX2_TESSELLATION_MODE_DISCRETE);
    group->fetchShaderProgram = GfxHeapAllocMEM2(size, GX2_SHADER_PROGRAM_ALIGNMENT);

    GX2InitFetchShaderEx(&group->fetchShader,
        group->fetchShaderProgram,
        group->numAttributes,
        group->attributes,
        GX2_FETCH_SHADER_TESSELATION_NONE,
        GX2_TESSELLATION_MODE_DISCRETE);

    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, group->fetchShaderProgram, size);
    return true;
}

bool WHBGfxFreeShaderGroup(WHBGfxShaderGroup* group) {
    if (group->fetchShaderProgram) {
        GfxHeapFreeMEM2(group->fetchShaderProgram);
        group->fetchShaderProgram = NULL;
    }

    if (group->pixelShader) {
        WHBGfxFreePixelShader(group->pixelShader);
        group->pixelShader = NULL;
    }

    if (group->vertexShader) {
        WHBGfxFreeVertexShader(group->vertexShader);
        group->vertexShader = NULL;
    }

    return true;
}
