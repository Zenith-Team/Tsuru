#ifndef __H264_FUNCTIONS_H_
#define __H264_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "os_types.h"
#include "h264_types.h"

void InitH264FunctionPointers(void);
void InitAcquireH264(void);

extern s32 (* H264DECCheckMemSegmentation)(void*, u32);
extern s32 (* H264DECMemoryRequirement)(s32, s32, s32, s32, s32*);
extern s32 (* H264DECInitParam)(s32, void*);
extern s32 (* H264DECSetParam)(void*, s32, void*);
extern s32 (* H264DECOpen)(void*);
extern s32 (* H264DECBegin)(void*);
extern s32 (* H264DECExecute)(void*, void*);
extern s32 (* H264DECFlush)(void*);
extern s32 (* H264DECEnd)(void*);
extern s32 (* H264DECClose)(void*);
extern s32 (* H264DECFindDecstartpoint)(const u8*, s32, s32*);
extern s32 (* H264DECFindIdrpoint)(const u8*, s32, s32*);
extern s32 (* H264DECCheckDecunitLength)(void*, const u8*, s32, s32, s32*);
extern s32 (* H264DECGetImageSize)(const u8*, s32, s32, s32*, s32*);
extern s32 (* H264DECSetBitstream)(void*, const u8*, const s32, const f64);
extern s32 (* H264DECCheckSkipableFrame)(const u8*, s32, s32*);

extern s32 (* H264DECSetParam_FPTR_OUTPUT)(void*, int(*)(void*));
extern s32 (* H264DECSetParam_OUTPUT_PER_FRAME)(void*, int);
extern s32 (* H264DECSetParam_USER_MEMORY)(void*, void**);

#ifdef __cplusplus
}
#endif

#endif // __H264_FUNCTIONS_H_
