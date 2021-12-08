#include "log.h"
#include "types.h"
#include "dynlibs/os/functions.h"
#include "dynlibs/gx2/functions.h"

// staticInit array
extern "C" funcPtr _ctors[];

// RPL loading dependencies
OsSpecifics osSpecifics;
extern u32 BLOSDynLoad_Acquire;
extern u32 BOSDynLoad_FindExport;

void render();

void initialize() {
    // Duplicate call check
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    // Call staticInit functions from _ctors array
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    // Set OSDynLoad_Acquire and OSDynLoad_FindExport
    OS_SPECIFICS->addr_OSDynLoad_Acquire    = (u32)(BLOSDynLoad_Acquire   & 0x03FFFFFC);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = (u32)(BOSDynLoad_FindExport & 0x03FFFFFC);

    if (!(BLOSDynLoad_Acquire & 2))
        OS_SPECIFICS->addr_OSDynLoad_Acquire    += (u32)&BLOSDynLoad_Acquire;
    if (!(BOSDynLoad_FindExport & 2))
        OS_SPECIFICS->addr_OSDynLoad_FindExport += (u32)&BOSDynLoad_FindExport;

    // Init RPL libraries
    InitOSFunctionPointers();
    InitGX2FunctionPointers();

    LOG("OSDynLoad_Acquire address: 0x%08X", OS_SPECIFICS->addr_OSDynLoad_Acquire);
    LOG("OSDynLoad_FindExport address: 0x%08X", OS_SPECIFICS->addr_OSDynLoad_FindExport);

    //render();
}

