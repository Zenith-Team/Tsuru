#include <log.h>
#include <types.h>
#include <dynlibs/os/functions.h>
#include <dynlibs/gx2/functions.h>

#include "cheatmgr/cheatmgr.h"

// staticInit array
typedef void (*funcPtr)();
extern "C" funcPtr _ctors[];

// RPL loading dependencies
OsSpecifics osSpecifics;
extern u32 BLOSDynLoadAcquire;
extern u32 BOSDynLoadFindExport;

// Create custom singletons
CheatMgr CheatMgr::sInstance;

void initialize() {
    // Duplicate call check
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;

    // Call staticInit functions from _ctors array
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    // Set OSDynLoadAcquire and OSDynLoadFindExport
    OS_SPECIFICS->addrOSDynLoadAcquire    = (u32)(BLOSDynLoadAcquire   & 0x03FFFFFC);
    OS_SPECIFICS->addrOSDynLoadFindExport = (u32)(BOSDynLoadFindExport & 0x03FFFFFC);

    if (!(BLOSDynLoadAcquire & 2))
        OS_SPECIFICS->addrOSDynLoadAcquire    += (u32)&BLOSDynLoadAcquire;
    if (!(BOSDynLoadFindExport & 2))
        OS_SPECIFICS->addrOSDynLoadFindExport += (u32)&BOSDynLoadFindExport;

    // Init RPL libraries
    InitOSFunctionPointers();
    InitGX2FunctionPointers();

    if (CheatMgr::sInstance.mDebugLoggingEnabled) {
        LOG("OSDynLoadAcquire address: 0x%08X", OS_SPECIFICS->addrOSDynLoadAcquire);
        LOG("OSDynLoadFindExport address: 0x%08X", OS_SPECIFICS->addrOSDynLoadFindExport);
    }
}
