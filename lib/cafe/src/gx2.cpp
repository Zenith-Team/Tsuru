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
#include "sdk/os/functions.h"
#include "sdk/gx2/types.h"

u32 gx2Handle = 0;

EXPORT_DECL(void, GX2Init, u32 * init_attribs);
EXPORT_DECL(void, GX2Shutdown, void);
EXPORT_DECL(void, GX2Flush, void);
EXPORT_DECL(void, GX2ResetGPU, u32);
EXPORT_DECL(s32, GX2GetMainCoreId, void);
EXPORT_DECL(s32, GX2DrawDone, void);
EXPORT_DECL(void, GX2ClearColor, GX2ColorBuffer *colorBuffer, f32 r, f32 g, f32 b, f32 a);
EXPORT_DECL(void, GX2SetViewport, f32 x, f32 y, f32 w, f32 h, f32 nearZ, f32 farZ);
EXPORT_DECL(void, GX2SetScissor, u32 x_orig, u32 y_orig, u32 wd, u32 ht);
EXPORT_DECL(void, GX2SetContextState, const GX2ContextState* state);
EXPORT_DECL(void, GX2DrawEx, s32 primitive_type, u32 count, u32 first_vertex, u32 instances_count);
EXPORT_DECL(void, GX2DrawIndexedEx, s32 primitive_type, u32 count, s32 index_format, const void* idx, u32 first_vertex, u32 instances_count);
EXPORT_DECL(void, GX2ClearDepthStencilEx, GX2DepthBuffer *depthBuffer, f32 depth_value, u8 stencil_value, s32 clear_mode);
EXPORT_DECL(void, GX2SetClearDepthStencil, GX2DepthBuffer *depthBuffer, f32 depth_value, u8 stencil_value);
EXPORT_DECL(void, GX2CopyColorBufferToScanBuffer, const GX2ColorBuffer *colorBuffer, s32 scan_target);
EXPORT_DECL(void, GX2SwapScanBuffers, void);
EXPORT_DECL(void, GX2SetTVEnable, s32 enable);
EXPORT_DECL(void, GX2SetSwapInterval, u32 swap_interval);
EXPORT_DECL(u32, GX2GetSwapInterval, void);
EXPORT_DECL(void, GX2GetSwapStatus, u32 *swapCount, u32 *flipCount, OSTime *lastFlip, OSTime *lastVsync);
EXPORT_DECL(void, GX2WaitForVsync, void);
EXPORT_DECL(void, GX2CalcTVSize, s32 tv_render_mode, s32 format, s32 buffering_mode, u32 * size, s32 * scale_needed);
EXPORT_DECL(void, GX2Invalidate, s32 invalidate_type, void * ptr, u32 buffer_size);
EXPORT_DECL(void, GX2SetTVBuffer, void *buffer, u32 buffer_size, s32 tv_render_mode, s32 format, s32 buffering_mode);
EXPORT_DECL(void, GX2CalcSurfaceSizeAndAlignment, GX2Surface *surface);
EXPORT_DECL(void, GX2InitDepthBufferRegs, GX2DepthBuffer *depthBuffer);
EXPORT_DECL(void, GX2InitColorBufferRegs, GX2ColorBuffer *colorBuffer);
EXPORT_DECL(void, GX2CalcColorBufferAuxInfo, GX2ColorBuffer *colorBuffer, u32 *size, u32 *align);
EXPORT_DECL(void, GX2CalcDepthBufferHiZInfo, GX2DepthBuffer *depthBuffer, u32 *size, u32 *align);
EXPORT_DECL(void, GX2InitDepthBufferHiZEnable, GX2DepthBuffer *depthBuffer, s32 hiZ_enable);
EXPORT_DECL(void, GX2SetupContextStateEx, GX2ContextState* state, s32 enable_profiling);
EXPORT_DECL(void, GX2SetColorBuffer, const GX2ColorBuffer *colorBuffer, s32 target);
EXPORT_DECL(void, GX2SetDepthBuffer, const GX2DepthBuffer *depthBuffer);
EXPORT_DECL(void, GX2SetAttribBuffer, u32 attr_index, u32 attr_size, u32 stride, const void* attr);
EXPORT_DECL(void, GX2InitTextureRegs, GX2Texture *texture);
EXPORT_DECL(void, GX2InitSampler, GX2Sampler *sampler, s32 tex_clamp, s32 min_mag_filter);
EXPORT_DECL(void, GX2SetShaderModeEx, u32 mode, u32 num_vs_gpr, u32 num_vs_stack_entries, u32 num_gs_gpr, u32 num_gs_stack_entries, u32 num_ps_gpr, u32 num_ps_stack_entries);
EXPORT_DECL(u32, GX2CalcFetchShaderSizeEx, u32 num_attrib, s32 fetch_shader_type, s32 tessellation_mode);
EXPORT_DECL(void, GX2InitFetchShaderEx, GX2FetchShader* fs, void* fs_buffer, u32 count, const GX2AttribStream* attribs, s32 fetch_shader_type, s32 tessellation_mode);
EXPORT_DECL(void, GX2SetFetchShader, const GX2FetchShader* fs);
EXPORT_DECL(void, GX2SetVertexUniformReg, u32 offset, u32 count, const void *values);
EXPORT_DECL(void, GX2SetPixelUniformReg, u32 offset, u32 count, const void *values);
EXPORT_DECL(void, GX2SetPixelTexture, const GX2Texture *texture, u32 texture_hw_location);
EXPORT_DECL(void, GX2SetVertexTexture, const GX2Texture *texture, u32 texture_hw_location);
EXPORT_DECL(void, GX2SetPixelSampler, const GX2Sampler *sampler, u32 sampler_hw_location);
EXPORT_DECL(void, GX2SetVertexSampler, const GX2Sampler *sampler, u32 sampler_hw_location);
EXPORT_DECL(void, GX2SetPixelShader, const GX2PixelShader* pixelShader);
EXPORT_DECL(void, GX2SetVertexShader, const GX2VertexShader* vertexShader);
EXPORT_DECL(void, GX2InitSamplerZMFilter, GX2Sampler *sampler, s32 z_filter, s32 mip_filter);
EXPORT_DECL(void, GX2SetColorControl, s32 lop, u8 blend_enable_mask, s32 enable_multi_write, s32 enable_color_buffer);
EXPORT_DECL(void, GX2SetDepthOnlyControl, s32 enable_depth, s32 enable_depth_write, s32 depth_comp_function);
EXPORT_DECL(void, GX2SetBlendControl, s32 target, s32 color_src_blend, s32 color_dst_blend, s32 color_combine, s32 separate_alpha_blend, s32 alpha_src_blend, s32 alpha_dst_blend, s32 alpha_combine);
EXPORT_DECL(void, GX2CalcDRCSize, s32 drc_mode, s32 format, s32 buffering_mode, u32 *size, s32 *scale_needed);
EXPORT_DECL(void, GX2SetDRCBuffer, void *buffer, u32 buffer_size, s32 drc_mode, s32 surface_format, s32 buffering_mode);
EXPORT_DECL(void, GX2SetDRCScale, u32 width, u32 height);
EXPORT_DECL(void, GX2SetDRCEnable, s32 enable);
EXPORT_DECL(void, GX2SetPolygonControl, s32 front_face_mode, s32 cull_front, s32 cull_back, s32 enable_mode, s32 mode_font, s32 mode_back, s32 poly_offset_front, s32 poly_offset_back, s32 point_line_offset);
EXPORT_DECL(void, GX2SetCullOnlyControl, s32 front_face_mode, s32 cull_front, s32 cull_back);
EXPORT_DECL(void, GX2SetDepthStencilControl, s32 enable_depth_test, s32 enable_depth_write, s32 depth_comp_function,  s32 stencil_test_enable, s32 back_stencil_enable,
            s32 font_stencil_func, s32 front_stencil_z_pass, s32 front_stencil_z_fail, s32 front_stencil_fail,
            s32 back_stencil_func, s32 back_stencil_z_pass, s32 back_stencil_z_fail, s32 back_stencil_fail);
