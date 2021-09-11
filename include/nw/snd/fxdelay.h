#pragma once

#include <types.h>

namespace nw { namespace snd {

class FxDelay {
public:
    struct DelayParam {
        DelayParam() 
            : delay(160.0f)
            , feedback(0.4f)
            , outGain(1.0f)
            , maxDelay(160.0f)
            , lpf(1.0f)
        { }

        f32 delay;
        f32 feedback;
        f32 outGain;
        f32 maxDelay;
        f32 lpf;
    };
};

} }
