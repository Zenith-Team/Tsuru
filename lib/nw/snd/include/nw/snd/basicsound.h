#pragma once

#include "types.h"

namespace nw { namespace snd {

namespace internal {

struct SoundActorParam {
    f32 volume;
    f32 pitch;
    f32 tvVolume;
    f32 tvPan;
    f32 drcVolume;
    f32 drcPan;
};

static_assert(sizeof(SoundActorParam) == 0x18, "nw::snd::internal::SoundActorParam size mismatch");

class BasicSound {
public:
    struct AmbientInfo { };

    void Stop(s32 fadeFrames);

    void SetVolume(f32 volume, s32 frames = 0);
    void SetPitch(f32 pitch);

    void SetLpfFreq(f32 lpfFreq)
    {
        m_LpfFreq = lpfFreq;
    }

    void SetBiquadFilter(s32 type, f32 value)
    {
        m_BiquadFilterType = static_cast<s8>(type);
        m_BiquadFilterValue = value;
    }

    void SetOutputLine(u32 lineFlag);
    void ResetOutputLine();
    void SetPan(f32 pan);

    u8 _0[0xCC];
    u8 m_Priority;
    s8 m_BiquadFilterType;
    u32 m_Id;
    f32 m_InitVolume;
    f32 m_Pitch;
    f32 m_LpfFreq;
    f32 m_BiquadFilterValue;
    u32 m_OutputLineFlag;
    // ...
};

//static_assert(sizeof(BasicSound) == 0x1A8, "nw::snd::internal::BasicSound size mismatch");

} } }
