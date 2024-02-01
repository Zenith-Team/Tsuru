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
#ifndef _GX2_TYPES_H_
#define _GX2_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk/os/types.h"

//!-----------------------------------------------------------------------------------------------------------------------
//! Constants
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_COMMAND_BUFFER_SIZE                         0x400000
#define GX2_COMMAND_BUFFER_ALIGNMENT                    0x40
#define GX2_SCAN_BUFFER_ALIGNMENT                       0x1000
#define GX2_SHADER_ALIGNMENT                            0x100
#define GX2_CONTEXT_STATE_ALIGNMENT                     0x100
#define GX2_DISPLAY_LIST_ALIGNMENT                      0x20
#define GX2_VERTEX_BUFFER_ALIGNMENT                     0x40
#define GX2_INDEX_BUFFER_ALIGNMENT                      0x20
#define GX2_UNIFORM_BLOCK_ALIGNMENT                     0x100
#define GX2_MAX_STREAMOUT_BUFFERS                       4

#define GX2_CONTEXT_STATE_SIZE                          0xA100
#define GX2_STREAMOUT_BUFFER_CONTEXT_SIZE               4

#define GX2_AUX_BUFFER_CLEAR_VALUE                      0xCC

#define GX2_NUM_VERTEX_SHADER_REGISTERS                 52
#define GX2_NUM_GEOMETRY_SHADER_REGISTERS               19
#define GX2_NUM_PIXEL_SHADER_REGISTERS                  41

#define GX2_NUM_FETCH_SHADER_REGISTERS                  1
#define GX2_NUM_LOOP_VAR_U32_WORDS                      2

