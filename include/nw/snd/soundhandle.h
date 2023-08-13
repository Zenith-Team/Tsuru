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

    void Stop(s32 fadeFrames)
    {
        if (IsAttachedSound())
            sound->Stop(fadeFrames);
    }

    bool IsAttachedSound() const {
        return sound != nullptr;
    }

    void DetachSound();

    internal::BasicSound* sound;
};

static_assert(sizeof(SoundHandle) == 0x4, "nw::snd::SoundHandle size mismatch");

} }
