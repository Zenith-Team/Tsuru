#include "log.h"
#include "types.h"
#include "dynlibs/os/functions.h"
#include "dynlibs/gx2/functions.h"
#include "tsuru/save/system/savemgrsystem.h"

/*
    ______
   /_  __/______  _________  __
    / / / ___/ / / / ___/ / / /
   / / (___ ) /_/ / /  / /_/ /
  /_/ /____/\__,_/_/   \__,_/

      _              __             _                       _           _
     | |__ _  _     / /  __ ____ _ (_) __  __ ____ __   ___| |_    __ _| |
     | '_ \ || |   / /__/ // /  ' \/ / _ \/ // /\ \ /  / -_)  _|  / _` | |_
     |_.__/\_, |  /____/\_,_/_/_/_/_/_//_/\_, //_\_\   \___|\__|  \__,_|_(_)
            |__/                         /___/
*/

// staticInit array
extern "C" funcPtr _ctors[];

// RPL loading dependencies
OsSpecifics osSpecifics;
extern u32 BLOSDynLoad_Acquire;
extern u32 BOSDynLoad_FindExport;

void initialize() {
    // Duplicate call check
    static bool initialized = false;
    if (initialized) return;
    initialized = true;

    // Call staticInit functions from _ctors array
    for (s32 i = 0; _ctors[i]; i++)
        (*_ctors[i])();

    // Set OSDynLoad_Acquire and OSDynLoad_FindExport
    $(uintptr_t)(const u32* instr)(
        uintptr_t ret = *instr & 0x03FFFFFCU;

        if (!(*instr & 2)) {
            // sign extend offset
            if (ret & 0x02000000U)
            ret |= 0xFE000000U;

            // make relative
            ret += (uintptr_t)instr;
        }

        return ret;
    ) extractAddrFromInstr;
    OS_SPECIFICS->addr_OSDynLoad_Acquire = extractAddrFromInstr(&BLOSDynLoad_Acquire);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = extractAddrFromInstr(&BOSDynLoad_FindExport);

    // Init RPL libraries
    InitOSFunctionPointers();
    InitGX2FunctionPointers();

    PRINT("OSDynLoad_Acquire address: ", LogColor::Yellow, fmt::hex, OS_SPECIFICS->addr_OSDynLoad_Acquire);
    PRINT("OSDynLoad_FindExport address: ", LogColor::Yellow, fmt::hex, OS_SPECIFICS->addr_OSDynLoad_FindExport);

    PRINT(LogColor::Green, "Custom code initialization complete!");
}

void initialize2() {
    SaveMgrSystem::initSystem();
}

