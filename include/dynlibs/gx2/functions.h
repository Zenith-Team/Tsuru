/****************************************************************************
 * Copyright (C) 2015
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#pragma once

#ifdef __cplusplus
#include <cstring>
extern "C" {
#else
#include<string.h>
#endif

#include "dynlibs/os/types.h"
#include "dynlibs/gx2/types.h"

extern u32 gx2_handle;

void InitGX2FunctionPointers(void);
void InitAcquireGX2(void);

extern void (*GX2Init)(u32* initAttribs);
extern void (*GX2Shutdown)(void);
extern void (*GX2Flush)(void);
extern void (*GX2ResetGPU)(u32);
extern s32  (*GX2GetMainCoreId)(void);
extern s32  (*GX2DrawDone)(void);
extern void (*GX2ClearColor)(GX2ColorBuffer* colorBuffer, f32 r, f32 g, f32 b, f32 a);
extern void (*GX2SetViewport)(f32 x, f32 y, f32 w, f32 h, f32 nearZ, f32 farZ);
extern void (*GX2SetScissor)(u32 origX, u32 origY, u32 wd, u32 ht);
extern void (*GX2SetContextState)(const GX2ContextState* state);
extern void (*GX2DrawEx)(s32 primitiveType, u32 count, u32 firstVertex, u32 instancesCount);
extern void (*GX2DrawIndexedEx)(s32 primitiveType, u32 count, s32 indexFormat, const void* idx, u32 firstVertex, u32 instancesCount);
extern void (*GX2ClearDepthStencilEx)(GX2DepthBuffer* depthBuffer, f32 depthValue, u8 stencilValue, s32 clearMode);
extern void (*GX2SetClearDepthStencil)(GX2DepthBuffer* depthBuffer, f32 depthValue, u8 stencilValue);
extern void (*GX2CopyColorBufferToScanBuffer)(const GX2ColorBuffer* colorBuffer, s32 scanTarget);
extern void (*GX2SwapScanBuffers)(void);
extern void (*GX2SetTVEnable)(s32 enable);
extern void (*GX2SetSwapInterval)(u32 swapInterval);
extern u32  (*GX2GetSwapInterval)(void);
extern void (*GX2GetSwapStatus)(u32* swapCount, u32* flipCount, OSTime* lastFlip, OSTime* lastVsync);
extern void (*GX2WaitForVsync)(void);
extern void (*GX2CalcTVSize)(s32 tvRenderMode, s32 format, s32 bufferingMode, u32* size, s32* scaleNeeded);
extern void (*GX2Invalidate)(s32 invalidateType, void* ptr, u32 bufferSize);
extern void (*GX2SetTVBuffer)(void* buffer, u32 bufferSize, s32 tvRenderMode, s32 format, s32 bufferingMode);
extern void (*GX2CalcSurfaceSizeAndAlignment)(GX2Surface* surface);
extern void (*GX2InitDepthBufferRegs)(GX2DepthBuffer* depthBuffer);
extern void (*GX2InitColorBufferRegs)(GX2ColorBuffer* colorBuffer);
extern void (*GX2CalcColorBufferAuxInfo)(GX2ColorBuffer* colorBuffer, u32* size, u32* align);
extern void (*GX2CalcDepthBufferHiZInfo)(GX2DepthBuffer* depthBuffer, u32* size, u32* align);
extern void (*GX2InitDepthBufferHiZEnable)(GX2DepthBuffer* depthBuffer, s32 hiZ_enable);
extern void (*GX2SetupContextStateEx)(GX2ContextState* state, s32 enableProfiling);
extern void (*GX2SetColorBuffer)(const GX2ColorBuffer* colorBuffer, s32 target);
extern void (*GX2SetDepthBuffer)(const GX2DepthBuffer* depthBuffer);
extern void (*GX2SetAttribBuffer)(u32 attrIndex, u32 attrSize, u32 stride, const void* attr);
extern void (*GX2InitTextureRegs)(GX2Texture* texture);
extern void (*GX2InitSampler)(GX2Sampler* sampler, s32 texClamp, s32 minMagFilter);
extern void (*GX2InitSamplerClamping)(GX2Sampler* sampler, s32 clampX, s32 clampY, s32 clampZ);
extern void (*GX2InitSamplerLOD)(GX2Sampler* sampler, f32 minLOD, f32 maxLOD, f32 LODBias);
extern void (*GX2InitSamplerDepthCompare)(GX2Sampler* sampler, s32 depthCompare);
extern void (*GX2InitSamplerXYFilter)(GX2Sampler* sampler, s32 magFilter, s32 minFilter, s32 maxAnisoRatio);
extern void (*GX2InitSamplerZMFilter)(GX2Sampler* sampler, s32 zFilter, s32 mipFilter);
extern u32  (*GX2CalcFetchShaderSizeEx)(u32 numAttrib, s32 fetchShaderType, s32 tessellationMode);
extern void (*GX2InitFetchShaderEx)(GX2FetchShader* fs, void* fsBuffer, u32 count, const GX2AttribStream* attribs, s32 fetchShaderType, s32 tessellationMode);
extern void (*GX2SetFetchShader)(const GX2FetchShader* fs);
extern void (*GX2SetVertexUniformReg)(u32 offset, u32 count, const void* values);
extern void (*GX2SetPixelUniformReg)(u32 offset, u32 count, const void* values);
extern void (*GX2SetPixelTexture)(const GX2Texture* texture, u32 textureHwLocation);
extern void (*GX2SetVertexTexture)(const GX2Texture* texture, u32 textureHwLocation);
extern void (*GX2SetPixelSampler)(const GX2Sampler* sampler, u32 samplerHwLocation);
extern void (*GX2SetVertexSampler)(const GX2Sampler* sampler, u32 samplerHwLocation);
extern void (*GX2SetVertexSamplerBorderColor)(u32 samplerUnitNumber, f32 r, f32 g, f32 b, f32 a);
extern void (*GX2SetPixelShader)(const GX2PixelShader* pixelShader);
extern void (*GX2SetVertexShader)(const GX2VertexShader* vertexShader);
extern void (*GX2InitSamplerZMFilter)(GX2Sampler* sampler, s32 zFilter, s32 mipFilter);
extern void (*GX2SetShaderModeEx)(u32 mode, u32 numVsGpr, u32 numVsStackEntries, u32 numGsGpr, u32 numGsStackEntries, u32 numPsGpr, u32 numPsStackEntries);
extern void (*GX2SetColorControl)(s32 lop, u8 blendEnableMask, s32 enableMultiWrite, s32 enableColorBuffer);
extern void (*GX2SetDepthOnlyControl)(s32 enableDepth, s32 enableDepthWrite, s32 depthCompFunction);
extern void (*GX2SetBlendControl)(s32 target, s32 colorSrcBlend, s32 colorDstBlend, s32 colorCombine, s32 separateAlphaBlend, s32 alphaSrcBlend, s32 alphaDstBlend, s32 alphaCombine);
extern void (*GX2CalcDRCSize)(s32 drcMode, s32 format, s32 bufferingMode, u32* size, s32* scaleNeeded);
extern void (*GX2SetDRCBuffer)(void* buffer, u32 bufferSize, s32 drcMode, s32 surfaceFormat, s32 bufferingMode);
extern void (*GX2SetDRCScale)(u32 width, u32 height);
extern void (*GX2SetDRCEnable)(s32 enable);
extern void (*GX2SetPolygonControl)(s32 frontFaceMode, s32 cullFront, s32 cullBack, s32 enableMode, s32 modeFront, s32 modeBack, s32 polyOffsetFront, s32 polyOffsetBack, s32 pointLineOffset);
extern void (*GX2SetCullOnlyControl)(s32 frontFaceMode, s32 cullFront, s32 cullBack);
extern void (*GX2SetDepthStencilControl)(s32 enableDepthTest, s32 enableDepthWrite, s32 depthCompFunction,  s32 stencilTestEnable, s32 backStencilEnable, s32 frontStencilFunc, s32 frontStencilZPass, s32 frontStencilZFail, s32 frontStencilFail, s32 backStencilFunc, s32 backStencilZPass, s32 backStencilZFail, s32 backStencilFail);
extern void (*GX2SetStencilMask)(u8 maskFront, u8 writeMaskFront, u8 refFront, u8 maskBack, u8 writeMaskBack, u8 refBack);
extern void (*GX2SetLineWidth)(f32 width);
extern void (*GX2SetTVGamma)(f32 val);
extern void (*GX2SetTVScale)(u32 x, u32 y);
extern void (*GX2SetDRCGamma)(f32 val);
extern s32  (*GX2GetSystemTVScanMode)(void);
extern s32  (*GX2GetSystemDRCScanMode)(void);
extern void (*GX2RSetAllocator)(void* (*allocFunc)(u32, u32, u32), void (*freeFunc)(u32, void*));
extern void (*GX2CopySurface)(GX2Surface* srcSurface, u32 srcMip, u32 srcSlice, GX2Surface* dstSurface, u32 dstMip, u32 dstSlice);
extern void (*GX2ClearBuffersEx)(GX2ColorBuffer* colorBuffer, GX2DepthBuffer* depthBuffer, f32 r, f32 g, f32 b, f32 a, f32 depthValue, u8 stencilValue, s32 clearFlags);
extern s32  (*GX2GetLastFrame)(s32 target, GX2Texture* texture);
extern void (*GX2BeginDisplayListEx)(void* displayList, u32 size, s32 unkwn);
extern u32  (*GX2EndDisplayList)(void* list);
extern void (*GX2CallDisplayList)(void* list, u32 size);
extern void (*GX2ExpandAAColorBuffer)(GX2ColorBuffer* buffer);
extern void (*GX2ResolveAAColorBuffer)(const GX2ColorBuffer* srcBuffer, GX2Surface* dstSurface, u32 dstMip, u32 dstSlice);
extern u32  (*GX2RCreateBuffer)(GX2RBuffer* buffer);
extern void (*GX2RDestroyBufferEx)(GX2RBuffer* buffer, u32 flags);
extern void* (*GX2RLockBufferEx)(GX2RBuffer* buffer, u32 flags);
extern void (*GX2RUnlockBufferEx)(GX2RBuffer* buffer, u32 flags);
extern void (*GX2RSetAttributeBuffer)(GX2RBuffer* buffer, u32 index, u32 stride, u32 offset);

static inline void GX2InitDepthBuffer(GX2DepthBuffer* depthBuffer, s32 dimension, u32 width, u32 height, u32 depth, s32 format, s32 aa) {
    depthBuffer->surface.dimension = dimension;
    depthBuffer->surface.width = width;
    depthBuffer->surface.height = height;
    depthBuffer->surface.depth = depth;
    depthBuffer->surface.numMips = 1;
    depthBuffer->surface.format = format;
    depthBuffer->surface.aa = aa;
    depthBuffer->surface.use = ((format == GX2_SURFACE_FORMAT_D_D24_S8_UNORM) || (format == GX2_SURFACE_FORMAT_D_D24_S8_FLOAT)) ? GX2_SURFACE_USE_DEPTH_BUFFER : GX2_SURFACE_USE_DEPTH_BUFFER_TEXTURE;
    depthBuffer->surface.tile = GX2_TILE_MODE_DEFAULT;
    depthBuffer->surface.swizzle  = 0;
    depthBuffer->viewMip = 0;
    depthBuffer->viewFirstSlice = 0;
    depthBuffer->viewSlicesCount = depth;
    depthBuffer->clearDepth = 1.0f;
    depthBuffer->clearStencil = 0;
    depthBuffer->hiZ_data = NULL;
    depthBuffer->hiZ_size = 0;
    GX2CalcSurfaceSizeAndAlignment(&depthBuffer->surface);
    GX2InitDepthBufferRegs(depthBuffer);
}

static inline void GX2InitColorBuffer(GX2ColorBuffer* colorBuffer, s32 dimension, u32 width, u32 height, u32 depth, s32 format, s32 aa) {
    colorBuffer->surface.dimension = dimension;
    colorBuffer->surface.width = width;
    colorBuffer->surface.height = height;
    colorBuffer->surface.depth = depth;
    colorBuffer->surface.numMips = 1;
    colorBuffer->surface.format = format;
    colorBuffer->surface.aa = aa;
    colorBuffer->surface.use = GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE_FTV;
    colorBuffer->surface.imageSize = 0;
    colorBuffer->surface.imageData = NULL;
    colorBuffer->surface.mipSize = 0;
    colorBuffer->surface.mipData = NULL;
    colorBuffer->surface.tile = GX2_TILE_MODE_DEFAULT;
    colorBuffer->surface.swizzle = 0;
    colorBuffer->surface.align = 0;
    colorBuffer->surface.pitch = 0;
    u32 i;
    for (i = 0; i < 13; i++)
        colorBuffer->surface.mipOffset[i] = 0;
    colorBuffer->viewMip = 0;
    colorBuffer->viewFirstSlice = 0;
    colorBuffer->viewSlicesCount = depth;
    colorBuffer->auxData = NULL;
    colorBuffer->auxSize = 0;
    for (i = 0; i < 5; i++)
        colorBuffer->regs[i] = 0;

    GX2CalcSurfaceSizeAndAlignment(&colorBuffer->surface);
    GX2InitColorBufferRegs(colorBuffer);
}

static inline void GX2InitAttribStream(GX2AttribStream* attr, u32 location, u32 buffer, u32 offset, s32 format) {
    attr->location = location;
    attr->buffer = buffer;
    attr->offset = offset;
    attr->format = format;
    attr->indexType = 0;
    attr->divisor = 0;
    attr->destinationSelector = attributeDestCompSelector[format & 0xFF];
    attr->endianSwap  = GX2_ENDIANSWAP_DEFAULT;
}

static inline void GX2InitTexture(GX2Texture* tex, u32 width, u32 height, u32 depth, u32 numMips, s32 format, s32 dimension, s32 tile) {
    tex->surface.dimension = dimension;
    tex->surface.width = width;
    tex->surface.height = height;
    tex->surface.depth = depth;
    tex->surface.numMips = numMips;
    tex->surface.format = format;
    tex->surface.aa = GX2_AA_MODE_1X;
    tex->surface.use = GX2_SURFACE_USE_TEXTURE;
    tex->surface.imageSize = 0;
    tex->surface.imageData = NULL;
    tex->surface.mipSize = 0;
    tex->surface.mipData = NULL;
    tex->surface.tile = tile;
    tex->surface.swizzle = 0;
    tex->surface.align = 0;
    tex->surface.pitch = 0;
    u32 i;
    for (i = 0; i < 13; i++)
        tex->surface.mipOffset[i] = 0;
    tex->viewFirstMip = 0;
    tex->viewMipsCount = numMips;
    tex->viewFirstSlice = 0;
    tex->viewSlicesCount = depth;
    tex->componentSelector = textureCompSelector[format & 0x3F];
    for (i = 0; i < 5; i++)
        tex->regs[i] = 0;

    GX2CalcSurfaceSizeAndAlignment(&tex->surface);
    GX2InitTextureRegs(tex);
}

static inline GX2UniformVar* GX2GetVertexUniformVar(const GX2VertexShader* shader, const char* name) {
    for (u32 i = 0; i < shader->uniformVarsCount; i++) {
        if (strcmp(shader->uniformVar[i].name, name) == 0)
            return &shader->uniformVar[i];
    }

    return NULL;
}

static inline s32 GX2GetVertexUniformVarOffset(const GX2VertexShader* shader, const char* name) {
    GX2UniformVar* var = GX2GetVertexUniformVar(shader, name);
    if (var)
        return var->offset;

    return -1;
}

static inline GX2UniformVar* GX2GetPixelUniformVar(const GX2PixelShader* shader, const char* name) {
    for (u32 i = 0; i < shader->uniformVarsCount; i++) {
        if (strcmp(shader->uniformVar[i].name, name) == 0)
            return &shader->uniformVar[i];
    }

    return NULL;
}

static inline s32 GX2GetPixelUniformVarOffset(const GX2PixelShader* shader, const char* name) {
    GX2UniformVar* var = GX2GetPixelUniformVar(shader, name);
    if (var)
        return var->offset;

    return -1;
}

#ifdef __cplusplus
}
#endif
