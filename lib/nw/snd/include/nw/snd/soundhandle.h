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

    void Stop(s32 fadeFrames) {
        if (IsAttachedSound())
            sound->Stop(fadeFrames);
    }

    void SetVolume(f32 volume, s32 frames = 0)
    {
        if (IsAttachedSound())
            sound->SetVolume(volume, frames);
    }

    void SetPitch(f32 pitch)
    {
        if (IsAttachedSound())
            sound->SetPitch(pitch);
    }

    void SetLpfFreq(f32 lpfFreq)
    {
        if (IsAttachedSound())
            sound->SetLpfFreq(lpfFreq);
    }

    void SetBiquadFilter(s32 type, f32 value)
    {
        //NW_MINMAX_ASSERT(type, BIQUAD_FILTER_TYPE_MIN , BIQUAD_FILTER_TYPE_MAX);

        if (IsAttachedSound())
            sound->SetBiquadFilter(type, value);
    }

    void SetOutputLine(u32 lineFlag)
    {
        if (IsAttachedSound())
            sound->SetOutputLine(lineFlag);
    }

    void ResetOutputLine()
    {
        if (IsAttachedSound())
            sound->ResetOutputLine();
    }

    bool IsAttachedSound() const {
        return sound != nullptr;
    }

    void DetachSound();

    internal::BasicSound* sound;
};

static_assert(sizeof(SoundHandle) == 0x4, "nw::snd::SoundHandle size mismatch");

} }
