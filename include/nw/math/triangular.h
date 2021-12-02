#pragma once

#include <nw/math/constant.h>

namespace nw { namespace math { namespace internal {

// Based on sead
struct SinCosSample {
    f32 sinVal;
    f32 sinDelta;
    f32 cosVal;
    f32 cosDelta;
};

extern const SinCosSample globalSinCosTbl[0x100 + 1];

}

inline void SinCosIdx(f32* sinVal, f32* cosVal, u32 angle) {
    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::globalSinCosTbl[idx];

    // if (sinVal != NULL)
        *sinVal = sample.sinVal + sample.sinDelta * del;
    // if (cosVal != NULL)
        *cosVal = sample.cosVal + sample.cosDelta * del;
}

// Does not match if using SinCosIdx
//
// f32 sinVal; SinCosIdx(&sinVal, NULL, angle);
// return sinVal;
inline f32 SinIdx(u32 angle) {
    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::globalSinCosTbl[idx];

    return sample.sinVal + sample.sinDelta * del;
}

// Does not match if using SinCosIdx
//
// f32 cosVal; SinCosIdx(NULL, &cosVal, angle);
// return cosVal;
inline f32 CosIdx(u32 angle) {
    u32 idx = (angle >> 24) & 0xFF;
    f32 del = static_cast<f32>(angle & 0xFFFFFF) / 0x1000000;
    const internal::SinCosSample& sample = internal::globalSinCosTbl[idx];

    return sample.cosVal + sample.cosDelta * del;
}

inline f32 Idx2Rad(f32 angle) {
    return angle * (F_PI / I_HALF_ROUND_IDX);
}

inline u32 Rad2Idx(f32 rad) {
    return static_cast<s64>(rad*  (I_HALF_ROUND_IDX / F_PI));
}

inline void SinCosRad(f32* sinVal, f32* cosVal, f32 rad) {
    SinCosIdx(sinVal, cosVal, Rad2Idx(rad));
}

// Does not match if using SinCosRad
//
// f32 sinVal; SinCosRad(&sinVal, NULL, rad);
// return sinVal;
inline f32 SinRad(f32 rad) {
    return SinIdx(Rad2Idx(rad));
}

// Does not match if using SinCosRad
//
// f32 cosVal; SinCosRad(NULL< &cosVal, rad)
// return cosVal;
inline f32 CosRad(f32 rad) {
    return CosIdx(Rad2Idx(rad));
}

} }
