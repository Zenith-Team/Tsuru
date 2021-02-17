#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/zlib_functions.h"
#include "types.h"

#include "log.h"

typedef void (*InitFunc)();
extern "C" InitFunc _ctors[];

OsSpecifics osSpecifics;

extern "C"
{

extern u32 BLOSDynLoad_Acquire;
extern u32 BOSDynLoad_FindExport;

}

void callCtors()
{
    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    // Time to set addr_OSDynLoad_Acquire
    // and addr_OSDynLoad_FindExport
    OS_SPECIFICS->addr_OSDynLoad_Acquire    = (u32)(BLOSDynLoad_Acquire   & 0x03FFFFFC);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = (u32)(BOSDynLoad_FindExport & 0x03FFFFFC);

    if (!(BLOSDynLoad_Acquire   & 2))
        OS_SPECIFICS->addr_OSDynLoad_Acquire    += (u32)&BLOSDynLoad_Acquire;
    if (!(BOSDynLoad_FindExport & 2))
        OS_SPECIFICS->addr_OSDynLoad_FindExport += (u32)&BOSDynLoad_FindExport;

    // Init the libraries you need here
    InitOSFunctionPointers();
    InitZlibFunctionPointers();

    LOG("OSDynLoad_Acquire address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_Acquire);
    LOG("OSDynLoad_FindExport address: 0x%08X\n", OS_SPECIFICS->addr_OSDynLoad_FindExport);
}
