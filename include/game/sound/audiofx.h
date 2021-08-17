#pragma once

#include <nw/snd.h>

class AudioFx {
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam& getDelayParam();
};
