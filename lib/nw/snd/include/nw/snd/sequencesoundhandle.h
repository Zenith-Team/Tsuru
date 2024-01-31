#pragma once

#include "nw/snd/sequencesound.h"

namespace nw { namespace snd {

class SoundHandle;

class SequenceSoundHandle {
public:
    SequenceSoundHandle()
        : sound(nullptr)
    { }

    explicit SequenceSoundHandle(SoundHandle* handle);

    ~SequenceSoundHandle() {
        DetachSound();
    }

    void Stop(s32 fadeFrames) {
        if (IsAttachedSound())
            sound->Stop(fadeFrames);
    }

    bool ReadVariable(s32 varNo, s16* var) const {
        if (!IsAttachedSound())
            return false;
            
        return sound->ReadVariable(varNo, var);
    }

    bool WriteVariable(s32 varNo, s16 var) {
        if (!IsAttachedSound())
            return false;

        sound->WriteVariable(varNo, var);
        return true;
    }

    bool IsAttachedSound() const {
        return sound != nullptr;
    }

    void DetachSound();

    internal::SequenceSound* sound;
};

} }
