#pragma once

#include "dynlibs/gx2/functions.h"

/**
 * \defgroup whb_gfx Graphics
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WHBGfxShaderGroup WHBGfxShaderGroup;

struct WHBGfxShaderGroup {
    GX2FetchShader fetchShader;
    void* fetchShaderProgram;
    GX2PixelShader* pixelShader;
    GX2VertexShader* vertexShader;
    uint32_t numAttributes;
    GX2AttribStream attributes[16];
};

bool WHBGfxInit();

void WHBGfxShutdown();

void WHBGfxBeginRender();

void WHBGfxFinishRender();

void WHBGfxClearColor(float r, float g, float b, float a);

void WHBGfxBeginRenderDRC();

void WHBGfxFinishRenderDRC();

void WHBGfxBeginRenderTV();

void WHBGfxFinishRenderTV();

GX2PixelShader*
WHBGfxLoadGFDPixelShader(uint32_t index,
    const void* file);

bool WHBGfxFreePixelShader(GX2PixelShader* shader);

GX2VertexShader*
WHBGfxLoadGFDVertexShader(uint32_t index,
    const void* file);

bool WHBGfxFreeVertexShader(GX2VertexShader* shader);

bool WHBGfxLoadGFDShaderGroup(WHBGfxShaderGroup* group,
    uint32_t index,
    const void* file);

bool WHBGfxInitShaderAttribute(WHBGfxShaderGroup* group,
    const char* name,
    uint32_t buffer,
    uint32_t offset,
    s32 format);

bool WHBGfxInitFetchShader(WHBGfxShaderGroup* group);

bool WHBGfxFreeShaderGroup(WHBGfxShaderGroup* group);

GX2Texture*
WHBGfxLoadGFDTexture(uint32_t index,
    const void* file);

bool WHBGfxFreeTexture(GX2Texture* texture);

GX2ColorBuffer*
WHBGfxGetTVColourBuffer();

GX2DepthBuffer*
WHBGfxGetTVDepthBuffer();

GX2ContextState*
WHBGfxGetTVContextState();

GX2ColorBuffer*
WHBGfxGetDRCColourBuffer();

GX2DepthBuffer*
WHBGfxGetDRCDepthBuffer();

GX2ContextState*
WHBGfxGetDRCContextState();

#ifdef __cplusplus
}
#endif

/** @} */
