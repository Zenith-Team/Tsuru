#pragma once

#include "nw/snd.h"

class AudioFx {
public:
    nw::snd::FxReverbHi::ReverbHiParam& getReverbHiParam();
    nw::snd::FxDelay::DelayParam& getDelayParam();
};