//!-----------------------------------------------------------------------------------------------------------------------
//! Common
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2Boolean
{
    GX2_FALSE   = 0,
    GX2_TRUE    = 1,
    GX2_DISABLE = 0,
    GX2_ENABLE  = 1
} GX2Boolean;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2InitAttrib
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_INIT_ATTRIB_NULL                            0
#define GX2_INIT_ATTRIB_CB_BASE                         1
#define GX2_INIT_ATTRIB_CB_SIZE                         2
#define GX2_INIT_ATTRIB_ARGC                            7
#define GX2_INIT_ATTRIB_ARGV                            8

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 compare functions
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2CompareFunction
{
    GX2_COMPARE_NEVER       = 0x00000000,
    GX2_COMPARE_LESS        = 0x00000001,
    GX2_COMPARE_EQUAL       = 0x00000002,
    GX2_COMPARE_LEQUAL      = 0x00000003,
    GX2_COMPARE_GREATER     = 0x00000004,
    GX2_COMPARE_NOTEQUAL    = 0x00000005,
    GX2_COMPARE_GEQUAL      = 0x00000006,
    GX2_COMPARE_ALWAYS      = 0x00000007
} GX2CompareFunction;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 stencil functions
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2StencilFunction
{
    GX2_STENCIL_KEEP        = 0,
    GX2_STENCIL_ZERO        = 1,
    GX2_STENCIL_REPLACE     = 2,
    GX2_STENCIL_INCR        = 3,
    GX2_STENCIL_DECR        = 4,
    GX2_STENCIL_INVERT      = 5,
    GX2_STENCIL_INCR_WRAP   = 6,
    GX2_STENCIL_DECR_WRAP   = 7
} GX2StencilFunction;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 logic op functions
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2LogicOp
{
    GX2_LOGIC_OP_CLEAR      = 0x00,
    GX2_LOGIC_OP_NOR        = 0x11,
    GX2_LOGIC_OP_INVAND     = 0x22,
    GX2_LOGIC_OP_INVCOPY    = 0x33,
    GX2_LOGIC_OP_REVAND     = 0x44,
    GX2_LOGIC_OP_INV        = 0x55,
    GX2_LOGIC_OP_XOR        = 0x66,
    GX2_LOGIC_OP_NAND       = 0x77,
    GX2_LOGIC_OP_AND        = 0x88,
    GX2_LOGIC_OP_EQUIV      = 0x99,
    GX2_LOGIC_OP_NOOP       = 0xAA,
    GX2_LOGIC_OP_INVOR      = 0xBB,
    GX2_LOGIC_OP_COPY       = 0xCC,
    GX2_LOGIC_OP_REVOR      = 0xDD,
    GX2_LOGIC_OP_OR         = 0xEE,
    GX2_LOGIC_OP_SET        = 0xFF,
    GX2_LOGIC_OP_NONE       = GX2_LOGIC_OP_COPY
} GX2LogicOp;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 blend combination functions
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2BlendCombine
{
    GX2_BLEND_COMBINE_ADD           = 0x00,
    GX2_BLEND_COMBINE_SRC_MINUS_DST = 0x01,
    GX2_BLEND_COMBINE_MIN           = 0x02,
    GX2_BLEND_COMBINE_MAX           = 0x03,
    GX2_BLEND_COMBINE_DST_MINUS_SRC = 0x04
} GX2BlendCombine;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 blend functions
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2BlendFunction
{
    GX2_BLEND_ZERO                      = 0,
    GX2_BLEND_ONE                       = 1,
    GX2_BLEND_SRC_COLOR                 = 2,
    GX2_BLEND_ONE_MINUS_SRC_COLOR       = 3,
    GX2_BLEND_SRC_ALPHA                 = 4,
    GX2_BLEND_ONE_MINUS_SRC_ALPHA       = 5,
    GX2_BLEND_DST_ALPHA                 = 6,
    GX2_BLEND_ONE_MINUS_DST_ALPHA       = 7,
    GX2_BLEND_DST_COLOR                 = 8,
    GX2_BLEND_ONE_MINUS_DST_COLOR       = 9,
    GX2_BLEND_SRC_ALPHA_SATURATE        = 10,
    GX2_BLEND_CONSTANT_COLOR            = 13,
    GX2_BLEND_ONE_MINUS_CONSTANT_COLOR  = 14,
    GX2_BLEND_CONSTANT_ALPHA            = 19,
    GX2_BLEND_ONE_MINUS_CONSTANT_ALPHA  = 20
} GX2BlendFunction;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 render targets
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2RenderTarget
{
    GX2_RENDER_TARGET_0 = 0,
    GX2_RENDER_TARGET_1 = 1,
    GX2_RENDER_TARGET_2 = 2,
    GX2_RENDER_TARGET_3 = 3,
    GX2_RENDER_TARGET_4 = 4,
    GX2_RENDER_TARGET_5 = 5,
    GX2_RENDER_TARGET_6 = 6,
    GX2_RENDER_TARGET_7 = 7
} GX2RenderTarget;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 cull modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2FrontFaceMode
{
    GX2_FRONT_FACE_CCW  = 0,
    GX2_FRONT_FACE_CW   = 1
} GX2FrontFaceMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 polygon modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2PolygonMode
{
    GX2_POLYGON_MODE_POINT      = 0,
    GX2_POLYGON_MODE_LINE       = 1,
    GX2_POLYGON_MODE_TRIANGLE   = 2
} GX2PolygonMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 special states
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_SPECIAL_STATE_CLEAR                         0
#define GX2_SPECIAL_STATE_CLEAR_HIZ                     1
#define GX2_SPECIAL_STATE_COPY                          2
#define GX2_SPECIAL_STATE_EXPAND_COLOR                  3
#define GX2_SPECIAL_STATE_EXPAND_DEPTH                  4
#define GX2_SPECIAL_STATE_CONVERT_DEPTH                 5
#define GX2_SPECIAL_STATE_CONVERT_AADEPTH               6
#define GX2_SPECIAL_STATE_RESOLVE_COLOR                 7
#define GX2_SPECIAL_STATE_CLEAR_COLOR_AS_DEPTH          8

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 attribute formats
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2AttribFormat
{
    GX2_ATTRIB_FORMAT_8_UNORM                   = 0x00000000,
    GX2_ATTRIB_FORMAT_4_4_UNORM                 = 0x00000001,
    GX2_ATTRIB_FORMAT_16_UNORM                  = 0x00000002,
    GX2_ATTRIB_FORMAT_8_8_UNORM                 = 0x00000004,
    GX2_ATTRIB_FORMAT_16_16_UNORM               = 0x00000007,
    GX2_ATTRIB_FORMAT_8_8_8_8_UNORM             = 0x0000000A,
    GX2_ATTRIB_FORMAT_10_10_10_2_UNORM          = 0x0000000B,
    GX2_ATTRIB_FORMAT_16_16_16_16_UNORM         = 0x0000000E,

    GX2_ATTRIB_FORMAT_8_UINT                    = 0x00000100,
    GX2_ATTRIB_FORMAT_16_UINT                   = 0x00000102,
    GX2_ATTRIB_FORMAT_8_8_UINT                  = 0x00000104,
    GX2_ATTRIB_FORMAT_32_UINT                   = 0x00000105,
    GX2_ATTRIB_FORMAT_16_16_UINT                = 0x00000107,
    GX2_ATTRIB_FORMAT_8_8_8_8_UINT              = 0x0000010A,
    GX2_ATTRIB_FORMAT_10_10_10_2_UINT           = 0x0000010B,
    GX2_ATTRIB_FORMAT_32_32_UINT                = 0x0000010C,
    GX2_ATTRIB_FORMAT_16_16_16_16_UINT          = 0x0000010E,
    GX2_ATTRIB_FORMAT_32_32_32_UINT             = 0x00000110,
    GX2_ATTRIB_FORMAT_32_32_32_32_UINT          = 0x00000112,

    GX2_ATTRIB_FORMAT_8_SNORM                   = 0x00000200,
    GX2_ATTRIB_FORMAT_16_SNORM                  = 0x00000202,
    GX2_ATTRIB_FORMAT_8_8_SNORM                 = 0x00000204,
    GX2_ATTRIB_FORMAT_16_16_SNORM               = 0x00000207,
    GX2_ATTRIB_FORMAT_8_8_8_8_SNORM             = 0x0000020A,
    GX2_ATTRIB_FORMAT_10_10_10_2_SNORM          = 0x0000020B,
    GX2_ATTRIB_FORMAT_16_16_16_16_SNORM         = 0x0000020E,

    GX2_ATTRIB_FORMAT_8_SINT                    = 0x00000300,
    GX2_ATTRIB_FORMAT_16_SINT                   = 0x00000303,
    GX2_ATTRIB_FORMAT_8_8_SINT                  = 0x00000304,
    GX2_ATTRIB_FORMAT_32_SINT                   = 0x00000305,
    GX2_ATTRIB_FORMAT_16_16_SINT                = 0x00000307,
    GX2_ATTRIB_FORMAT_8_8_8_8_SINT              = 0x0000030A,
    GX2_ATTRIB_FORMAT_10_10_10_2_SINT           = 0x0000030B,
    GX2_ATTRIB_FORMAT_32_32_SINT                = 0x0000030C,
    GX2_ATTRIB_FORMAT_16_16_16_16_SINT          = 0x0000030E,
    GX2_ATTRIB_FORMAT_32_32_32_SINT             = 0x00000310,
    GX2_ATTRIB_FORMAT_32_32_32_32_SINT          = 0x00000312,

    GX2_ATTRIB_FORMAT_8_UINT_TO_FLOAT           = 0x00000800,
    GX2_ATTRIB_FORMAT_16_UINT_TO_FLOAT          = 0x00000802,
    GX2_ATTRIB_FORMAT_16_FLOAT                  = 0x00000803,
    GX2_ATTRIB_FORMAT_8_8_UINT_TO_FLOAT         = 0x00000804,
    GX2_ATTRIB_FORMAT_32_FLOAT                  = 0x00000806,
    GX2_ATTRIB_FORMAT_16_16_UINT_TO_FLOAT       = 0x00000807,
    GX2_ATTRIB_FORMAT_16_16_FLOAT               = 0x00000808,
    GX2_ATTRIB_FORMAT_10_11_11_FLOAT            = 0x00000809,
    GX2_ATTRIB_FORMAT_8_8_8_8_UINT_TO_FLOAT     = 0x0000080A,
    GX2_ATTRIB_FORMAT_32_32_FLOAT               = 0x0000080D,
    GX2_ATTRIB_FORMAT_16_16_16_16_UINT_TO_FLOAT = 0x0000080E,
    GX2_ATTRIB_FORMAT_16_16_16_16_FLOAT         = 0x0000080F,
    GX2_ATTRIB_FORMAT_32_32_32_FLOAT            = 0x00000811,
    GX2_ATTRIB_FORMAT_32_32_32_32_FLOAT         = 0x00000813,

    GX2_ATTRIB_FORMAT_8_SINT_TO_FLOAT           = 0x00000A00,
    GX2_ATTRIB_FORMAT_16_SINT_TO_FLOAT          = 0x00000A02,
    GX2_ATTRIB_FORMAT_8_8_SINT_TO_FLOAT         = 0x00000A04,
    GX2_ATTRIB_FORMAT_16_16_SINT_TO_FLOAT       = 0x00000A07,
    GX2_ATTRIB_FORMAT_8_8_8_8_SINT_TO_FLOAT     = 0x00000A0A,
    GX2_ATTRIB_FORMAT_16_16_16_16_SINT_TO_FLOAT = 0x00000A0E
} GX2AttribFormat;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 attribute index types
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2AttribIndexType
{
    GX2_ATTRIB_INDEX_VERTEX_ID      = 0,
    GX2_ATTRIB_INDEX_INSTANCE_ID    = 1
} GX2AttribIndexType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 shader modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2ShaderMode
{
    GX2_SHADER_MODE_UNIFORM_REGISTER    = 0,
    GX2_SHADER_MODE_UNIFORM_BLOCK       = 1,
    GX2_SHADER_MODE_GEOMETRY_SHADER     = 2,
    GX2_SHADER_MODE_COMPUTE_SHADER      = 3
} GX2ShaderMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 shader modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_COMP_SEL_NONE                               0x04040405
#define GX2_COMP_SEL_X001                               0x00040405
#define GX2_COMP_SEL_XY01                               0x00010405
#define GX2_COMP_SEL_XYZ1                               0x00010205
#define GX2_COMP_SEL_XYZW                               0x00010203
#define GX2_COMP_SEL_XXXX                               0x00000000
#define GX2_COMP_SEL_YYYY                               0x01010101
#define GX2_COMP_SEL_ZZZZ                               0x02020202
#define GX2_COMP_SEL_WWWW                               0x03030303
#define GX2_COMP_SEL_WZYX                               0x03020100
#define GX2_COMP_SEL_WXYZ                               0x03000102

