#pragma once

#include "types.h"

namespace nw { namespace snd {

class FxReverbHi
{
public:
    struct ReverbHiParam
    {
        ReverbHiParam()
            : preDelayTime(0.02f)
            , fusedTime(3.0f)
            , coloration(0.6f)
            , damping(0.4f)
            , crosstalk(0.1f)
            , outGain(1.0f)
            , earlyMode(5)
            , preDelayTimeMax(0.02f)
            , fusedMode(0)
            , earlyGain(0.0f)
            , fusedGain(1.0f)
        {
        }

        f32 preDelayTime;
        f32 fusedTime;
        f32 coloration;
        f32 damping;
        f32 crosstalk;
        f32 outGain;
        u32 earlyMode;
        f32 preDelayTimeMax;
        u32 fusedMode;
        f32 earlyGain;
        f32 fusedGain;
    };
};

class FxDelay
{
public:
    struct DelayParam
    {
        DelayParam()
            : delay(160.0f)
            , feedback(0.4f)
            , outGain(1.0f)
            , maxDelay(160.0f)
            , lpf(1.0f)
        {
        }

        f32 delay;
        f32 feedback;
        f32 outGain;
        f32 maxDelay;
        f32 lpf;
    };
};

namespace internal {

typedef FxReverbHi::ReverbHiParam FxReverbHiParam;
typedef FxDelay::DelayParam FxDelayParam;

}

} }
