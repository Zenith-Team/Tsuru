#pragma once

#include "types.h"

namespace nw { namespace snd {

class FxReverbHi {
public:
    struct ReverbHiParam {
        ReverbHiParam()
            : mPreDelayTime(0.02f)
            , mFusedTime(3.0f)
            , mColoration(0.6f)
            , mDamping(0.4f)
            , mCrosstalk(0.1f)
            , mOutGain(1.0f)
            , mEarlyMode(5)
            , mPreDelayTimeMax(0.02f)
            , mFusedMode(0)
            , mEarlyGain(0.0f)
            , mFusedGain(1.0f)
        { }

        f32 mPreDelayTime;
        f32 mFusedTime;
        f32 mColoration;
        f32 mDamping;
        f32 mCrosstalk;
        f32 mOutGain;
        u32 mEarlyMode;
        f32 mPreDelayTimeMax;
        u32 mFusedMode;
        f32 mEarlyGain;
        f32 mFusedGain;
    };
};

} }