#define GX2_SQ_SEL_R 0
#define GX2_SQ_SEL_G 1
#define GX2_SQ_SEL_B 2
#define GX2_SQ_SEL_A 3
#define GX2_COMP_MAP(x, y, z, w)                        (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 variable types
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_VAR_TYPE_VOID                               0
#define GX2_VAR_TYPE_BOOL                               1
#define GX2_VAR_TYPE_INT                                2
#define GX2_VAR_TYPE_UINT                               3
#define GX2_VAR_TYPE_FLOAT                              4
#define GX2_VAR_TYPE_DOUBLE                             5
#define GX2_VAR_TYPE_VEC2                               9
#define GX2_VAR_TYPE_VEC3                               10
#define GX2_VAR_TYPE_VEC4                               11
#define GX2_VAR_TYPE_MAT2                               21
#define GX2_VAR_TYPE_MAT3                               25
#define GX2_VAR_TYPE_MAT4                               29

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 sample types
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_SAMPLER_TYPE_2D                             1


//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 index formats
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2IndexFormat
{
    GX2_INDEX_FORMAT_U16    = 4,
    GX2_INDEX_FORMAT_U32    = 9
} GX2IndexFormat;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 primitive types
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2PrimitiveType
{
    GX2_PRIMITIVE_POINTS                              = 0x01,
    GX2_PRIMITIVE_LINES                               = 0x02,
    GX2_PRIMITIVE_LINE_STRIP                          = 0x03,
    GX2_PRIMITIVE_TRIANGLES                           = 0x04,
    GX2_PRIMITIVE_TRIANGLE_FAN                        = 0x05,
    GX2_PRIMITIVE_TRIANGLE_STRIP                      = 0x06,
    GX2_PRIMITIVE_RECTS                               = 0x11,
    GX2_PRIMITIVE_LINE_LOOP                           = 0x12,
    GX2_PRIMITIVE_QUADS                               = 0x13,
    GX2_PRIMITIVE_QUAD_STRIP                          = 0x14
} GX2PrimitiveType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 clear modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_CLEAR_DEPTH                                 0x01
#define GX2_CLEAR_STENCIL                               0x02
#define GX2_CLEAR_BOTH                                  (GX2_CLEAR_DEPTH | GX2_CLEAR_STENCIL)

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 surface formats
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2SurfaceFormat
{
    GX2_SURFACE_FORMAT_INVALID                  = 0x00000000,
    GX2_SURFACE_FORMAT_TC_R8_UNORM              = 0x00000001,
    GX2_SURFACE_FORMAT_T_R4_G4_UNORM            = 0x00000002,
    GX2_SURFACE_FORMAT_TCD_R16_UNORM            = 0x00000005,
    GX2_SURFACE_FORMAT_TC_R8_G8_UNORM           = 0x00000007,
    GX2_SURFACE_FORMAT_TCS_R5_G6_B5_UNORM       = 0x00000008,
    GX2_SURFACE_FORMAT_TC_R5_G5_B5_A1_UNORM     = 0x0000000a,
    GX2_SURFACE_FORMAT_TC_R4_G4_B4_A4_UNORM     = 0x0000000b,
    GX2_SURFACE_FORMAT_TC_A1_B5_G5_R5_UNORM     = 0x0000000c,
    GX2_SURFACE_FORMAT_TC_R16_G16_UNORM         = 0x0000000f,
    GX2_SURFACE_FORMAT_D_D24_S8_UNORM           = 0x00000011,
    GX2_SURFACE_FORMAT_T_R24_UNORM_X8           = 0x00000011,
    GX2_SURFACE_FORMAT_TCS_R10_G10_B10_A2_UNORM = 0x00000019,
    GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_UNORM    = 0x0000001a,
    GX2_SURFACE_FORMAT_TCS_A2_B10_G10_R10_UNORM = 0x0000001b,
    GX2_SURFACE_FORMAT_TC_R16_G16_B16_A16_UNORM = 0x0000001f,
    GX2_SURFACE_FORMAT_T_BC1_UNORM              = 0x00000031,
    GX2_SURFACE_FORMAT_T_BC2_UNORM              = 0x00000032,
    GX2_SURFACE_FORMAT_T_BC3_UNORM              = 0x00000033,
    GX2_SURFACE_FORMAT_T_BC4_UNORM              = 0x00000034,
    GX2_SURFACE_FORMAT_T_BC5_UNORM              = 0x00000035,
    GX2_SURFACE_FORMAT_T_NV12_UNORM             = 0x00000081,

    GX2_SURFACE_FORMAT_TC_R8_UINT               = 0x00000101,
    GX2_SURFACE_FORMAT_TC_R16_UINT              = 0x00000105,
    GX2_SURFACE_FORMAT_TC_R8_G8_UINT            = 0x00000107,
    GX2_SURFACE_FORMAT_TC_R32_UINT              = 0x0000010d,
    GX2_SURFACE_FORMAT_TC_R16_G16_UINT          = 0x0000010f,
    GX2_SURFACE_FORMAT_T_X24_G8_UINT            = 0x00000111,
    GX2_SURFACE_FORMAT_TC_R10_G10_B10_A2_UINT   = 0x00000119,
    GX2_SURFACE_FORMAT_TC_R8_G8_B8_A8_UINT      = 0x0000011a,
    GX2_SURFACE_FORMAT_TC_A2_B10_G10_R10_UINT   = 0x0000011b,
    GX2_SURFACE_FORMAT_T_X32_G8_UINT_X24        = 0x0000011c,
    GX2_SURFACE_FORMAT_TC_R32_G32_UINT          = 0x0000011d,
    GX2_SURFACE_FORMAT_TC_R16_G16_B16_A16_UINT  = 0x0000011f,
    GX2_SURFACE_FORMAT_TC_R32_G32_B32_A32_UINT  = 0x00000122,

    GX2_SURFACE_FORMAT_TC_R8_SNORM              = 0x00000201,
    GX2_SURFACE_FORMAT_TC_R16_SNORM             = 0x00000205,
    GX2_SURFACE_FORMAT_TC_R8_G8_SNORM           = 0x00000207,
    GX2_SURFACE_FORMAT_TC_R16_G16_SNORM         = 0x0000020f,
    GX2_SURFACE_FORMAT_T_R10_G10_B10_A2_SNORM   = 0x00000219,
    GX2_SURFACE_FORMAT_TC_R10_G10_B10_A2_SNORM  = 0x00000219,
    GX2_SURFACE_FORMAT_TC_R8_G8_B8_A8_SNORM     = 0x0000021a,
    GX2_SURFACE_FORMAT_TC_R16_G16_B16_A16_SNORM = 0x0000021f,
    GX2_SURFACE_FORMAT_T_BC4_SNORM              = 0x00000234,
    GX2_SURFACE_FORMAT_T_BC5_SNORM              = 0x00000235,

    GX2_SURFACE_FORMAT_TC_R8_SINT               = 0x00000301,
    GX2_SURFACE_FORMAT_TC_R16_SINT              = 0x00000305,
    GX2_SURFACE_FORMAT_TC_R8_G8_SINT            = 0x00000307,
    GX2_SURFACE_FORMAT_TC_R32_SINT              = 0x0000030d,
    GX2_SURFACE_FORMAT_TC_R16_G16_SINT          = 0x0000030f,
    GX2_SURFACE_FORMAT_TC_R10_G10_B10_A2_SINT   = 0x00000319,
    GX2_SURFACE_FORMAT_TC_R8_G8_B8_A8_SINT      = 0x0000031a,
    GX2_SURFACE_FORMAT_TC_R32_G32_SINT          = 0x0000031d,
    GX2_SURFACE_FORMAT_TC_R16_G16_B16_A16_SINT  = 0x0000031f,
    GX2_SURFACE_FORMAT_TC_R32_G32_B32_A32_SINT  = 0x00000322,

    GX2_SURFACE_FORMAT_TCS_R8_G8_B8_A8_SRGB     = 0x0000041a,
    GX2_SURFACE_FORMAT_T_BC1_SRGB               = 0x00000431,
    GX2_SURFACE_FORMAT_T_BC2_SRGB               = 0x00000432,
    GX2_SURFACE_FORMAT_T_BC3_SRGB               = 0x00000433,

    GX2_SURFACE_FORMAT_TC_R16_FLOAT             = 0x00000806,
    GX2_SURFACE_FORMAT_TCD_R32_FLOAT            = 0x0000080e,
    GX2_SURFACE_FORMAT_TC_R16_G16_FLOAT         = 0x00000810,
    GX2_SURFACE_FORMAT_D_D24_S8_FLOAT           = 0x00000811,
    GX2_SURFACE_FORMAT_TC_R11_G11_B10_FLOAT     = 0x00000816,
    GX2_SURFACE_FORMAT_D_D32_FLOAT_S8_UINT_X24  = 0x0000081c,
    GX2_SURFACE_FORMAT_T_R32_FLOAT_X8_X24       = 0x0000081c,
    GX2_SURFACE_FORMAT_TC_R32_G32_FLOAT         = 0x0000081e,
    GX2_SURFACE_FORMAT_TC_R16_G16_B16_A16_FLOAT = 0x00000820,
    GX2_SURFACE_FORMAT_TC_R32_G32_B32_A32_FLOAT = 0x00000823
} GX2SurfaceFormat;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 tile modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TileMode
{
    GX2_TILE_MODE_DEFAULT                             = 0x00000000,
    GX2_TILE_MODE_LINEAR_ALIGNED                      = 0x00000001
} GX2TileMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 surface use
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2SurfaceUse
{
    GX2_SURFACE_USE_TEXTURE                     = 0x00000001,
    GX2_SURFACE_USE_COLOR_BUFFER                = 0x00000002,
    GX2_SURFACE_USE_DEPTH_BUFFER                = 0x00000004,
    GX2_SURFACE_USE_SCAN_BUFFER                 = 0x00000008,
    GX2_SURFACE_USE_FTV                         = 0x80000000,
    GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE        = (GX2_SURFACE_USE_COLOR_BUFFER | GX2_SURFACE_USE_TEXTURE),
    GX2_SURFACE_USE_DEPTH_BUFFER_TEXTURE        = (GX2_SURFACE_USE_DEPTH_BUFFER | GX2_SURFACE_USE_TEXTURE),
    GX2_SURFACE_USE_COLOR_BUFFER_FTV            = (GX2_SURFACE_USE_COLOR_BUFFER | GX2_SURFACE_USE_FTV),
    GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE_FTV    = (GX2_SURFACE_USE_COLOR_BUFFER_TEXTURE | GX2_SURFACE_USE_FTV)
} GX2SurfaceUse;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 surface dim
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2SurfaceDim
{
    GX2_SURFACE_DIM_1D              = 0x00000000,
    GX2_SURFACE_DIM_2D              = 0x00000001,
    GX2_SURFACE_DIM_3D              = 0x00000002,
    GX2_SURFACE_DIM_CUBE            = 0x00000003,
    GX2_SURFACE_DIM_1D_ARRAY        = 0x00000004,
    GX2_SURFACE_DIM_2D_ARRAY        = 0x00000005,
    GX2_SURFACE_DIM_2D_MSAA         = 0x00000006,
    GX2_SURFACE_DIM_2D_MSAA_ARRAY   = 0x00000007
} GX2SurfaceDim;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 AA modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2AAMode
{
    GX2_AA_MODE_1X  = 0x00000000,
    GX2_AA_MODE_2X  = 0x00000001,
    GX2_AA_MODE_4X  = 0x00000002,
    GX2_AA_MODE_8X  = 0x00000003
} GX2AAMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 texture clamp
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TexClamp
{
    GX2_TEX_CLAMP_WRAP                      = 0x00000000,
    GX2_TEX_CLAMP_MIRROR                    = 0x00000001,
    GX2_TEX_CLAMP_CLAMP                     = 0x00000002,
    GX2_TEX_CLAMP_MIRROR_ONCE               = 0x00000003,
    GX2_TEX_CLAMP_CLAMP_HALF_BORDER         = 0x00000004,
    GX2_TEX_CLAMP_MIRROR_ONCE_HALF_BORDER   = 0x00000005,
    GX2_TEX_CLAMP_CLAMP_BORDER              = 0x00000006,
    GX2_TEX_CLAMP_MIRROR_ONCE_BORDER        = 0x00000007
} GX2TexClamp;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 texture border
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TexBorderType
{
    GX2_TEX_BORDER_CLEAR_BLACK  = 0x00000000,
    GX2_TEX_BORDER_SOLID_BLACK  = 0x00000001,
    GX2_TEX_BORDER_SOLID_WHITE  = 0x00000002,
    GX2_TEX_BORDER_USE_REGISTER = 0x00000003
} GX2TexBorderType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 texture filter
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TexXYFilterType
{
    GX2_TEX_XY_FILTER_POINT     = 0x00000000,
    GX2_TEX_XY_FILTER_BILINEAR  = 0x00000001
} GX2TexXYFilterType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 texture mip filter
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TexMipFilterType
{
    GX2_TEX_MIP_FILTER_NO_MIP   = 0x00000000,
    GX2_TEX_MIP_FILTER_POINT    = 0x00000001,
    GX2_TEX_MIP_FILTER_LINEAR   = 0x00000002
} GX2TexMipFilterType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 texture aniso ratio
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2TexAnisoRatio
{
    GX2_TEX_ANISO_1_TO_1    = 0x00000000,
    GX2_TEX_ANISO_2_TO_1    = 0x00000001,
    GX2_TEX_ANISO_4_TO_1    = 0x00000002,
    GX2_TEX_ANISO_8_TO_1    = 0x00000003,
    GX2_TEX_ANISO_16_TO_1   = 0x00000004
} GX2TexAnisoRatio;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 TV scan modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_TV_SCAN_MODE_NONE                           0x00000000
#define GX2_TV_SCAN_MODE_576I                           0x00000001
#define GX2_TV_SCAN_MODE_480I                           0x00000002
#define GX2_TV_SCAN_MODE_480P                           0x00000003
#define GX2_TV_SCAN_MODE_720P                           0x00000004
#define GX2_TV_SCAN_MODE_1080I                          0x00000006
#define GX2_TV_SCAN_MODE_1080P                          0x00000007

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 TV render modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_TV_RENDER_480_NARROW                        0x00000001
#define GX2_TV_RENDER_480_WIDE                          0x00000002
#define GX2_TV_RENDER_720                               0x00000003
#define GX2_TV_RENDER_1080                              0x00000005

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 DRC render modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_DRC_NONE                                    0x00000000
#define GX2_DRC_SINGLE                                  0x00000001
#define GX2_DRC_DOUBLE                                  0x00000002
#define GX2_DRC_SINGLE_30HZ                             0x00000004

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 buffering mode
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_BUFFERING_SINGLE                            0x00000001
#define GX2_BUFFERING_DOUBLE                            0x00000002
#define GX2_BUFFERING_TRIPLE                            0x00000003
#define GX2_BUFFERING_QUAD
//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 scan targets
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2ScanTarget
{
    GX2_SCAN_TARGET_TV          = 0x00000001,
    GX2_SCAN_TARGET_DRC_FIRST   = 0x00000004,
    GX2_SCAN_TARGET_DRC_SECOND  = 0x00000008
} GX2ScanTarget;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 invalidate types
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_INVALIDATE_ATTRIB_BUFFER                    0x00000001
#define GX2_INVALIDATE_TEXTURE                          0x00000002
#define GX2_INVALIDATE_UNIFORM_BLOCK                    0x00000004
#define GX2_INVALIDATE_SHADER                           0x00000008
#define GX2_INVALIDATE_COLOR_BUFFER                     0x00000010
#define GX2_INVALIDATE_DEPTH_BUFFER                     0x00000020
#define GX2_INVALIDATE_CPU                              0x00000040
#define GX2_INVALIDATE_CPU_ATTRIB_BUFFER                (GX2_INVALIDATE_CPU | GX2_INVALIDATE_ATTRIB_BUFFER)
#define GX2_INVALIDATE_CPU_TEXTURE                      (GX2_INVALIDATE_CPU | GX2_INVALIDATE_TEXTURE)
#define GX2_INVALIDATE_CPU_UNIFORM_BLOCK                (GX2_INVALIDATE_CPU | GX2_INVALIDATE_UNIFORM_BLOCK)
#define GX2_INVALIDATE_CPU_SHADER                       (GX2_INVALIDATE_CPU | GX2_INVALIDATE_SHADER)

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 swap modes
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2EndianSwapMode {
    GX2_ENDIANSWAP_DEFAULT  = 0x00000003
} GX2EndianSwapMode;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 tessellation modes
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2_TESSELLATION_MODE_DISCRETE                  0x00000000
#define GX2_TESSELLATION_MODE_CONTINUOUS                0x00000001
#define GX2_TESSELLATION_MODE_ADAPTIVE                  0x00000002

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2 fetch shader types
//!-----------------------------------------------------------------------------------------------------------------------
typedef enum _GX2FetchShaderType {
    GX2_FETCH_SHADER_TESSELATION_NONE       = 0x00000000,
    GX2_FETCH_SHADER_TESSELATION_LINES      = 0x00000001,
    GX2_FETCH_SHADER_TESSELATION_TRIANGLES  = 0x00000002,
    GX2_FETCH_SHADER_TESSELATION_QUADS      = 0x00000003
} GX2FetchShaderType;

