#pragma once

#include <types.h>

namespace nw { namespace snd {

class FxDelay {
public:
    struct DelayParam {
        DelayParam() 
            : mDelay(160.0f)
            , mFeedback(0.4f)
            , mOutGain(1.0f)
            , mMaxDelay(160.0f)
            , mLpf(1.0f)
        { }
        
        f32 mDelay;
        f32 mFeedback;
        f32 mOutGain;
        f32 mMaxDelay;
        f32 mLpf;
    };
};

} }