void render() {

    //! ------------------------------------------------------------
    //! Initialize GX2
    //! ------------------------------------------------------------

    void* cmdList = MEMAllocFromDefaultHeapEx(0x400000, GX2_COMMAND_BUFFER_ALIGNMENT);

    u32 initAttribs[] = {
        GX2_INIT_ATTRIB_CB_BASE, (u32)cmdList,
        GX2_INIT_ATTRIB_CB_SIZE, 0x400000,
        GX2_INIT_ATTRIB_ARGC, 0,
        GX2_INIT_ATTRIB_ARGV, 0,
        GX2_INIT_ATTRIB_NULL
    };

    GX2Init(initAttribs);

    s32 MEM1HeapHandle = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
    s32 ForegroundHeapHandle = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);

    u32 tvRenderMode = GX2_TV_RENDER_720;

    u32 tvScanBufferSize;
    s32 unk;
    GX2CalcTVSize(tvRenderMode, GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM, GX2_BUFFERING_DOUBLE, &tvScanBufferSize, &unk);

    void* tvScanBuffer = MEMAllocFromFrmHeapEx(ForegroundHeapHandle, tvScanBufferSize, GX2_COMMAND_BUFFER_ALIGNMENT);

    GX2Invalidate(GX2_INVALIDATE_CPU, tvScanBuffer, tvScanBufferSize);

    GX2SetTVBuffer(tvScanBuffer, tvScanBufferSize, tvRenderMode, GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM, GX2_BUFFERING_DOUBLE);
    GX2SetTVScale(1280, 720);

    //! ------------------------------------------------------------
    //! Prepare rendering
    //! ------------------------------------------------------------

    GX2ColorBuffer colorBuffer;

    colorBuffer.surface.dimension = GX2_SURFACE_DIM_2D;
    colorBuffer.surface.width = 1280;
    colorBuffer.surface.height = 720;
    colorBuffer.surface.depth = 1;
    colorBuffer.surface.mipSize = 1;
    colorBuffer.surface.format = GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM;
    colorBuffer.surface.aa = GX2_AA_MODE_1X;
    colorBuffer.surface.use = GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE_FTV;
    colorBuffer.surface.mipData = nullptr;
    colorBuffer.surface.tile = GX2_TILE_MODE_DEFAULT;
    colorBuffer.surface.swizzle = 0;
    colorBuffer.viewMip = 0;
    colorBuffer.viewFirstSlice = 0;
    colorBuffer.viewSlicesCount = 1;

    GX2CalcSurfaceSizeAndAlignment(&colorBuffer.surface);
    GX2InitColorBufferRegs(&colorBuffer);

    void* colorBufferImageData = MEMAllocFromFrmHeapEx(MEM1HeapHandle, colorBuffer.surface.imageSize, colorBuffer.surface.align);

    colorBuffer.surface.imageData = colorBufferImageData;

    GX2Texture tex;
    tex.viewFirstMip = 0;
    tex.viewMipsCount = 1;
    tex.viewFirstSlice = 0;
    tex.viewSlicesCount = 1;
    tex.componentSelector = 66051;
    tex.regs[0] = 66588449;
    tex.regs[1] = 1744830573;
    tex.regs[2] = 109608960;
    tex.regs[3] = 0;
    tex.regs[4] = 2147483888;
    tex.surface.dimension = GX2_SURFACE_DIM_2D;
    tex.surface.width = 128;
    tex.surface.height = 110;
    tex.surface.depth = 1;
    tex.surface.numMips = 1;
    tex.surface.format = GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM;
    tex.surface.aa = GX2_AA_MODE_1X;
    tex.surface.use = GX2_SURFACE_USE_TEXTURE;
    tex.surface.imageSize = 57344;
    tex.surface.mipSize = 0;
    tex.surface.mipData = NULL;
    tex.surface.tile = GX2_TILE_MODE_2D_THIN1;
    tex.surface.swizzle = 851968;
    tex.surface.align = 2048;
    tex.surface.pitch = 128;
    for (u32 i = 0; i < 13; i++) tex.surface.mipOffset[i] = 0;

    //! ------------------------------------------------------------
    //! Setup context
    //! ------------------------------------------------------------

    GX2ContextState* context = (GX2ContextState*) MEMAllocFromDefaultHeapEx(sizeof(GX2ContextState), GX2_CONTEXT_STATE_ALIGNMENT);

    GX2SetupContextStateEx(context, false);

    GX2SetContextState(context);
    GX2SetColorBuffer(&colorBuffer, GX2_RENDER_TARGET_0);

    GX2SetSwapInterval(1);

    GX2SetViewport(0, 0, 1280, 720, 0.0f, 1.0f);
    GX2SetScissor(0, 0, 1280, 720);

    GX2SetDepthOnlyControl(false, false, GX2_COMPARE_LEQUAL);

    f32 r = 0.0f, rStep = 0.01;
    f32 g = 0.0f, gStep = 0.02;
    f32 b = 0.0f, bStep = 0.04;

    //! ------------------------------------------------------------
    //! Render loop
    //! ------------------------------------------------------------

    while (true) {

        // Animate colors
        r += rStep;
        g += gStep;
        b += bStep;

        if (r >= 1.0 || r <= 0.0) {
            rStep = -rStep;

            if (r > 1.0)
                r = 1.0;
            else if (r < 0.0)
                r = 0.0;
        }

        if (g >= 1.0 || g <= 0.0) {
            gStep = -gStep;

            if (g > 1.0)
                g = 1.0;
            else if (g < 0.0)
                g = 0.0;
        }

        if (b >= 1.0 || b <= 0.0) {
            bStep = -bStep;

            if (b > 1.0)
                b = 1.0;
            else if (b < 0.0)
                b = 0.0;
        }

        GX2ClearColor(&colorBuffer, r, g, b, 1.0f);

        // Make context current again
        GX2SetContextState(context);
        GX2SetColorBuffer(&colorBuffer, GX2_RENDER_TARGET_0);

        // Swap buffers
        GX2Flush();

        GX2CopyColorBufferToScanBuffer(&colorBuffer, GX2_SCAN_TARGET_TV);

        GX2SwapScanBuffers();

        GX2Flush();

        GX2SetTVEnable(true);


    }
}