//!-----------------------------------------------------------------------------------------------------------------------
//! GX2R resource flags
//!-----------------------------------------------------------------------------------------------------------------------
#define GX2R_RESOURCE_BIND_TEXTURE                      1 << 0
#define GX2R_RESOURCE_BIND_COLOR_BUFFER                 1 << 1
#define GX2R_RESOURCE_BIND_DEPTH_BUFFER                 1 << 2
#define GX2R_RESOURCE_BIND_SCAN_BUFFER                  1 << 3
#define GX2R_RESOURCE_BIND_VERTEX_BUFFER                1 << 4
#define GX2R_RESOURCE_BIND_INDEX_BUFFER                 1 << 5
#define GX2R_RESOURCE_BIND_UNIFORM_BLOCK                1 << 6
#define GX2R_RESOURCE_BIND_SHADER_PROGRAM               1 << 7
#define GX2R_RESOURCE_BIND_STREAM_OUTPUT                1 << 8
#define GX2R_RESOURCE_BIND_DISPLAY_LIST                 1 << 9
#define GX2R_RESOURCE_BIND_GS_RING_BUFFER               1 << 10
#define GX2R_RESOURCE_USAGE_CPU_READ                    1 << 11
#define GX2R_RESOURCE_USAGE_CPU_WRITE                   1 << 12
#define GX2R_RESOURCE_USAGE_GPU_READ                    1 << 13
#define GX2R_RESOURCE_USAGE_GPU_WRITE                   1 << 14
#define GX2R_RESOURCE_USAGE_DMA_READ                    1 << 15
#define GX2R_RESOURCE_USAGE_DMA_WRITE                   1 << 16
#define GX2R_RESOURCE_USAGE_FORCE_MEM1                  1 << 17
#define GX2R_RESOURCE_USAGE_FORCE_MEM2                  1 << 18
#define GX2R_RESOURCE_DISABLE_CPU_INVALIDATE            1 << 20
#define GX2R_RESOURCE_DISABLE_GPU_INVALIDATE            1 << 21
#define GX2R_RESOURCE_LOCKED_READ_ONLY                  1 << 22
#define GX2R_RESOURCE_GX2R_ALLOCATED                    1 << 29
#define GX2R_RESOURCE_LOCKED                            1 << 30

