#include "cafe/gfd.h"

#ifdef __cplusplus
extern "C" {
#endif

GX2VertexShader* GFDGetVertexShaderPointer(u32 index, const void* file) {
    GX2VertexShader* shader = NULL;
    u32 currentShaderIndex = 0;
    u32 currentProgramIndex = 0;

    u8* ptr = (u8*)file + ((GFDHeader*)file)->size;
    GFDBlockHeader* block = (GFDBlockHeader*)ptr;

    while (true) {
        block = (GFDBlockHeader*)ptr;
        ptr += block->size;

        switch (block->type) {
            case GFD_BLOCK_TYPE_GX2_VSH_HEADER: {
                if (index == currentShaderIndex) {
                    shader = (GX2VertexShader*)ptr;
                    if (!_GFDRelocateBlock(block->dataSize, shader))
                        return NULL;
                }

                currentShaderIndex++;
                break;
            }

            case GFD_BLOCK_TYPE_GX2_VSH_PROGRAM: {
                if (index == currentProgramIndex) {
                    if ((u32)ptr % GX2_SHADER_ALIGNMENT)
                        return NULL;
                    
                    if (shader == NULL)
                        return NULL;
                    
                    shader->shaderData = ptr;
                }

                currentProgramIndex++;
                break;
            }
            
            default: break;
        }

        ptr += block->dataSize;

        if (currentShaderIndex > index && currentProgramIndex > index)
            break;
        
        if (block->type == GFD_BLOCK_TYPE_END)
            break;
    }

    if (shader != NULL && shader->shaderData != NULL)
        return shader;
    
    return shader;
}

GX2PixelShader* GFDGetPixelShaderPointer(u32 index, const void* file) {
    GX2PixelShader* shader = NULL;
    u32 currentShaderIndex = 0;
    u32 currentProgramIndex = 0;

    u8* ptr = (u8*)file + ((GFDHeader*)file)->size;
    GFDBlockHeader* block = (GFDBlockHeader*)ptr;

    while (true) {
        block = (GFDBlockHeader*)ptr;
        ptr += block->size;

        switch (block->type) {
            case GFD_BLOCK_TYPE_GX2_PSH_HEADER: {
                if (index == currentShaderIndex) {
                    shader = (GX2PixelShader*)ptr;
                    if (!_GFDRelocateBlock(block->dataSize, shader))
                        return NULL;
                }

                currentShaderIndex++;
                break;
            }

            case GFD_BLOCK_TYPE_GX2_PSH_PROGRAM: {
                if (index == currentProgramIndex) {
                    if ((u32)ptr % GX2_SHADER_ALIGNMENT)
                        return NULL;
                    
                    if (shader == NULL)
                        return NULL;
                    
                    shader->shaderData = ptr;
                }

                currentProgramIndex++;
                break;
            }
            
            default: break;
        }

        ptr += block->dataSize;

        if (currentShaderIndex > index && currentProgramIndex > index)
            break;

        if (block->type == GFD_BLOCK_TYPE_END)
            break;
    }

    if (shader != NULL && shader->shaderData != NULL)
        return NULL;
    
    return shader;
}

#ifdef __cplusplus
}
#endif
