/****************************************************************************
 * Copyright (C) 2015
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#include <dynlibs/os/functions.h>

#ifdef Cemu
char logMsg[512];
#endif
u32 coreinitHandle = 0;

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Lib handle functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(s32, OSDynLoad_Acquire, const char* rpl, u32 *handle);
EXPORT_DECL(s32, OSDynLoad_FindExport, u32 handle, s32 isdata, const char *symbol, void *address);

EXPORT_DECL(void, OSDynLoad_Release, u32 handle);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Security functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(s32, OSGetSecurityLevel, void);
EXPORT_DECL(s32, OSForceFullRelaunch, void);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Thread functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(s32, OSCreateThread, OSThread *thread, s32 (*callback)(s32, void*), s32 argc, void *args, u32 stack, u32 stackSize, s32 priority, u32 attr);

EXPORT_DECL(void, OSEnableInterrupts, void);
EXPORT_DECL(void, __OSClearAndEnableInterrupt, void);
EXPORT_DECL(s32, OSIsInterruptEnabled, void);
EXPORT_DECL(s32, OSIsDebuggerPresent, void);
EXPORT_DECL(void, OSRestoreInterrupts, void);
EXPORT_DECL(void, OSSetDABR, s32, s32, s32, s32);
EXPORT_DECL(void, OSSetIABR, s32, s32);

EXPORT_DECL(s32, OSResumeThread, OSThread *thread);
EXPORT_DECL(s32, OSSuspendThread, OSThread *thread);
EXPORT_DECL(s32, OSIsThreadTerminated, OSThread *thread);
EXPORT_DECL(s32, OSIsThreadSuspended, OSThread *thread);
EXPORT_DECL(s32, OSSetThreadPriority, OSThread * thread, s32 priority);
EXPORT_DECL(s32, OSJoinThread, OSThread * thread, s32 * retVal);
EXPORT_DECL(void, OSDetachThread, OSThread * thread);
EXPORT_DECL(OSThread *,OSGetCurrentThread,void);
EXPORT_DECL(const char *,OSGetThreadName,OSThread * thread);
EXPORT_DECL(void ,OSGetActiveThreadLink,OSThread * thread, void* link);
EXPORT_DECL(u32 ,OSGetThreadAffinity,OSThread * thread);
EXPORT_DECL(s32 ,OSGetThreadPriority,OSThread * thread);
EXPORT_DECL(void ,OSSetThreadName,OSThread * thread, const char *name);
EXPORT_DECL(s32, OSGetCoreId, void);
EXPORT_DECL(void, OSSleepTicks, u64 ticks);
EXPORT_DECL(u64, OSGetTick, void);
EXPORT_DECL(u64, OSGetTime, void);
EXPORT_DECL(u64, OSGetSystemTime, void);
EXPORT_DECL(void, OSTicksToCalendarTime, u64 time, OSCalendarTime * calendarTime);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Message functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(void,OSInitMessageQueue,OSMessageQueue *queue, OSMessage *messages, s32 size);
EXPORT_DECL(u32,OSSendMessage,OSMessageQueue *queue, OSMessage *message, s32 flags);
EXPORT_DECL(u32,OSReceiveMessage,OSMessageQueue *queue, OSMessage *message, s32 flags);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Mutex functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(void, OSInitMutex, void* mutex);
EXPORT_DECL(void, OSLockMutex, void* mutex);
EXPORT_DECL(void, OSUnlockMutex, void* mutex);
EXPORT_DECL(s32, OSTryLockMutex, void* mutex);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! System functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(u64, OSGetTitleID, void);
EXPORT_DECL(void, OSGetArgcArgv, s32* argc, char*** argv);
EXPORT_DECL(void, __Exit, void);
EXPORT_DECL(void, OSFatal, const char* msg);
EXPORT_DECL(void, OSConsoleWrite, const char* msg, s32 size);
EXPORT_DECL(void*, OSSetExceptionCallback, u8 exceptionType, exception_callback newCallback);
EXPORT_DECL(void*, OSSetExceptionCallbackEx, s32 unkwn, u8 exceptionType, exception_callback newCallback);
EXPORT_DECL(void , OSLoadContext, OSContext* context);
EXPORT_DECL(void, DCFlushRange, const void* addr, u32 length);
EXPORT_DECL(void, DCStoreRange, const void* addr, u32 length);
EXPORT_DECL(void, ICInvalidateRange, const void* addr, u32 length);
EXPORT_DECL(void*, OSEffectiveToPhysical, const void*);
EXPORT_DECL(void*, __OSPhysicalToEffectiveUncached, const void*);
EXPORT_DECL(s32, __OSValidateAddressSpaceRange, s32, void*, s32);
EXPORT_DECL(s32, __os_snprintf, char* s, s32 n, const char* format, ...);
EXPORT_DECL(s32*, __gh_errno_ptr, void);

EXPORT_DECL(void, OSScreenInit, void);
EXPORT_DECL(void, OSScreenShutdown, void);
EXPORT_DECL(u32, OSScreenGetBufferSizeEx, u32 bufferNum);
EXPORT_DECL(s32, OSScreenSetBufferEx, u32 bufferNum, void* addr);
EXPORT_DECL(s32, OSScreenClearBufferEx, u32 bufferNum, u32 temp);
EXPORT_DECL(s32, OSScreenFlipBuffersEx, u32 bufferNum);
EXPORT_DECL(s32, OSScreenPutFontEx, u32 bufferNum, u32 posX, u32 posY, const char* buffer);
EXPORT_DECL(s32, OSScreenEnableEx, u32 bufferNum, s32 enable);
EXPORT_DECL(u32, OSScreenPutPixelEx, u32 bufferNum, u32 posX, u32 posY, u32 color);

EXPORT_DECL(void, DisassemblePPCRange, void*, void*, DisasmReport, DisasmGetSym, u32);
EXPORT_DECL(bool, DisassemblePPCOpcode, u32*, char*, u32, DisasmGetSym, u32);
EXPORT_DECL(void*, OSGetSymbolName, u32, u8*, u32);
EXPORT_DECL(void*, OSGetSymbolNameEx, u32, u8*, u32);
EXPORT_DECL(int, OSIsDebuggerInitialized, void);

EXPORT_DECL(bool, OSGetSharedData, u32 type, u32 unkR4, u8* addr, u32* size);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Memory functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_VAR(u32*, MEMAllocFromDefaultHeapExPtr);
EXPORT_VAR(u32*, MEMAllocFromDefaultHeapPtr);
EXPORT_VAR(u32*, MEMFreeToDefaultHeapPtr);

EXPORT_DECL(void*, MEMAllocFromAllocator, void* allocator, u32 size);
EXPORT_DECL(void, MEMFreeToAllocator, void* allocator, void* address);

EXPORT_DECL(s32, MEMGetBaseHeapHandle, s32 memArena);
EXPORT_DECL(u32, MEMGetTotalFreeSizeForExpHeap, s32 heap);
EXPORT_DECL(u32, MEMGetAllocatableSizeForExpHeapEx, s32 heap, s32 align);
EXPORT_DECL(u32, MEMGetAllocatableSizeForFrmHeapEx, s32 heap, s32 align);
EXPORT_DECL(void*, MEMAllocFromFrmHeapEx, s32 heap, u32 size, s32 align);
EXPORT_DECL(void, MEMFreeToFrmHeap, s32 heap, s32 mode);
EXPORT_DECL(u32, MEMFreeByStateToFrmHeap, s32 heap, u32 tag);
EXPORT_DECL(u32, MEMRecordStateForFrmHeap, s32 heap, u32 tag);
EXPORT_DECL(void*, MEMAllocFromExpHeapEx, s32 heap, u32 size, s32 align);
EXPORT_DECL(s32 , MEMCreateExpHeapEx, void* address, u32 size, unsigned short flags);
EXPORT_DECL(s32 , MEMCreateFrmHeapEx, void* address, u32 size, unsigned short flags);
EXPORT_DECL(void*, MEMDestroyExpHeap, s32 heap);
EXPORT_DECL(void, MEMFreeToExpHeap, s32 heap, void* ptr);
EXPORT_DECL(void*, OSAllocFromSystem, u32 size, s32 alignment);
EXPORT_DECL(void, OSFreeToSystem, void* addr);
EXPORT_DECL(s32, OSIsAddressValid, const void* ptr);
EXPORT_DECL(s32, MEMFindParentHeap, s32 heap);
EXPORT_DECL(s32, OSGetMemBound, s32 type, u32* startAddress, u32* size);
EXPORT_DECL(void*, OSBlockMove, void* dst, const void* src, size_t n, u32 flush);
EXPORT_DECL(void*, OSBlockSet, void* dst, u8 value, size_t n);


//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! MCP functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(s32, MCP_Open, void);
EXPORT_DECL(s32, MCP_Close, s32 handle);
EXPORT_DECL(s32, MCP_TitleCount, s32 handle);
EXPORT_DECL(s32, MCP_TitleList, s32 handle, s32 *res, void *data, s32 count);
EXPORT_DECL(s32, MCP_GetOwnTitleInfo, s32 handle, void *data);
EXPORT_DECL(void*, MCP_GetDeviceId, s32 handle, u32 * id);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Loader functions (not real rpl)
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(s32, LiWaitIopComplete, s32 unknownSyscallArgR3, s32 * remainingBytes);
EXPORT_DECL(s32, LiWaitIopCompleteWithInterrupts, s32 unknownSyscallArgR3, s32 * remainingBytes);
EXPORT_DECL(void, addr_LiWaitOneChunk, void);
EXPORT_DECL(void, addr_sgIsLoadingBuffer, void);
EXPORT_DECL(void, addr_gDynloadInitialized, void);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Kernel function addresses
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(void, addr_PrepareTitle_hook, void);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Other function addresses
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
EXPORT_DECL(void, DCInvalidateRange, void* buffer, u32 length);
EXPORT_DECL(s32, OSDynLoad_GetModuleName, s32 handle, char* nameBuffer, s32* nameBufferSize);
EXPORT_DECL(s32, OSIsHomeButtonMenuEnabled, void);
EXPORT_DECL(void, OSEnableHomeButtonMenu, s32);
EXPORT_DECL(s32, OSSetScreenCapturePermissionEx, s32 tvEnabled, s32 drcEnabled);


//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! Energy Saver functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Burn-in Reduction
EXPORT_DECL(s32, IMEnableDim,void);
EXPORT_DECL(s32, IMDisableDim,void);
EXPORT_DECL(s32, IMIsDimEnabled,s32* result);
//Auto power down
EXPORT_DECL(s32, IMEnableAPD,void);
EXPORT_DECL(s32, IMDisableAPD,void);
EXPORT_DECL(s32, IMIsAPDEnabled,s32 * result);
EXPORT_DECL(s32, IMIsAPDEnabledBySysSettings, s32* result);

EXPORT_DECL(s32, OSSendAppSwitchRequest, s32 param, void* unknown1, void* unknown2);

//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//! IOS functions
//!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

EXPORT_DECL(s32, IOS_Ioctl, s32 fd, u32 request, void* inputBuffer, u32 inputBufferLen, void* outputBuffer, u32 outputBufferLen);
EXPORT_DECL(s32, IOS_IoctlAsync, s32 fd, u32 request, void* inputBuffer, u32 inputBufferLen, void* outputBuffer, u32 outputBufferLen, void* cb, void* cbarg);
EXPORT_DECL(s32, IOS_Open, char* path, u32 mode);
EXPORT_DECL(s32, IOS_Close, s32 fd);

void _os_find_export(u32 handle, const char *funcName, void *funcPointer) {
    OSDynLoad_FindExport(handle, 0, funcName, funcPointer);

    if(!*(u32 *)funcPointer) {
        /*
         * This is effectively OSFatal("Function %s is NULL", funcName),
         * but we can't rely on any library functions like snprintf or
         * strcpy at this point.
         *
         * Buffer bounds are not checked. Beware!
         */
        char buf[256], *bufp = buf;
        const char a[] = "Function ", b[] = " is NULL", *p;
        unsigned int i;

        for (i = 0; i < sizeof(a) - 1; i++)
            *bufp++ = a[i];

        for (p = funcName; *p; p++)
            *bufp++ = *p;

        for (i = 0; i < sizeof(b) - 1; i++)
            *bufp++ = b[i];

        *bufp++ = '\0';

        OSFatal(buf);
    }
}

