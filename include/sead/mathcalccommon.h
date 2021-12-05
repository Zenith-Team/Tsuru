#pragma once

#include "types.h"

namespace sead {

template <typename T>
class MathCalcCommon {
public:
    // Linearly moves a variable towards a target value
    // @param out Pointer to variable which will be modified
    // @param target The value to move the variable towards
    // @param step The amount that the variable will be moved by
    // @return Whether or not the variable has reached the target
    static bool chase(T* out, T target, T step);
};

typedef MathCalcCommon<s32> Mathi;
typedef MathCalcCommon<u32> Mathu;
typedef MathCalcCommon<f32> Mathf;

}
