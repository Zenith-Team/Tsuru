#pragma once

#include "nw/snd.h"

class AudFxSocket {
public:
    AudFxSocket();
    ~AudFxSocket();

    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam& getDelayParam();

    u8 _0[0xB8 - 0x0];
};

static_assert(sizeof(AudFxSocket) == 0xB8, "AudFxSocket size mismatch");
