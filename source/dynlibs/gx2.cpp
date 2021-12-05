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
#include "dynlibs/os/functions.h"
#include "dynlibs/gx2/types.h"

u32 gx2Handle = 0;

EXPORT_DECL(void, GX2Init, u32* initAttribs);
EXPORT_DECL(void, GX2Shutdown, void);
EXPORT_DECL(void, GX2Flush, void);
EXPORT_DECL(void, GX2ResetGPU, u32);
EXPORT_DECL(s32,  GX2GetMainCoreId, void);
EXPORT_DECL(s32,  GX2DrawDone, void);
EXPORT_DECL(void, GX2ClearColor, GX2ColorBuffer* colorBuffer, f32 r, f32 g, f32 b, f32 a);
EXPORT_DECL(void, GX2SetViewport, f32 x, f32 y, f32 w, f32 h, f32 nearZ, f32 farZ);
EXPORT_DECL(void, GX2SetScissor, u32 origX, u32 origY, u32 wd, u32 ht);
EXPORT_DECL(void, GX2SetContextState, const GX2ContextState* state);
EXPORT_DECL(void, GX2DrawEx, s32 primitiveType, u32 count, u32 firstVertex, u32 instancesCount);
EXPORT_DECL(void, GX2DrawIndexedEx, s32 primitiveType, u32 count, s32 indexFormat, const void* idx, u32 firstVertex, u32 instancesCount);
EXPORT_DECL(void, GX2ClearDepthStencilEx, GX2DepthBuffer* depthBuffer, f32 depthValue, u8 stencilValue, s32 clearMode);
EXPORT_DECL(void, GX2SetClearDepthStencil, GX2DepthBuffer* depthBuffer, f32 depthValue, u8 stencilValue);
EXPORT_DECL(void, GX2CopyColorBufferToScanBuffer, const GX2ColorBuffer* colorBuffer, s32 scanTarget);
EXPORT_DECL(void, GX2SwapScanBuffers, void);
EXPORT_DECL(void, GX2SetTVEnable, s32 enable);
EXPORT_DECL(void, GX2SetSwapInterval, u32 swapInterval);
EXPORT_DECL(u32,  GX2GetSwapInterval, void);
EXPORT_DECL(void, GX2GetSwapStatus, u32* swapCount, u32* flipCount, OSTime* lastFlip, OSTime* lastVsync);
EXPORT_DECL(void, GX2WaitForVsync, void);
EXPORT_DECL(void, GX2CalcTVSize, s32 tvRenderMode, s32 format, s32 bufferingMode, u32* size, s32* scaleNeeded);
EXPORT_DECL(void, GX2Invalidate, s32 invalidateType, void* ptr, u32 bufferSize);
EXPORT_DECL(void, GX2SetTVBuffer, void* buffer, u32 bufferSize, s32 tvRenderMode, s32 format, s32 bufferingMode);
EXPORT_DECL(void, GX2CalcSurfaceSizeAndAlignment, GX2Surface* surface);
EXPORT_DECL(void, GX2InitDepthBufferRegs, GX2DepthBuffer* depthBuffer);
EXPORT_DECL(void, GX2InitColorBufferRegs, GX2ColorBuffer* colorBuffer);
EXPORT_DECL(void, GX2CalcColorBufferAuxInfo, GX2ColorBuffer* colorBuffer, u32* size, u32* align);
EXPORT_DECL(void, GX2CalcDepthBufferHiZInfo, GX2DepthBuffer* depthBuffer, u32* size, u32* align);
EXPORT_DECL(void, GX2InitDepthBufferHiZEnable, GX2DepthBuffer* depthBuffer, s32 hiZ_enable);
EXPORT_DECL(void, GX2SetupContextStateEx, GX2ContextState* state, s32 enableProfiling);
EXPORT_DECL(void, GX2SetColorBuffer, const GX2ColorBuffer* colorBuffer, s32 target);
EXPORT_DECL(void, GX2SetDepthBuffer, const GX2DepthBuffer* depthBuffer);
EXPORT_DECL(void, GX2SetAttribBuffer, u32 attrIndex, u32 attrSize, u32 stride, const void* attr);
EXPORT_DECL(void, GX2InitTextureRegs, GX2Texture* texture);
EXPORT_DECL(void, GX2InitSampler, GX2Sampler* sampler, s32 texClamp, s32 minMagFilter);
EXPORT_DECL(void, GX2InitSamplerClamping, GX2Sampler* sampler, s32 clampX, s32 clampY, s32 clampZ);
EXPORT_DECL(void, GX2InitSamplerLOD, GX2Sampler* sampler, f32 minLOD, f32 maxLOD, f32 LODBias);
EXPORT_DECL(void, GX2InitSamplerDepthCompare, GX2Sampler* sampler, s32 depthCompare);
EXPORT_DECL(void, GX2InitSamplerXYFilter, GX2Sampler* sampler, s32 magFilter, s32 minFilter, s32 maxAnisoRatio);
EXPORT_DECL(void, GX2InitSamplerZMFilter, GX2Sampler* sampler, s32 zFilter, s32 mipFilter);
EXPORT_DECL(void, GX2SetShaderModeEx, u32 mode, u32 numVsGpr, u32 numVsStackEntries, u32 numGsGpr, u32 numGsStackEntries, u32 numPsGpr, u32 numPsStackEntries);
EXPORT_DECL(u32,  GX2CalcFetchShaderSizeEx, u32 numAttrib, s32 fetchShaderType, s32 tessellationMode);
EXPORT_DECL(void, GX2InitFetchShaderEx, GX2FetchShader* fs, void* fsBuffer, u32 count, const GX2AttribStream* attribs, s32 fetchShaderType, s32 tessellationMode);
EXPORT_DECL(void, GX2SetFetchShader, const GX2FetchShader* fs);
EXPORT_DECL(void, GX2SetVertexUniformReg, u32 offset, u32 count, const void* values);
EXPORT_DECL(void, GX2SetPixelUniformReg, u32 offset, u32 count, const void* values);
EXPORT_DECL(void, GX2SetPixelTexture, const GX2Texture* texture, u32 textureHwLocation);
EXPORT_DECL(void, GX2SetVertexTexture, const GX2Texture* texture, u32 textureHwLocation);
EXPORT_DECL(void, GX2SetPixelSampler, const GX2Sampler* sampler, u32 samplerHwLocation);
EXPORT_DECL(void, GX2SetVertexSampler, const GX2Sampler* sampler, u32 samplerHwLocation);
EXPORT_DECL(void, GX2SetVertexSamplerBorderColor, u32 samplerUnitNumber, f32 r, f32 g, f32 b, f32 a);
EXPORT_DECL(void, GX2SetPixelShader, const GX2PixelShader* pixelShader);
EXPORT_DECL(void, GX2SetVertexShader, const GX2VertexShader* vertexShader);
EXPORT_DECL(void, GX2SetColorControl, s32 lop, u8 blendEnableMask, s32 enableMultiWrite, s32 enableColorBuffer);
EXPORT_DECL(void, GX2SetDepthOnlyControl, s32 enableDepth, s32 enableDepthWrite, s32 depthCompFunction);
EXPORT_DECL(void, GX2SetBlendControl, s32 target, s32 colorSrcBlend, s32 colorDstBlend, s32 colorCombine, s32 separateAlphaBlend, s32 alphaSrcBlend, s32 alphaDstBlend, s32 alphaCombine);
EXPORT_DECL(void, GX2CalcDRCSize, s32 drcMode, s32 format, s32 bufferingMode, u32* size, s32* scaleNeeded);
EXPORT_DECL(void, GX2SetDRCBuffer, void* buffer, u32 bufferSize, s32 drcMode, s32 surfaceFormat, s32 bufferingMode);
EXPORT_DECL(void, GX2SetDRCScale, u32 width, u32 height);
EXPORT_DECL(void, GX2SetDRCEnable, s32 enable);
EXPORT_DECL(void, GX2SetPolygonControl, s32 frontFaceMode, s32 cullFront, s32 cullBack, s32 enableMode, s32 modeFront, s32 modeBack, s32 polyOffsetFront, s32 polyOffsetBack, s32 pointLineOffset);
EXPORT_DECL(void, GX2SetCullOnlyControl, s32 frontFaceMode, s32 cullFront, s32 cullBack);
EXPORT_DECL(void, GX2SetDepthStencilControl, s32 enableDepthTest, s32 enableDepthWrite, s32 depthCompFunction,  s32 stencilTestEnable, s32 backStencilEnable, s32 fontStencilFunc, s32 frontStencilZPass, s32 frontStencilZFail, s32 frontStencilFail, s32 backStencilFunc, s32 backStencilZPpass, s32 backStencilZFail, s32 backStencilFail);
EXPORT_DECL(void, GX2SetStencilMask, u8 maskFront, u8 writeMaskFront, u8 refFront, u8 maskBack, u8 writeMaskBack, u8 refBack);
EXPORT_DECL(void, GX2SetLineWidth, f32 width);
EXPORT_DECL(void, GX2SetTVGamma, f32 val);
EXPORT_DECL(void, GX2SetTVScale, u32 x, u32 y);
EXPORT_DECL(void, GX2SetDRCGamma, f32 gam);
EXPORT_DECL(s32,  GX2GetSystemTVScanMode, void);
EXPORT_DECL(s32,  GX2GetSystemDRCScanMode, void);
EXPORT_DECL(void, GX2RSetAllocator, void* (* allocFunc)(u32, u32, u32), void (* freeFunc)(u32, void*));
EXPORT_DECL(void, GX2CopySurface, GX2Surface* srcSurface, u32 srcMip, u32 srcSlice, GX2Surface* dstSurface, u32 dstMip, u32 dstSlice);
EXPORT_DECL(s32,  GX2GetLastFrame, s32 target, GX2Texture* texture);
EXPORT_DECL(void, GX2BeginDisplayListEx, void* displayList, u32 size, s32 unkwn);
EXPORT_DECL(u32,  GX2EndDisplayList, void* list);
EXPORT_DECL(void, GX2CallDisplayList, void* list, u32 size);
EXPORT_DECL(void, GX2ExpandAAColorBuffer, GX2ColorBuffer* buffer);
EXPORT_DECL(void, GX2ResolveAAColorBuffer, const GX2ColorBuffer* srcBuffer, GX2Surface* dstSurface, u32 dstMip, u32 dstSlice);
EXPORT_DECL(u32,  GX2RCreateBuffer, GX2RBuffer* buffer);
EXPORT_DECL(void, GX2RDestroyBufferEx, GX2RBuffer* buffer, u32 flags);
EXPORT_DECL(void*, GX2RLockBufferEx, GX2RBuffer* buffer, u32 flags);
EXPORT_DECL(void, GX2RUnlockBufferEx, GX2RBuffer* buffer, u32 flags);
EXPORT_DECL(void, GX2RSetAttributeBuffer, GX2RBuffer* buffer, u32 index, u32 stride, u32 offset);
EXPORT_DECL(void, GX2ClearBuffersEx, GX2ColorBuffer* colorBuffer, GX2DepthBuffer* depthBuffer, f32 r, f32 g, f32 b, f32 a, f32 depthValue, u8 stencilValue, s32 clearFlags);

