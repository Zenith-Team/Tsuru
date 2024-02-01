#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <ppc_ghs.h>
#include <ppc_ps.h>

#define UGQR0                 896
#define UGQR1                 897
#define UGQR2                 898
#define UGQR3                 899
#define UGQR4                 900
#define UGQR5                 901
#define UGQR6                 902
#define UGQR7                 903

#define OS_GQR_F32 0x0000
#define OS_GQR_U8  0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8  0x0006
#define OS_GQR_S16 0x0007

#define OS_GQR_SCALE_NONE   0
#define OS_GQR_SCALE_2      1
#define OS_GQR_SCALE_4      2
#define OS_GQR_SCALE_8      3
#define OS_GQR_SCALE_16     4
#define OS_GQR_SCALE_32     5
#define OS_GQR_SCALE_64     6
#define OS_GQR_SCALE_128    7
#define OS_GQR_SCALE_256    8
#define OS_GQR_SCALE_512    9
#define OS_GQR_SCALE_1024   10
#define OS_GQR_SCALE_2048   11
#define OS_GQR_SCALE_4096   12
#define OS_GQR_SCALE_8192   13
#define OS_GQR_SCALE_16384  14
#define OS_GQR_SCALE_32768  15
#define OS_GQR_SCALE_65536  16
#define OS_GQR_SCALE_MAX    31

#define OS_GQR_DIVIDE_2     63
#define OS_GQR_DIVIDE_4     62
#define OS_GQR_DIVIDE_8     61
#define OS_GQR_DIVIDE_16    60
#define OS_GQR_DIVIDE_32    59
#define OS_GQR_DIVIDE_64    58
#define OS_GQR_DIVIDE_128   57
#define OS_GQR_DIVIDE_256   56
#define OS_GQR_DIVIDE_512   55
#define OS_GQR_DIVIDE_1024  54
#define OS_GQR_DIVIDE_2048  53
#define OS_GQR_DIVIDE_4096  52
#define OS_GQR_DIVIDE_8192  51
#define OS_GQR_DIVIDE_16384 50
#define OS_GQR_DIVIDE_32768 49
#define OS_GQR_DIVIDE_65536 48
#define OS_GQR_DIVIDE_MAX   32

#define OS_FASTCAST_U8  2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8  4
#define OS_FASTCAST_S16 5

static inline void OSInitFastCast(void) {
    __MTSPR(UGQR2, (OS_GQR_U8  << 16) | OS_GQR_U8);
    __MTSPR(UGQR3, (OS_GQR_U16 << 16) | OS_GQR_U16);
    __MTSPR(UGQR4, (OS_GQR_S8  << 16) | OS_GQR_S8);
    __MTSPR(UGQR5, (OS_GQR_S16 << 16) | OS_GQR_S16);
}

static inline void OSSetGQR2(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR2, val);
}

static inline void OSSetGQR3(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR3, val);
}

static inline void OSSetGQR4(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR4, val);
}

static inline void OSSetGQR5(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR5, val);
}

static inline void OSSetGQR6(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR6, val);
}

static inline void OSSetGQR7(u32 type, u32 scale) {
    u32 val = (((scale<<8)|type)<<16)|((scale<<8)|type);
    __MTSPR(UGQR7, val);
}

//!-----------------------------------------------------------------------------------------------------------------------
//! int to float
//!-----------------------------------------------------------------------------------------------------------------------
static inline f32 OSu8tof32Value(const u8* in) {
    f32x2 f = __PSQ_L(in, 1, OS_FASTCAST_U8);
    return f[0];
}

static inline void OSu8tof32(const u8* in, volatile f32* out) {
    *out = OSu8tof32Value(in);
}

static inline f32 OSu16tof32Value(const u16 * in) {
    f32x2 f = __PSQ_L(in, 1, OS_FASTCAST_U16);
    return f[0];
}

static inline void OSu16tof32(const u16* in, volatile f32* out) {
    *out = OSu16tof32Value(in);
}

static inline f32 OSs8tof32Value(const s8 * in) {
    f32x2 f = __PSQ_L(in, 1, OS_FASTCAST_S8);
    return f[0];
}

static inline void OSs8tof32(const s8* in, volatile f32* out) {
    *out = OSs8tof32Value(in);
}

static inline f32 OSs16tof32Value(const s16 * in) {
    f32x2 f = __PSQ_L(in, 1, OS_FASTCAST_S16);
    return f[0];
}

static inline void OSs16tof32(const s16* in, volatile f32* out) {
    *out = OSs16tof32Value(in);
}

//!-----------------------------------------------------------------------------------------------------------------------
//! float to int
//!-----------------------------------------------------------------------------------------------------------------------

static inline void OSf32tou8(const f32* in, volatile u8* out) {
    f32x2 f = {*in};
    __PSQ_ST((void *) out, f, 1, OS_FASTCAST_U8);
}

static inline u8 __OSf32tou8Value(const f32 in) {
    u8 value;
    f32x2 f = {in};
    __PSQ_ST((void *) &value, f, 1, OS_FASTCAST_U8);
    return value;
}

static inline void OSf32tou16(const f32* in, volatile u16* out) {
    f32x2 f = {*in};
    __PSQ_ST((void *) out, f, 1, OS_FASTCAST_U16);
}

static inline u16 __OSf32tou16Value(const f32 in) {
    u16 value;
    f32x2 f = {in};
    __PSQ_ST((void *) &value, f, 1, OS_FASTCAST_U16);
    return value;
}

static inline void OSf32tos8(const f32* in, volatile s8* out) {
    f32x2 f = {*in};
    __PSQ_ST((void *) out, f, 1, OS_FASTCAST_S8);
}

static inline s8 __OSf32tos8Value(const f32 in) {
    s8 value;
    f32x2 f = {in};
    __PSQ_ST((void *) &value, f, 1, OS_FASTCAST_S8);
    return value;
}

static inline void OSf32tos16(const f32* in, volatile s16* out) {
    f32x2 f = {*in};
    __PSQ_ST((void *) out, f, 1, OS_FASTCAST_S16);
}

static inline s16 __OSf32tos16Value(const f32 in) {
    s16 value;
    f32x2 f = {in};
    __PSQ_ST((void *) &value, f, 1, OS_FASTCAST_S16);
    return value;
}

#ifdef __cplusplus
}
#endif