typedef struct _GX2RBuffer {
    u32 flags;
    u32 elemSize;
    u32 elemCount;
    void *buffer;
} GX2RBuffer;

typedef struct _GX2ContextState {
    u8 data[GX2_CONTEXT_STATE_SIZE];
} GX2ContextState;

typedef struct _GX2Surface {
    GX2SurfaceDim dim;
    u32 width;
    u32 height;
    u32 depth;
    u32 numMips;
    GX2SurfaceFormat format;
    GX2AAMode aa;
    GX2SurfaceUse use;
    u32 imageSize;
    void *imagePtr;
    u32 mipSize;
    void *mipPtr;
    GX2TileMode tileMode;
    u32 swizzle;
    u32 alignment;
    u32 pitch;
    u32 mipOffset[13];
} GX2Surface;

typedef struct _GX2ColorBuffer {
    GX2Surface surface;
    u32 viewMip;
    u32 viewFirstSlice;
    u32 viewNumSlices;
    void *auxPtr;
    u32  auxSize;
    u32 regs[5];
} GX2ColorBuffer;

typedef struct _GX2DepthBuffer {
    GX2Surface surface;
    u32 viewMip;
    u32 viewFirstSlice;
    u32 viewNumSlices;
    void *hiZPtr;
    u32  hiZSize;
    f32 clearDepth;
    u32 clearStencil;
    u32 regs[7];
} GX2DepthBuffer;