void InitAcquireGX2(void) {
    if (coreinitHandle == 0)
        InitAcquireOS();

    OSDynLoad_Acquire("gx2.rpl", &gx2Handle);
}

extern "C" void InitGX2FunctionPointers(void) {
    u32* funcPointer = 0;
    InitAcquireGX2();

    OS_FIND_EXPORT(gx2Handle, GX2Init);
    OS_FIND_EXPORT(gx2Handle, GX2Shutdown);
    OS_FIND_EXPORT(gx2Handle, GX2Flush);
    OS_FIND_EXPORT(gx2Handle, GX2ResetGPU);
    OS_FIND_EXPORT(gx2Handle, GX2GetMainCoreId);
    OS_FIND_EXPORT(gx2Handle, GX2DrawDone);
    OS_FIND_EXPORT(gx2Handle, GX2ClearColor);
    OS_FIND_EXPORT(gx2Handle, GX2SetViewport);
    OS_FIND_EXPORT(gx2Handle, GX2SetScissor);
    OS_FIND_EXPORT(gx2Handle, GX2SetContextState);
    OS_FIND_EXPORT(gx2Handle, GX2DrawEx);
    OS_FIND_EXPORT(gx2Handle, GX2DrawIndexedEx);
    OS_FIND_EXPORT(gx2Handle, GX2ClearDepthStencilEx);
    OS_FIND_EXPORT(gx2Handle, GX2CopyColorBufferToScanBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SwapScanBuffers);
    OS_FIND_EXPORT(gx2Handle, GX2SetTVEnable);
    OS_FIND_EXPORT(gx2Handle, GX2SetSwapInterval);
    OS_FIND_EXPORT(gx2Handle, GX2GetSwapInterval);
    OS_FIND_EXPORT(gx2Handle, GX2GetSwapStatus);
    OS_FIND_EXPORT(gx2Handle, GX2WaitForVsync);
    OS_FIND_EXPORT(gx2Handle, GX2CalcTVSize);
    OS_FIND_EXPORT(gx2Handle, GX2Invalidate);
    OS_FIND_EXPORT(gx2Handle, GX2SetTVBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2CalcSurfaceSizeAndAlignment);
    OS_FIND_EXPORT(gx2Handle, GX2InitDepthBufferRegs);
    OS_FIND_EXPORT(gx2Handle, GX2InitColorBufferRegs);
    OS_FIND_EXPORT(gx2Handle, GX2CalcColorBufferAuxInfo);
    OS_FIND_EXPORT(gx2Handle, GX2CalcDepthBufferHiZInfo);
    OS_FIND_EXPORT(gx2Handle, GX2InitDepthBufferHiZEnable);
    OS_FIND_EXPORT(gx2Handle, GX2SetupContextStateEx);
    OS_FIND_EXPORT(gx2Handle, GX2SetColorBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SetDepthBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SetAttribBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2InitTextureRegs);
    OS_FIND_EXPORT(gx2Handle, GX2InitSampler);
    OS_FIND_EXPORT(gx2Handle, GX2SetShaderModeEx);
    OS_FIND_EXPORT(gx2Handle, GX2CalcFetchShaderSizeEx);
    OS_FIND_EXPORT(gx2Handle, GX2InitFetchShaderEx);
    OS_FIND_EXPORT(gx2Handle, GX2SetFetchShader);
    OS_FIND_EXPORT(gx2Handle, GX2SetVertexUniformReg);
    OS_FIND_EXPORT(gx2Handle, GX2SetPixelUniformReg);
    OS_FIND_EXPORT(gx2Handle, GX2SetPixelTexture);
    OS_FIND_EXPORT(gx2Handle, GX2SetVertexTexture);
    OS_FIND_EXPORT(gx2Handle, GX2SetPixelSampler);
    OS_FIND_EXPORT(gx2Handle, GX2SetVertexSampler);
    OS_FIND_EXPORT(gx2Handle, GX2SetPixelShader);
    OS_FIND_EXPORT(gx2Handle, GX2SetVertexShader);
    OS_FIND_EXPORT(gx2Handle, GX2InitSamplerZMFilter);
    OS_FIND_EXPORT(gx2Handle, GX2SetColorControl);
    OS_FIND_EXPORT(gx2Handle, GX2SetDepthOnlyControl);
    OS_FIND_EXPORT(gx2Handle, GX2SetBlendControl);
    OS_FIND_EXPORT(gx2Handle, GX2CalcDRCSize);
    OS_FIND_EXPORT(gx2Handle, GX2SetDRCBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SetDRCScale);
    OS_FIND_EXPORT(gx2Handle, GX2SetDRCEnable);
    OS_FIND_EXPORT(gx2Handle, GX2SetPolygonControl);
    OS_FIND_EXPORT(gx2Handle, GX2SetCullOnlyControl);
    OS_FIND_EXPORT(gx2Handle, GX2SetDepthStencilControl);
    OS_FIND_EXPORT(gx2Handle, GX2SetStencilMask);
    OS_FIND_EXPORT(gx2Handle, GX2SetLineWidth);
    OS_FIND_EXPORT(gx2Handle, GX2SetDRCGamma);
    OS_FIND_EXPORT(gx2Handle, GX2SetTVGamma);
    OS_FIND_EXPORT(gx2Handle, GX2SetTVScale);
    OS_FIND_EXPORT(gx2Handle, GX2GetSystemTVScanMode);
    OS_FIND_EXPORT(gx2Handle, GX2GetSystemDRCScanMode);
    OS_FIND_EXPORT(gx2Handle, GX2RSetAllocator);
    OS_FIND_EXPORT(gx2Handle, GX2CopySurface);
    OS_FIND_EXPORT(gx2Handle, GX2GetLastFrame);
    OS_FIND_EXPORT(gx2Handle, GX2ClearBuffersEx);
    OS_FIND_EXPORT(gx2Handle, GX2BeginDisplayListEx);
    OS_FIND_EXPORT(gx2Handle, GX2EndDisplayList);
    OS_FIND_EXPORT(gx2Handle, GX2CallDisplayList);
    OS_FIND_EXPORT(gx2Handle, GX2ExpandAAColorBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2ResolveAAColorBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SetClearDepthStencil);
    OS_FIND_EXPORT(gx2Handle, GX2RCreateBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2RDestroyBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RLockBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RUnlockBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RSetAttributeBuffer);
}
