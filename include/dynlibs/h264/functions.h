#ifndef __H264_FUNCTIONS_H_
#define __H264_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dynlibs/h264/types.h"

void InitH264FunctionPointers(void);
void InitAcquireH264(void);

extern s32 (*H264DECInitParam)(s32 memSize, void* memPtr);
extern s32 (*H264DECSetParam)(void* memPtr, s32 paramID, void* param);
extern s32 (*H264DECOpen)(void* memPtr);
extern s32 (*H264DECBegin)(void* memPtr);
extern s32 (*H264DECSetBitstream)(void* memPtr, const u8* bitstream, const s32 length, const f64 timeStamp);
extern s32 (*H264DECExecute)(void* memPtr, void* strFmPtr);
extern s32 (*H264DECFlush)(void* memPtr);
extern s32 (*H264DECEnd)(void* memPtr);
extern s32 (*H264DECClose)(void* memPtr);
extern s32 (*H264DECMemoryRequirement)(s32 profile, s32 level, s32 maxWidth, s32 maxHeight, s32* codecMemSize);
extern s32 (*H264DECGetImageSize)(const u8* buffer, s32 totalBytes, s32 streamOffset, s32* width, s32* height);
extern s32 (*H264DECFindDecstartpoint)(const u8* buffer, s32 totalBytes, s32* streamOffset);
extern s32 (*H264DECFindIdrpoint)(const u8* buffer, s32 totalBytes, s32* streamOffset);
extern s32 (*H264DECCheckDecunitLength)(void* memPtr, const u8* buffer, s32 totalBytes, s32 streamOffset, s32* length);
extern s32 (*H264DECCheckMemSegmentation)(void* memPtr, u32 size);
extern s32 (*H264DECCheckSkipableFrame)(const u8* buffer, s32 length, s32* skipFlag);

#ifdef __cplusplus
}
#endif

#endif // __H264_FUNCTIONS_H_