void InitAcquireOS(void) {
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Lib handle functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    EXPORT_FUNC_WRITE(OSDynLoad_Acquire, (s32 (*)(const char*, unsigned *))OS_SPECIFICS->addr_OSDynLoad_Acquire);
    EXPORT_FUNC_WRITE(OSDynLoad_FindExport, (s32 (*)(u32, s32, const char *, void *))OS_SPECIFICS->addr_OSDynLoad_FindExport);

    OSDynLoad_Acquire("coreinit.rpl", &coreinitHandle);
}

void InitOSFunctionPointers(void) {
    u32 *funcPointer = 0;

    InitAcquireOS();

    OS_FIND_EXPORT(coreinitHandle, OSDynLoad_Release);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Security functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    OS_FIND_EXPORT(coreinitHandle, OSGetSecurityLevel);
    OS_FIND_EXPORT(coreinitHandle, OSForceFullRelaunch);
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! System functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, OSFatal);
    OS_FIND_EXPORT(coreinitHandle, OSConsoleWrite);
    OS_FIND_EXPORT(coreinitHandle, OSGetTitleID);
    OS_FIND_EXPORT(coreinitHandle, OSGetArgcArgv);
    OS_FIND_EXPORT(coreinitHandle, OSSetExceptionCallback);
    OS_FIND_EXPORT(coreinitHandle, OSSetExceptionCallbackEx);
    OS_FIND_EXPORT(coreinitHandle, OSLoadContext);
    OS_FIND_EXPORT(coreinitHandle, DCFlushRange);
    OS_FIND_EXPORT(coreinitHandle, DCStoreRange);
    OS_FIND_EXPORT(coreinitHandle, ICInvalidateRange);
    OS_FIND_EXPORT(coreinitHandle, OSEffectiveToPhysical);
    OS_FIND_EXPORT(coreinitHandle, __OSPhysicalToEffectiveUncached);
    OS_FIND_EXPORT(coreinitHandle, __OSValidateAddressSpaceRange);
    OS_FIND_EXPORT(coreinitHandle, __os_snprintf);
    OS_FIND_EXPORT(coreinitHandle, __gh_errno_ptr);

    OSDynLoad_FindExport(coreinitHandle, 0, "_Exit", &__Exit);

    OS_FIND_EXPORT(coreinitHandle, OSScreenInit);
    OS_FIND_EXPORT(coreinitHandle, OSScreenShutdown);
    OS_FIND_EXPORT(coreinitHandle, OSScreenGetBufferSizeEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenSetBufferEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenClearBufferEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenFlipBuffersEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenPutFontEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenEnableEx);
    OS_FIND_EXPORT(coreinitHandle, OSScreenPutPixelEx);

    OS_FIND_EXPORT(coreinitHandle, DisassemblePPCRange);
    OS_FIND_EXPORT(coreinitHandle, DisassemblePPCOpcode);
    OS_FIND_EXPORT(coreinitHandle, OSGetSymbolName);
    OS_FIND_EXPORT(coreinitHandle, OSGetSymbolNameEx);
    OS_FIND_EXPORT(coreinitHandle, OSIsDebuggerInitialized);

    OS_FIND_EXPORT(coreinitHandle, OSGetSharedData);
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Thread functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, OSEnableInterrupts);
    OS_FIND_EXPORT(coreinitHandle, __OSClearAndEnableInterrupt);
    OS_FIND_EXPORT(coreinitHandle, OSIsInterruptEnabled);
    OS_FIND_EXPORT(coreinitHandle, OSIsDebuggerPresent);
    OS_FIND_EXPORT(coreinitHandle, OSRestoreInterrupts);
    OS_FIND_EXPORT(coreinitHandle, OSSetDABR);
    OS_FIND_EXPORT(coreinitHandle, OSSetIABR);

    OS_FIND_EXPORT(coreinitHandle, OSCreateThread);
    OS_FIND_EXPORT(coreinitHandle, OSResumeThread);
    OS_FIND_EXPORT(coreinitHandle, OSSuspendThread);
    OS_FIND_EXPORT(coreinitHandle, OSIsThreadTerminated);
    OS_FIND_EXPORT(coreinitHandle, OSIsThreadSuspended);
    OS_FIND_EXPORT(coreinitHandle, OSJoinThread);
    OS_FIND_EXPORT(coreinitHandle, OSSetThreadPriority);
    OS_FIND_EXPORT(coreinitHandle, OSDetachThread);
    OS_FIND_EXPORT(coreinitHandle, OSGetCurrentThread);
    OS_FIND_EXPORT(coreinitHandle, OSGetThreadName);
    OS_FIND_EXPORT(coreinitHandle, OSGetActiveThreadLink);
    OS_FIND_EXPORT(coreinitHandle, OSGetThreadAffinity);
    OS_FIND_EXPORT(coreinitHandle, OSGetThreadPriority);
    OS_FIND_EXPORT(coreinitHandle, OSSetThreadName);
    OS_FIND_EXPORT(coreinitHandle, OSGetCoreId);

    OS_FIND_EXPORT(coreinitHandle, OSSleepTicks);
    OS_FIND_EXPORT(coreinitHandle, OSGetTick);
    OS_FIND_EXPORT(coreinitHandle, OSGetTime);
    OS_FIND_EXPORT(coreinitHandle, OSGetSystemTime);
    OS_FIND_EXPORT(coreinitHandle, OSTicksToCalendarTime);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Message functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, OSInitMessageQueue);
    OS_FIND_EXPORT(coreinitHandle, OSSendMessage);
    OS_FIND_EXPORT(coreinitHandle, OSReceiveMessage);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Mutex functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, OSInitMutex);
    OS_FIND_EXPORT(coreinitHandle, OSLockMutex);
    OS_FIND_EXPORT(coreinitHandle, OSUnlockMutex);
    OS_FIND_EXPORT(coreinitHandle, OSTryLockMutex);
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! MCP functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, MCP_Open);
    OS_FIND_EXPORT(coreinitHandle, MCP_Close);
    OS_FIND_EXPORT(coreinitHandle, MCP_TitleCount);
    OS_FIND_EXPORT(coreinitHandle, MCP_TitleList);
    OS_FIND_EXPORT(coreinitHandle, MCP_GetOwnTitleInfo);
    OS_FIND_EXPORT(coreinitHandle, MCP_GetDeviceId);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Memory functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OSDynLoad_FindExport(coreinitHandle, 1, "MEMAllocFromDefaultHeapEx", &MEMAllocFromDefaultHeapExPtr);
    OSDynLoad_FindExport(coreinitHandle, 1, "MEMAllocFromDefaultHeap", &MEMAllocFromDefaultHeapPtr);
    OSDynLoad_FindExport(coreinitHandle, 1, "MEMFreeToDefaultHeap", &MEMFreeToDefaultHeapPtr);

    OS_FIND_EXPORT(coreinitHandle, MEMAllocFromAllocator);
    OS_FIND_EXPORT(coreinitHandle, MEMFreeToAllocator);
    OS_FIND_EXPORT(coreinitHandle, MEMGetBaseHeapHandle);
    OS_FIND_EXPORT(coreinitHandle, MEMGetTotalFreeSizeForExpHeap);
    OS_FIND_EXPORT(coreinitHandle, MEMGetAllocatableSizeForExpHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMGetAllocatableSizeForFrmHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMAllocFromFrmHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMFreeToFrmHeap);
    OS_FIND_EXPORT(coreinitHandle, MEMFreeByStateToFrmHeap);
    OS_FIND_EXPORT(coreinitHandle, MEMRecordStateForFrmHeap);
    OS_FIND_EXPORT(coreinitHandle, MEMAllocFromExpHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMCreateExpHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMCreateFrmHeapEx);
    OS_FIND_EXPORT(coreinitHandle, MEMDestroyExpHeap);
    OS_FIND_EXPORT(coreinitHandle, MEMFreeToExpHeap);
    OS_FIND_EXPORT(coreinitHandle, OSAllocFromSystem);
    OS_FIND_EXPORT(coreinitHandle, OSFreeToSystem);
    OS_FIND_EXPORT(coreinitHandle, OSIsAddressValid);
    OS_FIND_EXPORT(coreinitHandle, MEMFindParentHeap);
    OS_FIND_EXPORT(coreinitHandle, OSGetMemBound);
    OS_FIND_EXPORT(coreinitHandle, OSBlockMove);
    OS_FIND_EXPORT(coreinitHandle, OSBlockSet);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Other function addresses
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, DCInvalidateRange);
    OS_FIND_EXPORT(coreinitHandle, OSDynLoad_GetModuleName);
    OS_FIND_EXPORT(coreinitHandle, OSIsHomeButtonMenuEnabled);
    OS_FIND_EXPORT(coreinitHandle, OSEnableHomeButtonMenu);
    OS_FIND_EXPORT(coreinitHandle, OSSetScreenCapturePermissionEx);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! Energy Saver functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //Burn-in Reduction
    OS_FIND_EXPORT(coreinitHandle, IMEnableDim);
    OS_FIND_EXPORT(coreinitHandle, IMDisableDim);
    OS_FIND_EXPORT(coreinitHandle, IMIsDimEnabled);
    //Auto power down
    OS_FIND_EXPORT(coreinitHandle, IMEnableAPD);
    OS_FIND_EXPORT(coreinitHandle, IMDisableAPD);
    OS_FIND_EXPORT(coreinitHandle, IMIsAPDEnabled);
    OS_FIND_EXPORT(coreinitHandle, IMIsAPDEnabledBySysSettings);

    OS_FIND_EXPORT(coreinitHandle, OSSendAppSwitchRequest);

    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //! IOS functions
    //!----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    OS_FIND_EXPORT(coreinitHandle, IOS_Ioctl);
    OS_FIND_EXPORT(coreinitHandle, IOS_IoctlAsync);
    OS_FIND_EXPORT(coreinitHandle, IOS_Open);
    OS_FIND_EXPORT(coreinitHandle, IOS_Close);
}
