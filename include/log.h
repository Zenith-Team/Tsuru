#pragma once

#ifdef Cemu
#include "dynlibs/os/functions.h"
#define LOG(FMT, ...)  { __os_snprintf(logMsg, sizeof(logMsg), FMT, ## __VA_ARGS__); OSConsoleWrite(logMsg, sizeof(logMsg)); } (void)0
#else
#define LOG(FMT, ...) { ((void (*)(const char* format, ...))(*(unsigned int*)(DATA_ADDR - 4)))(FMT, ## __VA_ARGS__); } (void)0
#endif

const char* formatBool(bool value) {
    return value ? "true" : "false";
}

/* Specialized logging functions */

void LogGraphicsContext(volatile sead::GraphicsContext& gc) {
    LOG("------------------GraphicsContext------------------");
    LOG("  alphaTest: Enable(%s), Func(%d), Ref(%f)", formatBool(gc.alphaTestEnable), gc.alphaTestFunc, gc.alphaTestRef);
    LOG("  blendConstantColor: RGBA(%f, %f, %f, %f)", gc.blendConstantColor.r, gc.blendConstantColor.g, gc.blendConstantColor.b, gc.blendConstantColor.a);
    LOG("  blendEnable:    %s", formatBool(gc.blendEnable));
    LOG("  blendEquation:  RGB(%d), A(%d)", gc.blendEquationRGB, gc.blendEquationA);
    LOG("  blendFactorDst: RGB(%d), A(%d)", gc.blendFactorDstRGB, gc.blendFactorDstA);
    LOG("  blendFactorSrc: RGB(%d), A(%d)", gc.blendFactorSrcRGB, gc.blendFactorSrcA);
    LOG("  colorMask: RGBA(%s, %s, %s, %s)", formatBool(gc.colorMaskR), formatBool(gc.colorMaskG), formatBool(gc.colorMaskB), formatBool(gc.colorMaskA));
    LOG("  cullingMode: %d", gc.cullingMode);
    LOG("  depthFunc:   %d", gc.depthFunc);
    LOG("  depth(Test/Write)Enable: %s / %s", formatBool(gc.depthTestEnable), formatBool(gc.depthWriteEnable));
    LOG("  renderStatePolygonMode: Back(%d), Front(%d)", gc.renderState.polygonModeBack, gc.renderState.polygonModeFront);
    LOG("  renderStatePolyOffset(Back/Front)Enable: %d / %d", gc.renderState.polyOffsetBackEnable, gc.renderState.polyOffsetFrontEnable);
    LOG("  renderStatePolyLineOffsetEnable: %d", gc.renderState.polyLineOffsetEnable);
    LOG("  stencilOp: Fail(%d), ZFail(%d), ZPass(%d)", gc.stencilOpFail, gc.stencilOpZFail, gc.stencilOpZPass);
    LOG("  stencilTest: Enable(%s), Func(%d), Mask(%d), Ref(%d)", formatBool(gc.stencilTestEnable), gc.stencilTestFunc, gc.stencilTestMask, gc.stencilTestRef);
    LOG("---------------------------------------------------\n");
}
