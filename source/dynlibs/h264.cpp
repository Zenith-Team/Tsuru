#include <dynlibs/os/functions.h>
#include <dynlibs/h264/functions.h>

u32 h264Handle = 0;

EXPORT_DECL(s32, H264DECInitParam, s32 memSize, void* memPtr);
EXPORT_DECL(s32, H264DECSetParam, void* memPtr, s32 paramID, void* param);
EXPORT_DECL(s32, H264DECOpen, void* memPtr);
EXPORT_DECL(s32, H264DECBegin, void* memPtr);
EXPORT_DECL(s32, H264DECSetBitstream, void* memPtr, const u8* bitstream, const s32 length, const f64 timeStamp);
EXPORT_DECL(s32, H264DECExecute, void* memPtr, void* strFmPtr);
EXPORT_DECL(s32, H264DECFlush, void* memPtr);
EXPORT_DECL(s32, H264DECEnd, void* memPtr);
EXPORT_DECL(s32, H264DECClose, void* memPtr);
EXPORT_DECL(s32, H264DECMemoryRequirement, s32 profile, s32 level, s32 maxWidth, s32 maxHeight, s32* codecMemSize);
EXPORT_DECL(s32, H264DECGetImageSize, const u8* buffer, s32 totalBytes, s32 streamOffset, s32* width, s32* height);
EXPORT_DECL(s32, H264DECFindDecstartpoint, const u8* buffer, s32 totalBytes, s32* streamOffset);
EXPORT_DECL(s32, H264DECFindIdrpoint, const u8* buffer, s32 totalBytes, s32* streamOffset);
EXPORT_DECL(s32, H264DECCheckDecunitLength, void* memPtr, const u8* buffer, s32 totalBytes, s32 streamOffset, s32* length);
EXPORT_DECL(s32, H264DECCheckMemSegmentation, void* memPtr, u32 size);
EXPORT_DECL(s32, H264DECCheckSkipableFrame, const u8* buffer, s32 length, s32* skipFlag);

void InitAcquireH264(void) {
    if (coreinitHandle == 0)
        InitAcquireOS();

    OSDynLoad_Acquire("h264.rpl", &h264Handle);
}

extern "C" void InitH264FunctionPointers(void) {
    u32* funcPointer = 0;
    InitAcquireH264();

    OS_FIND_EXPORT(h264Handle, H264DECInitParam);
    OS_FIND_EXPORT(h264Handle, H264DECSetParam);
    OS_FIND_EXPORT(h264Handle, H264DECOpen);
    OS_FIND_EXPORT(h264Handle, H264DECBegin);
    OS_FIND_EXPORT(h264Handle, H264DECSetBitstream);
    OS_FIND_EXPORT(h264Handle, H264DECExecute);
    OS_FIND_EXPORT(h264Handle, H264DECFlush);
    OS_FIND_EXPORT(h264Handle, H264DECEnd);
    OS_FIND_EXPORT(h264Handle, H264DECClose);
    OS_FIND_EXPORT(h264Handle, H264DECMemoryRequirement);
    OS_FIND_EXPORT(h264Handle, H264DECGetImageSize);
    OS_FIND_EXPORT(h264Handle, H264DECFindDecstartpoint);
    OS_FIND_EXPORT(h264Handle, H264DECFindIdrpoint);
    OS_FIND_EXPORT(h264Handle, H264DECCheckDecunitLength);
    OS_FIND_EXPORT(h264Handle, H264DECCheckMemSegmentation);
    OS_FIND_EXPORT(h264Handle, H264DECCheckSkipableFrame);
}
