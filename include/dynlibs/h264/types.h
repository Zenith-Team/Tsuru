#ifndef __H264_TYPES_H_
#define __H264_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <dynlibs/os/types.h>

//!-----------------------------------------------------------------------------------------------------------------------
//! H264 params
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_PARAM_ID_FPTR_OUTPUT                    0x1
#define H264DEC_PARAM_ID_OUTPUT_PER_FRAME               0x20000002
#define H264DEC_PARAM_ID_USER_MEMORY                    0x70000001
                             
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 buffer output                             
//!-----------------------------------------------------------------------------------------------------------------------
#define BUFFERING_OUTPUT_PER_FRAME                      0x0
#define UNBUFFERING_OUTPUT_PER_FRAME                    0x01
                                     
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 alignment                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_ALIGN_PITCH_IN_PIXELS(pitch)            (pitch + 0xFF) & ~0xFF
#define H264DEC_BUFFER_ALIGNMENT                        0x100
                             
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 profiles                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264_BASELINE_PROFILE                           0x42
#define H264_MAIN_PROFILE                               0x4D
#define H264_HIGH_PROFILE                               0x64
                                
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 errors                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_ERROR_STREAM                            0x1000000
#define H264DEC_ERROR_PROFILE                           0x1080000
#define H264DEC_ERROR_NODATA                            0x1100000
#define H264DEC_ERROR_NOTSUPPORTED                      0x1180000
#define H264DEC_ERROR_PARAM                             0x1010000
#define H264DEC_ERROR_OUTOFMEMORY                       0x1020000
#define H264DEC_ERROR_INTERNAL                          0x1030000
#define H264DEC_ERROR_SEQUENCE                          0x1050000
#define H264DEC_ERROR_MEMSEGMENT                        0x1060000
#define H264DEC_ERROR_MAX_SIZE                          0x1070000
#define H264DEC_ERROR_BUFFEREMPTY                       0x80000
#define H264DEC_ERROR_USE_FM                            0x80
#define H264DEC_ERROR_FM_STAT                           0xFF

typedef struct _VUIParameters {
    u8 aspectRatioInfoPresentFlag;
    u8 aspectRatioIdc;
    s16 sarWidth;
    s16 sarHeight;
    u8 overscanInfoPresentFlag;
    u8 overscanAppropriateFlag;
    u8 videoSignalTypePresentFlag;
    u8 videoFormat;
    u8 videoFullRangeFlag;
    u8 colorDescriptionPresentFlag;
    u8 colorPrimaries;
    u8 transferCharacteristics;
    u8 matrixCoefficients;
    u8 chromaLocInfoPresentFlag;
    u8 chromaSampleLocTypeTop;
    u8 chromaSampleLocTypeBottom;
    u8 timingInfoPresentFlag;
    u32 unitsPerTick;
    u32 timescale;
    u8 fixedFramerateFlag;
    u8 nalHrdParamsPresentFlag;
    u8 vclHrdParametersPresentFlag;
    u8 lowDelayHrdFlag;
    u8 picStructPresentFlag;
    u8 bitstreamRestrictionFlag;
    u8 motionVectorsOverPicBoundariesFlag;
    s16 maxBytesPerPicDenom;
    s16 maxBitsPerMBDenom;
    s16 log2MaxMovieLengthHorizontal;
    s16 log2MaxMovieLengthVertical;
    s16 numReorderFrames;
    s16 maxDecFrameBuffering;
} VUIParameters;

typedef struct _H264DECResult {
    s32 decStatus;
    f64 timeStamp;
    s32 resultWidth;
    s32 resultHeight;
    s32 nextLine;
    u8 cropEnableFlag;
    s32 topCrop;
    s32 bottomCrop;
    s32 leftCrop;
    s32 rightCrop;
    u8 panScanEnableFlag;
    s32 topPanScan;
    s32 bottomPanScan;
    s32 leftPanScan;
    s32 rightPanScan;
    void* result;
    u8 vuiParametersPresentFlag;
    VUIParameters* VUIparameters;
    s32 reserved[10];
} H264DECResult;

typedef struct _H264DECOutput {
    s32 frameCount;
    H264DECResult** decodeResPtr;
    void* userMem;
} H264DECOutput;

#ifdef __cplusplus
}
#endif

#endif
