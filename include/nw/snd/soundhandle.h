#pragma once

#include "nw/snd/basicsound.h"

namespace nw { namespace snd {

class SoundHandle {
public:
    SoundHandle()
        : sound(nullptr)
    { }

    ~SoundHandle() {
        DetachSound();
    }

    void DetachSound();

    internal::BasicSound* sound;
};

static_assert(sizeof(SoundHandle) == 0x4, "nw::snd::SoundHandle size mismatch");

} }
