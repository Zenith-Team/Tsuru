#pragma once

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _OsSpecifics {
    u32 addr_OSDynLoad_Acquire;
    u32 addr_OSDynLoad_FindExport;
    u32 addr_OSTitle_main_entry;

    u32 addr_KernSyscallTbl1;
    u32 addr_KernSyscallTbl2;
    u32 addr_KernSyscallTbl3;
    u32 addr_KernSyscallTbl4;
    u32 addr_KernSyscallTbl5;
} OsSpecifics;

typedef struct _s_mem_area {
    u32        address;
    u32        size;
    struct _s_mem_area* next;
} s_mem_area;

#ifdef __cplusplus
}
#endif
