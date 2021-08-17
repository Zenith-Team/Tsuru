#pragma once

#include <nw/snd.h>

class AudioFx {
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam& getDelayParam();
};
