#ifndef SEAD_MATHCALCCOMMONCAFE_H_
#define SEAD_MATHCALCCOMMONCAFE_H_

#include "sead/basis/seadTypes.h"

namespace sead {

template <typename T>
class MathCafe
{
public:
    static T rsqrt(T x);
};

} // namespace sead

#ifdef __cplusplus

#include "sead/math/cafe/seadMathCalcCommonCafe.hpp"

#endif // __cplusplus

#endif // SEAD_MATHCALCCOMMONCAFE_H_