typedef struct _GX2Texture {
    GX2Surface surface;
    u32 viewFirstMip;
    u32 viewNumMips;
    u32 viewFirstSlice;
    u32 viewNumSlices;
    u32 compSel;
    u32 regs[5];
} GX2Texture;


typedef struct _GX2Sampler {
    u32 regs[3];
} GX2Sampler;

typedef struct _GX2AttribStream {
    u32 location;
    u32 buffer;
    u32 offset;
    s32 format;
    s32 indexType;
    u32 aluDivisor;
    u32 destSel;
    s32 endianSwap;
} GX2AttribStream;

typedef struct _GX2FetchShader {
    GX2FetchShaderType type;
    u32 _regs[GX2_NUM_FETCH_SHADER_REGISTERS];
    u32 shaderSize;
    void *shaderPtr;
    u32 numAttribs;
    u32 _num_divisors;
    u32 _divisors[2];
} GX2FetchShader;

typedef struct _GX2AttribVar {
    const char *name;
    s32 var_type;
    u32 array_count;
    u32 location;
} GX2AttribVar;


typedef struct _GX2UniformBlock {
    const char *name;
    u32 location;
    u32 block_size;
} GX2UniformBlock;

typedef struct _GX2UniformInitialValue {
    f32 value[4];
    u32 offset;
} GX2UniformInitialValue;

