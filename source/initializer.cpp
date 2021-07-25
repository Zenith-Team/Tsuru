#include "log.h"
#include "config"
#include "types.h"
#include "dynlibs/os/functions.h"

typedef void (*InitFunc)();
extern "C" InitFunc _ctors[];

OsSpecifics osSpecifics;

extern "C" {
    extern u32 BLOSDynLoad_Acquire;
    extern u32 BOSDynLoad_FindExport;
}

void initialize() {
    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;

    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    OS_SPECIFICS->addr_OSDynLoad_Acquire    = (u32)(BLOSDynLoad_Acquire   & 0x03FFFFFC);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = (u32)(BOSDynLoad_FindExport & 0x03FFFFFC);

    if (!(BLOSDynLoad_Acquire & 2))
        OS_SPECIFICS->addr_OSDynLoad_Acquire    += (u32)&BLOSDynLoad_Acquire;
    if (!(BOSDynLoad_FindExport & 2))
        OS_SPECIFICS->addr_OSDynLoad_FindExport += (u32)&BOSDynLoad_FindExport;

// Init libraries
    InitOSFunctionPointers();

#if DEBUG == 1
    LOG("OSDynLoad_Acquire address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_Acquire);
    LOG("OSDynLoad_FindExport address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_FindExport);
#endif
}