EXPORT_DECL(void, GX2SetStencilMask, u8 mask_front, u8 write_mask_front, u8 ref_front, u8 mask_back, u8 write_mask_back, u8 ref_back);
EXPORT_DECL(void, GX2SetLineWidth, f32 width);
EXPORT_DECL(void, GX2SetTVGamma, f32 val);
EXPORT_DECL(void, GX2SetTVScale, u32 x, u32 y);
EXPORT_DECL(void, GX2SetDRCGamma, f32 gam);
EXPORT_DECL(s32, GX2GetSystemTVScanMode, void);
EXPORT_DECL(s32, GX2GetSystemDRCScanMode, void);
EXPORT_DECL(void, GX2RSetAllocator, void * (* allocFunc)(u32, u32, u32), void (* freeFunc)(u32, void*));
EXPORT_DECL(void, GX2SetSurfaceSwizzle, GX2Surface * srcSurface,u32 swizzle );
EXPORT_DECL(void, GX2CopySurface, GX2Surface * srcSurface,u32 srcMip,u32 srcSlice,GX2Surface * dstSurface,u32 dstMip,u32 dstSlice );
EXPORT_DECL(s32, GX2GetLastFrame, s32 target, GX2Texture * texture);
EXPORT_DECL(void, GX2BeginDisplayListEx,void * displayList,u32 size,s32 unkwn);
EXPORT_DECL(u32, GX2EndDisplayList, void * list);
EXPORT_DECL(void, GX2DirectCallDisplayList, void * displayList,u32 size);
EXPORT_DECL(void, GX2CallDisplayList, void * list, u32 size);
EXPORT_DECL(void, GX2ExpandAAColorBuffer,GX2ColorBuffer * buffer);
EXPORT_DECL(void, GX2ExpandDepthBuffer, GX2DepthBuffer * buffer);
EXPORT_DECL(void, GX2ResolveAAColorBuffer, const GX2ColorBuffer * srcBuffer, GX2Surface * dstSurface,u32 dstMip,u32 dstSlice);
EXPORT_DECL(u32, GX2RCreateBuffer, GX2RBuffer * buffer);
EXPORT_DECL(void, GX2RDestroyBufferEx, GX2RBuffer * buffer, u32 flags);
EXPORT_DECL(void *, GX2RLockBufferEx, GX2RBuffer * buffer, u32 flags);
EXPORT_DECL(void, GX2RUnlockBufferEx, GX2RBuffer * buffer, u32 flags);
EXPORT_DECL(void, GX2RSetAttributeBuffer, GX2RBuffer * buffer, u32 index, u32 stride, u32 offset);
EXPORT_DECL(bool, GX2RDestroySurfaceEx, GX2Surface* surface, u32 flags);
EXPORT_DECL(void, GX2ClearBuffersEx, GX2ColorBuffer * colorBuffer,GX2DepthBuffer * depthBuffer,f32 r, f32 g, f32 b, f32 a,f32 depthValue,u8 stencilValue,s32 clearFlags);
EXPORT_DECL(bool, GX2RCreateSurface, GX2Surface* surface, u32 flags);
EXPORT_DECL(void*, GX2RLockSurfaceEx, GX2Surface* surface, int32_t level, u32 flags);
EXPORT_DECL(void, GX2RUnlockSurfaceEx, GX2Surface* surface, int32_t level, u32 flags);

