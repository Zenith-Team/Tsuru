#ifndef MATH_TRIANGULAR_H_
#define MATH_TRIANGULAR_H_

#include "nw/math/constant.h"

namespace nw { namespace math { namespace internal {

// Based on sead
struct SinCosSample {
    f32 sin_val;
    f32 sin_delta;
    f32 cos_val;
    f32 cos_delta;
};

extern const SinCosSample gSinCosTbl[0x100+1];

} // namespace nw::math::internal

inline void SinCosIdx(f32* sin_val, f32* cos_val, u32 angle) {
    u32 idx = (angle >> 24) & 0xff;
    f32 del = static_cast<f32>(angle & 0xffffff) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    /*if (sin_val != NULL)*/ *sin_val = sample.sin_val + sample.sin_delta * del;
    /*if (cos_val != NULL)*/ *cos_val = sample.cos_val + sample.cos_delta * del;
}

inline f32 SinIdx(u32 angle) {
    // Does not match if using SinCosIdx
    // f32 sin_val; SinCosIdx(&sin_val, NULL, angle);
    // return sin_val;

    u32 idx = (angle >> 24) & 0xff;
    f32 del = static_cast<f32>(angle & 0xffffff) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    return sample.sin_val + sample.sin_delta * del;
}

inline f32 CosIdx(u32 angle) {
    // Does not match if using SinCosIdx
    // f32 cos_val; SinCosIdx(NULL, &cos_val, angle);
    // return cos_val;

    u32 idx = (angle >> 24) & 0xff;
    f32 del = static_cast<f32>(angle & 0xffffff) / 0x1000000;
    const internal::SinCosSample& sample = internal::gSinCosTbl[idx];

    return sample.cos_val + sample.cos_delta * del;
}

inline f32 Idx2Rad(f32 angle) {
    return angle * (F_PI / I_HALF_ROUND_IDX);
}

inline u32 Rad2Idx(f32 rad) {
    return static_cast<s64>(rad * (I_HALF_ROUND_IDX / F_PI));
}

inline void SinCosRad(f32* sin_val, f32* cos_val, f32 rad) {
    SinCosIdx(sin_val, cos_val, Rad2Idx(rad));
}

inline f32 SinRad(f32 rad) {
    // Does not match if using SinCosRad
    // f32 sin_val; SinCosRad(&sin_val, NULL, rad);
    // return sin_val;

    return SinIdx(Rad2Idx(rad));
}

inline f32 CosRad(f32 rad) {
    // Does not match if using SinCosRad
    // f32 cos_val; SinCosRad(NULL, &cos_val, rad);
    // return cos_val;

    return CosIdx(Rad2Idx(rad));
}

} } // namespace nw::math

#endif // MATH_TRIANGULAR_H_
