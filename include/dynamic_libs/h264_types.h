#ifndef __H264_TYPES_H_
#define __H264_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "os_types.h"

//!-----------------------------------------------------------------------------------------------------------------------
//! H264 params
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_PARAM_ID_FPTR_OUTPUT                    0x00000001
#define H264DEC_PARAM_ID_OUTPUT_PER_FRAME               0x20000002
#define H264DEC_PARAM_ID_USER_MEMORY                    0x70000001
                             
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 buffer output                             
//!-----------------------------------------------------------------------------------------------------------------------
#define BUFFERING_OUTPUT_PER_FRAME                      0x00000000
#define UNBUFFERING_OUTPUT_PER_FRAME                    0x00000001
                                     
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 alignment                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_ALIGN_PITCH_IN_PIXELS(PitchInPixels)    ((PitchInPixels + 0xFF) & ~0xFF)
#define H264DEC_BUFFER_ALIGNMENT                        (256)
                             
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 profiles                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264_BASELINE_PROFILE                           66
#define H264_MAIN_PROFILE                               77
#define H264_HIGH_PROFILE                               100
                                
//!-----------------------------------------------------------------------------------------------------------------------
//! H264 errors                             
//!-----------------------------------------------------------------------------------------------------------------------
#define H264DEC_ERR_STREAM                              0x01000000
#define H264DEC_ERR_PROFILE                             0x01080000
#define H264DEC_ERR_NODATA                              0x01100000
#define H264DEC_ERR_NOTSUPPORTED                        0x01180000
#define H264DEC_ERR_PARAM                               0x01010000
#define H264DEC_ERR_OUTOFMEMORY                         0x01020000
#define H264DEC_ERR_INTERNAL                            0x01030000
#define H264DEC_ERR_SEQUENCE                            0x01050000
#define H264DEC_ERR_MEMSEGMENT                          0x01060000
#define H264DEC_ERR_MAX_SIZE                            0x01070000
#define H264DEC_ERR_BUFFEREMPTY                         0x00080000
#define H264DEC_ERR_USE_FM                              0x00000080
#define H264DEC_ERR_FM_STAT                             0x000000FF

typedef struct __VUI_PARAMETERS__ {
    u8 aspect_ratio_info_present_flag;
    u8 aspect_ratio_idc;
    s16 sar_width;
    s16 sar_height;
    u8 overscan_info_present_flag;
    u8 overscan_appropriate_flag;
    u8 video_signal_type_present_flag;
    u8 video_format;
    u8 video_full_range_flag;
    u8 colour_description_present_flag;
    u8 colour_primaries;
    u8 transfer_characteristics;
    u8 matrix_coefficients;
    u8 chroma_loc_info_present_flag;
    u8 chroma_sample_loc_type_top_side_field;
    u8 chroma_sample_loc_type_bottom_side_field;
    u8 timing_info_present_flag;
    u32 num_units_in_tick;
    u32 time_scale;
    u8 fixed_frame_rate_flag;
    u8 nal_hrd_params_present_flag;
    u8 vcl_hrd_params_present_flag;
    u8 low_delay_hrd_flag;
    u8 pic_struct_present_flag;
    u8 bitstream_restriction_flag;
    u8 motion_vectors_over_pic_boundaries_flag;
    s16 max_bytes_per_pic_denom;
    s16 max_bits_per_mb_denom;
    s16 log2_max_mv_length_horizontal;
    s16 log2_max_mv_length_vertical;
    s16 num_reorder_frames;
    s16 max_dec_frame_buffering;
} VUIParameters;

typedef struct __H264DEC_RESULT__ {
    s32 status;
    f64 timestamp;
    s32 result_width;
    s32 result_height;
    s32 line_next;
    u8 enable_crop_flag;
    s32 top_side_Crop;
    s32 bottom_side_Crop;
    s32 left_side_crop;
    s32 right_crop;
    u8 pan_scan_flag;
    s32 top_side_pan_scan;
    s32 bottom_side_pan_scan;
    s32 left_side_pan_scan;
    s32 right_side_pan_scan;
    void* result;
    u8 vui_params_present_flag;
    VUIParameters* VUI_params;
    s32 reserved[10];
} H264DECResult;

typedef struct __H264DEC_OUTPUT__ {
    s32 frame_count;
    H264DECResult** resptr;
    void* user_memory;
} H264DECOutput;


#ifdef __cplusplus
}
#endif

#endif // __H264_TYPES_H_
