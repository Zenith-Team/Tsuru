#include <log.h>
#include <types.h>
#include <dynlibs/os/functions.h>
#include <dynlibs/gx2/functions.h>
#include <sead.h>
#include <custom/shsavemgr.h>

// staticInit array
typedef void (*funcPtr)();
extern "C" funcPtr _ctors[];

// RPL loading dependencies
OsSpecifics osSpecifics;
extern u32 BLOSDynLoad_Acquire;
extern u32 BOSDynLoad_FindExport;

void initialize() {
    // Duplicate call check
    static bool initialized = false;
    if (initialized)
        return;
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
}
