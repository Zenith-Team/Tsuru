#pragma once

#include "dynlibs/gx2/types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 GFDGetPixelShaderCount(const void* file);

u32 GFDGetVertexShaderCount(const void* file);

u32 GFDGetPixelShaderHeaderSize(u32 index, const void* file);

u32 GFDGetPixelShaderProgramSize(u32 index, const void* file);

u32 GFDGetPixelShader(GX2PixelShader* shader, void* program, u32 index, const void* file);

u32 GFDGetVertexShaderHeaderSize(u32 index, const void* file);

u32 GFDGetVertexShaderProgramSize(u32 index, const void* file);

u32 GFDGetVertexShader(GX2VertexShader* shader, void* program, u32 index, const void* file);

#ifdef __cplusplus
}
#endif
