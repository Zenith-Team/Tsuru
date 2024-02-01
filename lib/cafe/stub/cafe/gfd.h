#pragma once

#include <cafe.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GFD_BLOCK_TYPE_HEADER                 0
#define GFD_BLOCK_TYPE_END                    1
#define GFD_BLOCK_TYPE_PAD                    2
#define GFD_BLOCK_TYPE_GX2_VSH_HEADER         3
#define GFD_BLOCK_TYPE_GX2_VSH_PROGRAM        5
#define GFD_BLOCK_TYPE_GX2_PSH_HEADER         6
#define GFD_BLOCK_TYPE_GX2_PSH_PROGRAM        7
#define GFD_BLOCK_TYPE_GX2_GSH_HEADER         8
#define GFD_BLOCK_TYPE_GX2_GSH_PROGRAM        9
#define GFD_BLOCK_TYPE_GX2_GSH_COPY_PROGRAM   10
#define GFD_BLOCK_TYPE_GX2_TEX_HEADER         11
#define GFD_BLOCK_TYPE_GX2_TEX_IMAGE          12
#define GFD_BLOCK_TYPE_GX2_TEX_MIP_IMAGE      13
#define GFD_BLOCK_TYPE_GX2_CSH_HEADER         14
#define GFD_BLOCK_TYPE_GX2_CSH_PROGRAM        15
#define GFD_BLOCK_TYPE_USER                   16

typedef struct _GFDHeader {
    u32 magic;
    u32 size;
    u32 majorVersion;
    u32 minorVersion;
    u32 gpuVersion;
    u32 alignMode;
    u32 reserved[2];
} GFDHeader;

typedef struct _GFDBlockHeader {
    u32 magic;
    u32 size;
    u32 majorVersion;
    u32 minorVersion;
    u32 type;
    u32 dataSize;
    u32 id;
    u32 typeIdx;
} GFDBlockHeader;

u32 _GFDCheckHeaderVersions(const void* file);
u32 _GFDCheckBlockHeaderMagicVersions(const GFDBlockHeader* header);
u32 _GFDRelocateBlock(u32 size, void* data);

u32 GFDGetVertexShaderCount(const void* file);
u32 GFDGetPixelShaderCount(const void* file);

u32 GFDGetVertexShaderHeaderSize(u32 index, const void* file);
u32 GFDGetVertexShaderProgramSize(u32 index, const void* file);
u32 GFDGetVertexShader(GX2VertexShader* shader, void* program, u32 index, const void* file);
GX2VertexShader* GFDGetVertexShaderPointer(u32 index, const void* file);

u32 GFDGetPixelShaderHeaderSize(u32 index, const void* file);
u32 GFDGetPixelShaderProgramSize(u32 index, const void* file);
u32 GFDGetPixelShader(GX2PixelShader* shader, void* program, u32 index, const void* file);
GX2PixelShader* GFDGetPixelShaderPointer(u32 index, const void* file);

#ifdef __cplusplus
}
#endif
