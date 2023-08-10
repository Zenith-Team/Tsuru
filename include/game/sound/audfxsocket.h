#pragma once

#include "nw/snd.h"

class AudFxSocket {
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam& getDelayParam();
};