void InitAcquireGX2(void) {
    if (coreinitHandle == 0) {
        InitAcquireOS();
    };
    OSDynLoad_Acquire("gx2.rpl", &gx2Handle);
}

extern "C" void InitGX2FunctionPointers(void) {
    u32 *funcPointer = 0;
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
    OS_FIND_EXPORT(gx2Handle, GX2SetSurfaceSwizzle);
    OS_FIND_EXPORT(gx2Handle, GX2CopySurface);
    OS_FIND_EXPORT(gx2Handle, GX2GetLastFrame);
    OS_FIND_EXPORT(gx2Handle, GX2ClearBuffersEx);
    OS_FIND_EXPORT(gx2Handle, GX2BeginDisplayListEx);
    OS_FIND_EXPORT(gx2Handle, GX2EndDisplayList);
    OS_FIND_EXPORT(gx2Handle, GX2DirectCallDisplayList);
    OS_FIND_EXPORT(gx2Handle, GX2CallDisplayList);
    OS_FIND_EXPORT(gx2Handle, GX2ExpandAAColorBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2ExpandDepthBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2ResolveAAColorBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2SetClearDepthStencil);
    OS_FIND_EXPORT(gx2Handle, GX2RCreateBuffer);
    OS_FIND_EXPORT(gx2Handle, GX2RDestroyBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RLockBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RUnlockBufferEx);
    OS_FIND_EXPORT(gx2Handle, GX2RSetAttributeBuffer);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RBufferExists);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RCreateBufferUserMemory);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RGetBufferAlignment);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RGetBufferAllocationSize);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RInvalidateBuffer);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RSetVertexUniformBlock);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RSetPixelUniformBlock);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RSetGeometryUniformBlock);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RBeginDisplayListEx);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2REndDisplayList);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RCallDisplayList);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RDirectCallDisplayList);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RDrawIndexed);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RInvalidateMemory);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RIsUserMemory);
    OS_FIND_EXPORT(gx2Handle, GX2RCreateSurface);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RCreateSurfaceUserMemory);
    OS_FIND_EXPORT(gx2Handle, GX2RDestroySurfaceEx);
    // TODO: OS_FIND_EXPORT(gx2Handle, GX2RInvalidateSurface);
    OS_FIND_EXPORT(gx2Handle, GX2RLockSurfaceEx);
    OS_FIND_EXPORT(gx2Handle, GX2RUnlockSurfaceEx);
}