typedef struct _GX2SamplerVar {
    const char *name;
    s32 sampler_type;
    u32 location;
} GX2SamplerVar;

typedef struct _GX2UniformVar {
    const char *name;
    s32 var_type;
    u32 array_count;
    u32 offset;
    u32 block_index;
} GX2UniformVar;

typedef struct _GX2VertexShader {
    u32 _regs[GX2_NUM_VERTEX_SHADER_REGISTERS];
    u32 shaderSize;
    void *shaderPtr;
    GX2ShaderMode shaderMode;
    u32 numUniformBlocks;
    GX2UniformBlock *uniformBlocks;
    u32 numUniforms;
    GX2UniformVar *uniformVars;
    u32 numInitialValues;
    GX2UniformInitialValue *initialValues;
    u32 _numLoops;
    void *_loopVars;
    u32 numSamplers;
    GX2SamplerVar *samplerVars;
    u32 numAttribs;
    GX2AttribVar *attribVars;
    u32 ringItemsize;
    GX2Boolean hasStreamOut;
    u32 streamOutVertexStride[GX2_MAX_STREAMOUT_BUFFERS];
    GX2RBuffer shaderProgram;
} GX2VertexShader;

typedef struct _GX2PixelShader {
    u32  _regs[GX2_NUM_PIXEL_SHADER_REGISTERS];
    u32 shaderSize;
    void *shaderPtr;
    GX2ShaderMode shaderMode;
    u32 numUniformBlocks;
    GX2UniformBlock *uniformBlocks;
    u32 numUniforms;
    GX2UniformVar *uniformVars;
    u32 numInitialValues;
    GX2UniformInitialValue *initialValues;
    u32 _numLoops;
    void *_loopVars;
    u32 numSamplers;
    GX2SamplerVar *samplerVars;
    GX2RBuffer shaderProgram;
} GX2PixelShader;

