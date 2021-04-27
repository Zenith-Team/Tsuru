#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/h264_functions.h"

u32 h264_handle = 0;

EXPORT_DECL(s32, H264DECCheckMemSegmentation, void*, u32);
EXPORT_DECL(s32, H264DECMemoryRequirement, s32, s32, s32, s32, s32*);
EXPORT_DECL(s32, H264DECInitParam, s32, void*);
EXPORT_DECL(s32, H264DECSetParam, void*, s32, void*);
EXPORT_DECL(s32, H264DECOpen, void*);
EXPORT_DECL(s32, H264DECBegin, void*);
EXPORT_DECL(s32, H264DECExecute, void*, void*);
EXPORT_DECL(s32, H264DECFlush, void*);
EXPORT_DECL(s32, H264DECEnd, void*);
EXPORT_DECL(s32, H264DECClose, void*);
EXPORT_DECL(s32, H264DECFindDecstartpoint, const u8*, s32, s32*);
EXPORT_DECL(s32, H264DECFindIdrpoint, const u8*, s32, s32*);
EXPORT_DECL(s32, H264DECCheckDecunitLength, void*, const u8*, s32, s32, s32*);
EXPORT_DECL(s32, H264DECGetImageSize, const u8*, s32, s32, s32*, s32*);
EXPORT_DECL(s32, H264DECSetBitstream, void*, const u8*, const s32, const f64);
EXPORT_DECL(s32, H264DECCheckSkipableFrame, const u8*, s32, s32*);

EXPORT_DECL(s32, H264DECSetParam_FPTR_OUTPUT, void*, int(*)(void*));
EXPORT_DECL(s32, H264DECSetParam_OUTPUT_PER_FRAME, void*, int);
EXPORT_DECL(s32, H264DECSetParam_USER_MEMORY, void*, void**);

void InitAcquireH264(void) {
    if (coreinit_handle == 0) {
        InitAcquireOS();
    };
    OSDynLoad_Acquire("h264.rpl", &h264_handle);
}

void InitH264FunctionPointers(void) {
    u32* funcPointer = 0;
    InitAcquireH264();

    OS_FIND_EXPORT(h264_handle, H264DECCheckMemSegmentation);
    OS_FIND_EXPORT(h264_handle, H264DECMemoryRequirement);
    OS_FIND_EXPORT(h264_handle, H264DECInitParam);
    OS_FIND_EXPORT(h264_handle, H264DECSetParam);
    OS_FIND_EXPORT(h264_handle, H264DECOpen);
    OS_FIND_EXPORT(h264_handle, H264DECBegin);
    OS_FIND_EXPORT(h264_handle, H264DECExecute);
    OS_FIND_EXPORT(h264_handle, H264DECFlush);
    OS_FIND_EXPORT(h264_handle, H264DECEnd);
    OS_FIND_EXPORT(h264_handle, H264DECClose);
    OS_FIND_EXPORT(h264_handle, H264DECFindDecstartpoint);
    OS_FIND_EXPORT(h264_handle, H264DECFindIdrpoint);
    OS_FIND_EXPORT(h264_handle, H264DECCheckDecunitLength);
    OS_FIND_EXPORT(h264_handle, H264DECGetImageSize);
    OS_FIND_EXPORT(h264_handle, H264DECSetBitstream);
    OS_FIND_EXPORT(h264_handle, H264DECCheckSkipableFrame);

    OS_FIND_EXPORT(h264_handle, H264DECSetParam_FPTR_OUTPUT);
    OS_FIND_EXPORT(h264_handle, H264DECSetParam_OUTPUT_PER_FRAME);
    OS_FIND_EXPORT(h264_handle, H264DECSetParam_USER_MEMORY);
}
