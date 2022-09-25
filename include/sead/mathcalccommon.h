#pragma once

#include "types.h"

namespace sead {

template <typename T>
class MathCalcCommon {
public:
    struct SinCosSample {
        T sinVal;
        T sinDelta;
        T cosVal;
        T cosDelta;
    };

public:
    // Linearly moves a variable towards a target value
    // @param out Pointer to variable which will be modified
    // @param target The value to move the variable towards
    // @param step The amount that the variable will be moved by
    // @return Whether or not the variable has reached the target
    static bool chase(T* out, T target, T step);

    static T abs(T x) {
        return (x < 0) ? -x : x;
    }

    static T max(T a, T b) {
        if (a < b) return b;
        else       return a;
    }

    static T min(T a, T b) {
        if (a < b) return a;
        else       return b;
    }

    static T clampMax(T val, T max_) {
        return min(val, max_);
    }

    static T clampMin(T val, T min_) {
        return max(val, min_);
    }

    static T clamp2(T min_, T val, T max_) {
        if (val < min_) return min_;
        if (val > max_) return max_;

        return val;
    }

    static void sinCosIdx(T* outsin, T* outcos, u32 idx);

public:
    static const SinCosSample cSinCosTbl[257];
};

typedef MathCalcCommon<s32> Mathi;
typedef MathCalcCommon<u32> Mathu;
typedef MathCalcCommon<f32> Mathf;

template<>
void MathCalcCommon<f32>::sinCosIdx(f32* outsin, f32* outcos, u32 idx) {
    u32 index = (idx >> 24) & 0xFF;
    f32 rest = static_cast<f32>(idx & 0xFFFFFF) / 0x1000000;
    const SinCosSample& sample = cSinCosTbl[index];

    if (outsin)
        *outsin = sample.sinVal + sample.sinDelta * rest;
    
    if (outcos)
        *outcos = sample.cosVal + sample.cosDelta * rest;
}

}