typedef struct _GX2GeometryShader {
    u32 _regs[GX2_NUM_GEOMETRY_SHADER_REGISTERS];
    u32 shaderSize;
    void *shaderPtr;
    u32 copyShaderSize;
    void *copyShaderPtr;
    GX2ShaderMode shaderMode;
    u32 numUniformBlocks;
    GX2UniformBlock *uniformBlocks;
    u32 numUniforms;
    GX2UniformVar *uniformVars;
    u32 numInitialValues;
    GX2UniformInitialValue *initialValues;
    u32 _numLoops;
    void *_loopVars;
    u32 numSamplers;
    GX2SamplerVar *samplerVars;
    u32 ringItemsize;
    GX2Boolean hasStreamOut;
    u32 streamOutVertexStride[GX2_MAX_STREAMOUT_BUFFERS];
    GX2RBuffer shaderProgram;
    GX2RBuffer copyShaderProgram;
} GX2GeometryShader;

typedef struct _GX2StreamOutContext {
    u32 data[GX2_STREAMOUT_BUFFER_CONTEXT_SIZE / sizeof(u32)];
} GX2StreamOutContext;

typedef struct {
    u32 reg;
} GX2DepthStencilControlReg;

typedef struct {
    u32 reg;
} GX2PolygonControlReg;

typedef struct {
    u32 reg[2];
} GX2AlphaTestReg;

typedef struct {
    u32 reg;
} GX2ColorControlReg;

typedef struct {
    u32 reg[2];
} GX2BlendControlReg;

typedef struct {
    union {
        u32 u32All;
        f32 f32All;
    } reg[4];
} GX2BlendConstantColorReg;

static const u32 attribute_dest_comp_selector[20] = {
    GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01, GX2_COMP_SEL_X001, GX2_COMP_SEL_X001,  GX2_COMP_SEL_XY01, GX2_COMP_SEL_X001,
    GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW,
    GX2_COMP_SEL_XY01, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZ1,
    GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW
};

static const u32 texture_comp_selector[54] = {
    GX2_COMP_SEL_NONE, GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_X001,
    GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW,
    GX2_COMP_SEL_WZYX, GX2_COMP_SEL_X001, GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XY01, GX2_COMP_SEL_NONE,
    GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_NONE,
    GX2_COMP_SEL_NONE, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_WZYX, GX2_COMP_SEL_XY01, GX2_COMP_SEL_XY01,
    GX2_COMP_SEL_XY01, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_NONE, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW,
    GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_X001,
    GX2_COMP_SEL_XY01, GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_NONE, GX2_COMP_SEL_XYZ1,
    GX2_COMP_SEL_XYZ1, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_XYZW, GX2_COMP_SEL_X001, GX2_COMP_SEL_XY01
};

typedef struct _GX2Color {
    u8 r, g, b, a;
} GX2Color;

typedef struct _GX2ColorF32 {
    f32 r, g, b, a;
} GX2ColorF32;

typedef void* (* GX2RAllocFunction) (u32, u32, u32);
typedef void (* GX2RFreeFunction) (u32, void *);

typedef u32 GX2CompSel;

#ifdef __cplusplus
}
#endif

#endif
